/*
Code Source: Connected environment course
   
一、specifing aims before coding

    1.setting up wifi connection
    2.connecting Mqtt server
    3.get the values of the plant and refresh the data-time- main loop
    4.pushing the data to the mqtt server
    5.showing the data in the http page
    
二、define functions we used to realise our aims-frame is very important

    1.setting up wifi connection
      startwifi()
    2.connecting Mqtt server
      client.setServer()
      client.setCallback()
    3.get the values of the plant and refresh the data-time
      dht.begin()        
      readMoisture()    
      readhumidity()
      readtemperature()
      syncDate()
    4.pushing the data to the mqtt server
      sendMQTT()
    5.showing the data in the http page
      startWebserver()
      sendHTML()
      
三、specifing each function
    1.setting up wifi connection
      startwifi()
                  if :Wifi connect successful, the output would be:Wifi connected, IP address:
                  else :the output will be "....." untill the wifi connect, it will print: Wifi connected, IP address:
             
    2.connecting Mqtt server
      client.setServer()
      client.setCallback()
      
    3.get the values of the plant and refresh the data-time
      readMoisture()
                  power the sensor
                  get: the Moisture data
                  stop power
                  print: the Moisture data
      
      readhumidity()
      readtemperature()
      syncDate()                                  
                  get:the real data and time
                  print:the data and time in the format:UTC: Europe/London London time:
                  
    4.pushing the data to the mqtt server
      sendMQTT() 
                  if:client doesn't connect, reconnect() again
                  else:read the value of the temperature, print the data under the topic:student/CASA0014/plant/ucrhhew/temperature
                  
    5.showing the data in the http page
      startWebserver()
             
                  if: connected and IP address obtained start HTTP server
                  print:"HTTP server started"

      sendHTML()
                  write the whole structure of the page using html
*/


/* 1.Import libraries part
 *  At the begaining we need to import librararies that will be uesd in the later programming
 
 Name                                       Used for
    wifi library-<ESP8266WiFi.h>             :one of the special features of Feather Huzzah ESP8266 
    Mqtt server library-<ESP8266WebServer.h> :Connecting with Mqtt server
    Time library- <ezTime.h>                 :knowing what date or time a measurement was taken
                                              !!!Arduino cannot output the current time                                      
    <PubSubClient.h>                         :This library allows you to send and receive MQTT messages.
    <DHT.h>                                  :Temp & Humidity Sensors
    <DHT_U.h>
 */
#include <ESP8266WiFi.h>      
#include <ESP8266WebServer.h> 
#include <ezTime.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <DHT_U.h>

/* 2.Define part
 *  define pin for each unit and create variables and the type of the DTH 
    Pinsetting:   DHTpin;soilpin;sensorVCC;build-in Led
    variables:    Temperature;Humidity;Moisture
    DHTTYPE and initialize DHT sensor
*/
// There are many different DHT types. For example:DHT11, DHT22 and AM2302 Sensors. In this case the type should be DHT22
#define DHTTYPE DHT22   
uint8_t DHTPin = 12;        // on Pin 2 of the Huzzah
uint8_t soilPin = 0;      // ADC or A0 pin on Huzzah
float Temperature;
float Humidity;
int Moisture = 1; // initial value just in case web page is loaded before readMoisture called
int sensorVCC = 13;
int blueLED = 2;
DHT dht(DHTPin, DHTTYPE);   // Initialize DHT sensor.


//3.Connecting Wifi and MQTT
#include "arduino_secrets.h" 
/*
Adding new tab,naming the new tab as arduino_secrets.h putting the sensitive data into the file

The format in the arduino_secrets.h file should be like this:entering the real information for each attribute
#define SECRET_SSID "ssid name"
#define SECRET_PASS "ssid password"
#define SECRET_MQTTUSER "user name - eg student"
#define SECRET_MQTTPASS "password";

The format in the orginal file should be like this:entering the vitual information for each attribute
const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;
 */

const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;

ESP8266WebServer server(80);                     //!!!port 80 is a default port that the server "listens to" or expects to receive from a Web client, Experimental services run at port 8080.
const char* mqtt_server = "mqtt.cetools.org";   //Setting the address for the web server
WiFiClient espClient;                          //passing in the WiFiClient just defined as the connection.
PubSubClient client(espClient);               //To new a PubSubClient object-espClient-that will handle the MQTT messages
long lastMsg = 0;
char msg[50];
int value = 0;

// 4.Date and time-In this case time used for refresh the data which is collecting from the plant.Once the current time change, print the value of h,m,t
Timezone GB;

