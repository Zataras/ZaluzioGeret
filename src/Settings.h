/** The MIT License (MIT)

Copyright (c) 2019 Lukas Luc3as Porubcan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266HTTPUpdateServer.h>
#include "FS.h"
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include <PubSubClient.h>
#include <Servo.h>
#include <Wire.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

// Constants and initializations
String themeColor = "light-green"; // this can be changed later in the web interface.
unsigned long lastSend;
int counter = 0;
WiFiClient espClient;
PubSubClient client(espClient);


//******************************
// Start Settings
//******************************

// Peripherals 
int servoPIN = D4;
int servoEnablePIN = D3;
int LDRPIN = A0;
Servo blinds;
int MINANGLE = 0;
int MAXANGLE = 180;
int MAXLIGHT = 1023;
int lightPercent = -1;
int actualServoAngle = 90;
int buttonUp = D5;
int buttonDown = D6;
long buttonTimer = 0;   // For counting time the button is presed
long longPressTime = 750;  // How long is considered as long-press of button (miliseconds)
long megaLongPressTime = 8 * 1000;  // How long is considered as long-press of button (miliseconds)
boolean buttonActive = false;
boolean longPressActive = false;
boolean megaLongPressActive = false;
boolean buttonUpActive = false;
boolean buttonDownActive = false;

// Webserver
const int WEBSERVER_PORT = 80; // The port you can access this device on over HTTP
const boolean WEBSERVER_ENABLED = true;  // Device will provide a web interface via http://[ip]:[port]/
boolean IS_BASIC_AUTH = true;  // true = require athentication to change configuration settings / false = no auth
char* www_username = "admin";  // User account for the Web Interface
char* www_password = "password";  // Password for the Web Interface
String MQTTADDRESS; 
String MQTTUSER ;
String MQTTPASS ;
int MQTTPORT;
String MQTTSUBTOPIC ;
String MQTTPUBTOPIC ;
String MQTTSLAVEID ;
const char* on_cmd = "ON";
const char* off_cmd = "OFF";
const char* will_msg = "Offline";
const char* online_msg = "Online";
int sendInterval = 5;
String LWTTopic ;
String SUBTopic ;
String SUBTopicLight ;
String PUBTopicLight ;
String PUBTopicAngle ;
String SlaveTopic;

// Date and Time
float UtcOffset = +2; // Hour offset from GMT for your timezone
boolean IS_REVERSED_CONTROL = false;  
const char* ntp_server = "eu.pool.ntp.org";
int minutesBetweenDataRefresh = 15;
boolean DISPLAYCLOCK = true;   // true = Show Clock when not printing / false = turn off display when not printing
long now ;

// LED Settings
const int externalLight = D1; // Set to unused pin, like D1, to disable use of built-in LED (LED_BUILTIN)

// OTA Updates
boolean ENABLE_OTA = true;     // this will allow you to load firmware to the device over WiFi (see OTA for ESP8266)
String OTA_Password = "";      // Set an OTA password here -- leave blank if you don't want to be prompted for password

//******************************
// End Settings
//******************************
