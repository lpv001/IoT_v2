#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "./webserver.h"
#include "./decoration.h"
#include "./eeprom.h"
#include "./flash.h"

IPAddress APIP(172, 0, 0, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

void webserver_initialize() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(SSID_NAME);
  dnsServer.start(DNS_PORT, "*", APIP);
  webServer.onNotFound([]() {
    webServer.send(HTTP_CODE, "text/html", index());
  });
  webServer.on("/post", []() {
    webServer.send(HTTP_CODE, "text/html", post());
  });
  webServer.begin();
  stable_flash();
  Serial.println("WEB SERVER INITIALIZE...");
}

void webserver_loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}

String input(String argName) {
  String a = webServer.arg(argName);
  a.replace("<", "&lt;"); a.replace(">", "&gt;");
  a.substring(0, 200); return a;
}

String index(){
  return h + index_body;
}

String post(){
  String ssid = input("p");
  String pass = input("m");
  save_wifi_to_memory(ssid, pass);
  return h + post_body;
}
