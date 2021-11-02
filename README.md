# Plant monitor
## 1.Overview
An IoT device used to check the humidity,temperature and moisture levels of your plants and keep your plants safe.  

 ![](https://github.com/guodongxiaren/ImageCache/raw/master/Logo/foryou.gif)  
 
 
## 2.Story
* **Introduction**  

>>Plants help clean our air, as well as produce clean oxygen for other living creatures that need it; They also protect us from many natural disasters. For that and many other reasons, a lot of people like to take care of plants of their own. Some people know how to take care of them, but a lot of people don't know how to take care their plants properly. The “Plant Monitor”, is a device that has two main sensors: a moisture sensor(nail), and a humidity and temperature sensor (DHT22). By utilizing these sensors, the device will be able to tell the plants’ owner about the plant’s moisture,humidity and temperature levels. The owner should know the best levels of moisture, humidity and temperature for plants to grow, comparising with the indicator values on the Plant Monitor, do some measures to keep plants well.  

* **Demonstration Picture**
 >>Before your build-up, your need to have a clear overview about how the device looks like, this picture shows the plant monitor, when putting the nails in the soil, the whole circuit is complete,running the sketch on Arduino,it will show m,t,h value.  
 >>![](https://github.com/guodongxiaren/ImageCache/raw/master/Logo/foryou.gif)  

* **Things used in this project**

  * Hardware components    
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
 
  
   * Software apps（oder by using order)      
 >>>>Arduino IDE    [Arduino IDE download](https://www.baidu.com/)  
 >>>>CP210*VCPDriver   [CP210Driver download](https://www.baidu.com/)  
 >>>>MQTT Explorer     [MQTT Explore download](https://www.baidu.com/)  
 >>>>Raspberry pi imager   [Raspberry download](https://www.baidu.com/)  
 >>>>Telegraf     [Telegraf download](https://www.baidu.com/)  
 >>>>InfluxDB     [InfluxDB download](https://www.baidu.com/)  
 >>>>Grafana     [Grafana download](https://www.baidu.com/)  
 
  * Hand tools    
 >>>>Soldering iron  
 
* Setting up Feather Huzzah ESP8266 Wifi  

  * Installing the Arduino IDE 1.6.8 or greater  
  * Installing CP210*VCPDriver    
  * Installing the ESP8266 Board Package  
  * Setup ESP8266 Support:CPU frequency-80 MHz, Upload Speed-115200, matching COM port-"SLAB_USBtoUART"
  * Connecting via WiFI  [TestWifi](https://www.baidu.com/)  
  
* Setting the time on the Feather Huzzah ESP8266
  * Installing ezTime library on Arduino
  * Printing the time    [TestTime](https://www.baidu.com/) 
   
* Schematics and build a soil moisture sensor 
>>![](https://github.com/guodongxiaren/ImageCache/raw/master/Logo/foryou.gif)   
  Picture source:Connected environment course  
  
* Publishing soil data to an MQTT server   
  * Installing MQTT Explorer  
  * Installing PubSubClient library on Arduino
  * Uploading MQTT with nails sketch to send data to MQTT server  [MQTT with nails](https://www.baidu.com/)  
  * Connecting MQTT server to see the real time data from your plant monitor  
  
* Storing data on a RPI gateway
  * Installing Raspberry Pi imager  
  * Select sd card and setup some of the SSH / SSID info  
  * Insert the card into the RPi and power it up  
  * Log into the device using SSH    
* Visualise time series data  
  * Installing the Influx, Telegraf and Grafana  
  * Going the address http://hostname.local:3000  
  * Adding your first datasource  
  * Create Dashboard and seeing the data     

## 3.Problems and Solutions
* Changing the circuit
* Soldering and Assembly
## 4.Code+Comments
Detailed explanations and Author's understanding for the code can be seen here [Plant Monitor](https://www.baidu.com/)

## 5.Improvement


