#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "Trilacious";
const char* password = "9995546007@DANI";

ESP8266WebServer server(80);

String param1, param2, param3, param4, param5, param6;

void handleRoot() {
  String cmd;
  cmd += "<!DOCTYPE HTML>\r\n";
  cmd += "<html>\r\n";
  cmd += "<head>";

  cmd += "<title>\"IoT Based Green House Monitoring System\"</title>";
  cmd += "<meta http-equiv='refresh' content='3'/>";

  cmd += "<style>";
  cmd += "a {";
  cmd += "background-color: #990033;";
  cmd += "border: none;";
  cmd += "color: white;";
  cmd += "padding: 7px 20px;";
  cmd += "text-align: center;";
  cmd += "text-decoration: none;}";
  cmd += "a:hover {background-color: green;}";
  cmd += "</style>";
  cmd += "</head>";

  cmd += "<h1>IoT Based Green House Monitoring  System</h1>";
  cmd += "<h3>MODE:     " + param1 +"</h3>";
  cmd += "<h3>Temparature:  " + param2 + "</h3>";
  cmd += "<h3>Humidity:     " + param3 + "</h3>";
  cmd += "<h3>Light:         " + param4 + "</h3>";
  cmd += "<h3>MOISTURE:     " + param5 +"</h3>";
  cmd += "<h3>MODE: <a href=\"dev1=1\">AUTO</a>---<a href=\"dev1=0\">MANUAL</a></h3>";
  cmd += "<h3>FAN: <a href=\"dev2=1\">ON</a>---<a href=\"dev2=0\">OFF</a></h3>";
  cmd += "<h3>PUMP: <a href=\"dev3=1\">ON</a>---<a href=\"dev3=0\">OFF</a></h3>";
  cmd += "<h3>LAMB: <a href=\"dev4=1\">ON</a>---<a href=\"dev4=0\">OFF</a></h3>";

  cmd += "<html>\r\n";
  server.send(200, "text/html", cmd);
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void){

  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/dev1=1", [](){
    Serial.print("*g");
    server.send(200, "text/plain", "MODE: AUTO");
  });

  server.on("/dev1=0", [](){
    Serial.print("*G");
    server.send(200, "text/plain", "MODE : MANUAL");
  });
server.on("/dev2=1", [](){
    Serial.print("*B");
    server.send(200, "text/plain", "FAN : ON");
  });

  server.on("/dev2=0", [](){
    Serial.print("*b");
    server.send(200, "text/plain", "FAN :  OFF");
  });
server.on("/dev3=1", [](){
    Serial.print("*D");
    server.send(200, "text/plain", "PUMB : ON");
  });

  server.on("/dev3=0", [](){
    Serial.print("*d");
    server.send(200, "text/plain", "PUMB :  OFF");
  });
server.on("/dev4=1", [](){
    Serial.print("*C");
    server.send(200, "text/plain", "LAMB : ON");
  });

  server.on("/dev4=0", [](){
    Serial.print("*c");
    server.send(200, "text/plain", "LAMB :  OFF");
  });

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();

  // Read serial
  if (Serial.available() > 0) {
    String rcvd = Serial.readString();
    Serial.print("Serial received: ");
    Serial.println(rcvd);
    param1 = rcvd.substring(1,2);
    param2 = rcvd.substring(2,4);
    param3 = rcvd.substring(4,6);
    param4 = rcvd.substring(6,9);
    param5 = rcvd.substring(9);
  }
}