/*5. setup functions
 * 
 *  define which pin act as Output or Input:                
 *  
 *      Output            BUILTIN_LED-to be controllable via broker by changing the number 0 and 1
 *                        sensorVCC-to control the soil sensor
 *                        blueLED-for status indicator
 *                  
 *      Input             DHTPin                
 *      
 * !!!digitalWrite(BUILTIN_LED, HIGH); 
 * 
 *                        turn the led off-by making the voltage High:Some of those boards have the LED connected to VCC, 
 *                        probably because the MCU can sink more (the needed) current in the I/O pins at lower level.
 *        
 * start DHT sensor:      dht.begin()
 *  
 * start wifi;webserver,date:
 *                        startWifi():
                          startWebserver();
                          syncDate();
                                        
   start MQTT server:    client.setServer(mqtt_server, 1884);
                          client.setCallback(callback);
 */

void setup() {
  // Set up LED to be controllable via broker
  // Initialize the BUILTIN_LED pin as an output
  // Turn the LED off by making the voltage HIGH
  pinMode(BUILTIN_LED, OUTPUT);     
  digitalWrite(BUILTIN_LED, HIGH); 

  // Set up the outputs to control the soil sensor
  // switch and the blue LED for status indicator
  pinMode(sensorVCC, OUTPUT); 
  digitalWrite(sensorVCC, LOW);
  pinMode(blueLED, OUTPUT); 
  digitalWrite(blueLED, HIGH);

  // open serial connection for debug info
  Serial.begin(115200);
  delay(100);

  // start DHT sensor
  pinMode(DHTPin, INPUT);
  dht.begin();

  // run initialisation functions
  startWifi();
  startWebserver();
  syncDate();

  // start MQTT server
  client.setServer(mqtt_server, 1884);
  client.setCallback(callback);

}
/*6.loop
 * setting a handleClient for receiving requests to webserver
 * if the time changed,read the misture again and send the real-time data to the Mqtt and print the current time
 * readMoisture()
 * sendMQTT()
 */
void loop() {
  server.handleClient(); 
  if (minuteChanged()) {
    readMoisture();
    sendMQTT();
    Serial.println(GB.dateTime("H:i:s")); // UTC.dateTime("l, d-M-y H:i:s.v T")
  }
  
  client.loop();
}


void readMoisture(){
  
  // power the sensor
  digitalWrite(sensorVCC, HIGH);
  digitalWrite(blueLED, LOW);
  delay(100);
  // read the value from the sensor:
  Moisture = analogRead(soilPin);         
  //Moisture = map(analogRead(soilPin), 0,320, 0, 100);    // note: if mapping work out max value by dipping in water     
  //stop power 
  digitalWrite(sensorVCC, LOW);  
  digitalWrite(blueLED, HIGH);
  delay(100);
  Serial.print("Wet ");
  Serial.println(Moisture);   // read the value from the nails
}


void startWifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // check to see if connected and wait until you are
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void syncDate() {
  // get real date and time
  waitForSync();
  Serial.println("UTC: " + UTC.dateTime());
  GB.setLocation("Europe/London");
  Serial.println("London time: " + GB.dateTime());

}

void startWebserver() {
  // when connected and IP address obtained start HTTP server
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
}


void sendMQTT() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  Temperature = dht.readTemperature(); // Gets the values of the temperature
  snprintf (msg, 50, "%.1f", Temperature);
  Serial.print("Publish message for t: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucrhhew/temperature", msg);

  Humidity = dht.readHumidity(); // Gets the values of the humidity
  snprintf (msg, 50, "%.0f", Humidity);
  Serial.print("Publish message for h: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucrhhew/humidity", msg);

  //Moisture = analogRead(soilPin);   // moisture read by readMoisture function
  snprintf (msg, 50, "%.0i", Moisture);
  Serial.print("Publish message for m: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucrhhew/moisture", msg);

}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect with clientID, username and password
    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe("student/CASA0014/plant/ucrhhew/inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void handle_OnConnect() {
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity
  server.send(200, "text/html", SendHTML(Temperature, Humidity, Moisture));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat, float Humiditystat, int Moisturestat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>ESP8266 DHT22 Report</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>ESP8266 Huzzah DHT22 Report</h1>\n";

  ptr += "<p>Temperature: ";
  ptr += (int)Temperaturestat;
  ptr += " C</p>";
  ptr += "<p>Humidity: ";
  ptr += (int)Humiditystat;
  ptr += "%</p>";
  ptr += "<p>Moisture: ";
  ptr += Moisturestat;
  ptr += "</p>";
  ptr += "<p>Sampled on: ";
  ptr += GB.dateTime("l,");
  ptr += "<br>";
  ptr += GB.dateTime("d-M-y H:i:s T");
  ptr += "</p>";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
