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
cmd+= "<html lang='en'><head><meta http-equiv='refresh' content='3' name='viewport' content='width=device-width, initial-scale=1'/>";
cmd+=   "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js'></script><script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>";
cmd+=   "<title>Green House</title></head><body>";
cmd+=     "<div class='row'>";
cmd+=      "<div class='col-md-12'>";
cmd+=         "<div class='btn-group'>";
cmd+=           "<div class ='container'>";
cmd+=         "<h1>IOT Based Green House Monitoring System</h1>";
cmd+=         "<h3> Mode selection</h3>";
cmd+= "<a href=\'dev1=1\' button type='button' class='btn btn-success'>Automatic</button></a> <a href=\'dev1=0\' button type='button' class='btn btn-primary'>Manual</button></a> <a href=\'dev5=1\' button type='button' class='btn btn-success'>GET READING</button></a>";
cmd+=           "<h3> </h3>";
cmd+=           "</li>";
cmd+=        "</ul>";
cmd+=         "<table class='table table-bordered'>";
cmd+=           "<thead><tr class='active'><th>Mode</th><th>" + param1 + "</th>";
cmd+=           "<tbody>";
cmd+=             "<tr><td>Temperature</td><td>" + param2 + "&deg;C</td>";
cmd+=             "<tr class='active'><td>Humidity</td><td>" + param3 + "%</td>";
cmd+=             "<tr><td>Moisture</td><td>" + param5 + " %</td>";
cmd+=               "<tr class='active'><td>Light</td><td>" + param4 + " %</td>";
cmd+=         "</tbody></table>";
cmd+=         "<h3>Manual control</h3>";
cmd+=         "<div class='row'>";
cmd+=           "<div class='col-md-4'><h4 class ='text-left'>FAN";
cmd+=             "<span class='badge'>";
cmd+=             "control";
cmd+=           "</span></h4></div>";
cmd+=            "<div class='col-md-4'><form action=\"dev2=1\" method='POST'><button type='button submit' class='btn btn-success btn-lg'>ON</button></form></div>"; 
cmd+=            "<div class='col-md-4'><form action=\"dev2=0\" method='POST'><button type='button submit' class='btn btn-danger btn-lg'>OFF</button></form></div>";       
cmd+=                "<div class='col-md-4'><h4 class ='text-left'>PUMP";
cmd+=             "<span class='badge'>";
cmd+=             "control";
cmd+=           "</span></h4></div>";
cmd+=           "<div class='col-md-4'><form action=\"dev3=1\" method='POST'><button type='button submit' class='btn btn-success btn-lg'>ON</button></form>"; 
cmd+=           "</div><div class='col-md-4'><form action=\"dev3=0\" method='POST'><button type='button submit' class='btn btn-danger btn-lg'>OFF</button></form></div>";
cmd+=               "<div class='col-md-4'><h4 class ='text-left'>LAMB";
cmd+=             "<span class='badge'>";
cmd+=             "control";
cmd+=           "</span></h4></div>";
cmd+=           "<div class='col-md-4'><form action=\"dev4=1\" method='POST'><button type='button submit' class='btn btn-success btn-lg'>ON</button></form></div>";
cmd+=           "<div class='col-md-4'><form action=\"dev4=0\" method='POST'><button type='button submit' name='D7' value='0' class='btn btn-danger btn-lg'>OFF</button></form></div>";
cmd+=         "</div>";
cmd+=   "</div></div></div></div>";
cmd+=   "</body></html>";
server.send(200, "text/html", cmd);
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {

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
  server.on("/dev5=1",[](){
    Serial.print("*N");
    server.send(200, "text/plain", "READING");
  });

  server.on("/dev1=1", []() {
    Serial.print("*Q");
    server.send(200, "text/plain", "MODE: AUTO");
  });

  server.on("/dev1=0", []() {
    Serial.print("*C");
    server.send(200, "text/plain", "MODE : MANUAL");
  });
  server.on("/dev2=1", []() {
    Serial.print("*B");
    server.send(200, "text/plain", "FAN : ON");
  });

  server.on("/dev2=0", []() {
    Serial.print("*b");
    server.send(200, "text/plain", "FAN :  OFF");
  });
  server.on("/dev3=1", []() {
    Serial.print("*X");
    server.send(200, "text/plain", "PUMB : ON");
  });

  server.on("/dev3=0", []() {
    Serial.print("*R");
    server.send(200, "text/plain", "PUMB :  OFF");
  });
  server.on("/dev4=1", []() {
    Serial.print("*L");
    server.send(200, "text/plain", "LAMB : ON");
  });

  server.on("/dev4=0", []() {
    Serial.print("*V");
    server.send(200, "text/plain", "LAMB :  OFF");
  });

  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();

  // Read serial
  if (Serial.available() > 0) {
    String rcvd = Serial.readString();
    Serial.print("Serial received: ");
    Serial.println(rcvd);
    param1 = rcvd.substring(1, 2);
    param2 = rcvd.substring(2, 4);
    param3 = rcvd.substring(4, 6);
    param4 = rcvd.substring(6, 9);
    param5 = rcvd.substring(9);
  }
}


