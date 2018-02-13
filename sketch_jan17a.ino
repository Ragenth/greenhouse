// www.arduinesp.com
//
// Plot DTH11 data on thingspeak.com using an ESP8266
// April 11 2015
// Author: Jeroen Beemster
// Website: www.arduinesp.com

#include <ESP8266WiFi.h>

// replace with your channel’s thingspeak API key,
String apiKey = "Y4BBKYGN8Q7TPYGT";
const char* ssid = "Trilacious";
const char* password = "9995546007@DANI";

const char* server = "api.thingspeak.com";
String param1, param2,param3,param4;

WiFiClient client;

void setup() {
Serial.begin(9600);
delay(10);


WiFi.begin(ssid, password);

Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");

}

void loop() {

if (Serial.available() > 0) {
    String rcvd = Serial.readString();
    Serial.print("Serial received: ");
    Serial.println(rcvd);
   // param1 = rcvd.substring(1,3);
   // param2 = rcvd.substring(3,5);
    param1 = rcvd.substring(1,3);
    param2 = rcvd.substring(3,5);
    param3 = rcvd.substring(5,8);
    param4 = rcvd.substring(8); 
}
if (client.connect(server,80)) { // "184.106.153.149" or api.thingspeak.com
String postStr = apiKey;
postStr +="&field1=";
postStr += String(param1);
postStr +="&field2=";
postStr += String(param2);
postStr +="&field3=";
postStr += String(param3);
postStr +="&field4=";
postStr += String(param4);
postStr += "\r\n\r\n";

client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);

//Serial.print("Temperature: ");
//Serial.print(t);
//Serial.print(" degrees Celcius Humidity: ");
//Serial.print(h);
//Serial.println("% send to Thingspeak");
}
client.stop();

Serial.println("Waiting…");
// thingspeak needs minimum 15 sec delay between updates
delay(20000);
}

