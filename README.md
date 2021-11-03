# Plant monitor
## 1.Overview
An IoT device used to check the humidity,temperature and moisture levels of your plants and keep your plants in a good condition.  

 <img src="https://github.com/roxy-cym/img/blob/main/Plant%20monitor/IMG_6810.JPG" width="1000" height="400" alt="procedures"/>
 
## 2.Story
* **Introduction**  

>>Plants help clean our air, as well as produce clean oxygen for other living creatures that need it; They also protect us from many natural disasters. For that and many other reasons, a lot of people like to take care of plants of their own. Some people know how to take care of them, but a lot of people don't know how to take care their plants properly. The “Plant Monitor”, is a device that has two main sensors: a moisture sensor(nail), and a humidity and temperature sensor (DHT22). By utilizing these sensors, the device will be able to tell the plants’ owner about the plant’s moisture,humidity and temperature levels. The owner should know the best levels of moisture, humidity and temperature for plants to grow, comparising with the indicator values on the Plant Monitor, do some measures to keep plants well.  

* **Demonstration Picture**
 >>Before your build-up, your need to have a clear overview about how the device looks like, this picture shows the plant monitor, when putting the nails in the soil, the whole circuit is complete,running the sketch on Arduino,it will show m,t,h value.  
    
 >><img src="https://github.com/roxy-cym/img/blob/main/Plant%20monitor/IMG_6811.JPG" width="1000" height="800" alt="plant monitor"/> 

* **Things used in this project**

>>>>**Hardware components**      
>>>>name  | number  
>>>>---- | ----- 
>>>>Arduino Feather Huzzah ESP8266  | 1 
>>>>DHT22  | 1
>>>>Raspberry pi  | 1
>>>>Resistor-100  | 2
>>>>Resistor-200  | 1
>>>>Resistor-10k  | 2
>>>>Transistor  | 1
>>>>Nails  | 2
 
  
 >>>>**Software apps**     
 >>>>Arduino IDE    [Arduino IDE download](https://www.arduino.cc/en/software)  
 >>>>CP210*VCPDriver   [CP210Driver download](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide)  
 >>>>MQTT Explorer     [MQTT Explore download](http://mqtt-explorer.com/)  
 >>>>Raspberry pi imager   [Raspberry download](https://www.raspberrypi.com/software/)  
 >>>>Telegraf     [Telegraf download](https://github.com/influxdata/telegraf/releases)  
 >>>>InfluxDB     [InfluxDB download](https://portal.influxdata.com/downloads/#influxdb)  
 >>>>Grafana       
 
 >>>>**Hand tools**    
 >>>>Soldering iron  
 
* Setting up Feather Huzzah ESP8266 Wifi  

  * Installing the Arduino IDE 1.6.8 or greater  
  * Installing CP210*VCPDriver    
  * Installing the ESP8266 Board Package  
  * Setup ESP8266 Support:CPU frequency-80 MHz, Upload Speed-115200, matching COM port-"SLAB_USBtoUART"
  * Connecting via WiFI  [TestWifi](https://github.com/roxy-cym/plant-monitor/tree/main/TestWifi)  
  
* Setting the time on the Feather Huzzah ESP8266
  * Installing ezTime library on Arduino
  * Printing the time    [TestTime](https://github.com/roxy-cym/plant-monitor/tree/main/TestTime) 
   
* Schematics and building a plant monitor 
![](https://github.com/roxy-cym/img/blob/main/Plant%20monitor/circuit.png)   
  Picture source:Connected environment course  
  
* Connecting to the MQTT server and publishing soil data to an MQTT server   
  * Installing MQTT Explorer  
  * Installing PubSubClient library on Arduino
  * Uploading MQTT with nails sketch to send data to MQTT server  [MQTT with nails](https://github.com/roxy-cym/plant-monitor/tree/main/MQTT_with_nails)  
  * Connecting MQTT server to see the real time data from your plant monitor  
  
* Storing data on a RPI gateway
  * Installing Raspberry Pi imager  
  * Select sd card and setup some of the SSH / SSID info  
  * Insert the card into the RPi and power it up  
  * Log into the device using SSH    
* Visualising time series data  
  * Installing the Influx, Telegraf and Grafana  
  * Setting up Telegraf configuration   [Telegraf configuration](https://github.com/roxy-cym/plant-monitor/tree/main/Telegraf%20Configuration) 
  * Going the address http://hostname.local:3000  
  * Adding your first datasource-InfluxDB
  * Create Dashboard and seeing the data     

## 3.Problems and Solutions  
* Problem Description:  
  * When I connected the circuit referring to The Fritzing diagram，Putting the nail in a different environment.The Moisture value does not change  
* Analyzing:  
  * The connection between the various parts is unstable-result in disconnection of the circuit
  * Short circuit
The circuit is not connected
* Solution:  
  * Referring the sketch / schematic of the circuit,do it again! The position of each part does not need to be exactly the same as Fritzing diagram, but the connection structure of the circuit must refer to the sketch / schematic  
  
  >><img src="https://github.com/roxy-cym/img/blob/main/Plant%20monitor/schematics.png" width="1000" height="400" alt="schematics"/>  
  >>  
  >><img src="https://github.com/roxy-cym/img/blob/main/Plant%20monitor/IMG_6814.JPG" width="1000" height="400" alt="Circuit"/>  
  * Soldering and Assembly  
  
  >><img src="https://github.com/roxy-cym/img/blob/main/Plant%20monitor/IMG_6813.JPG" width="1000" height="400" alt="Soldering"/> 
  
## 4.Code+Comments
* Detailed explanations and Author's understanding for the code can be seen here [Plant Monitor](https://github.com/roxy-cym/plant-monitor/tree/main/MQTT_with_nails)

## 5.Improvement  
[Improvment](https://github.com/roxy-cym/plant-monitor/blob/main/Improvment/Improvment.ino)


