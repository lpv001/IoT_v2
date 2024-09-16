#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "./wireless_connection.h"

void wireless_connection_initialize(const char* wifi_ssid, const char* wifi_password) {
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    ++initial_state;
    Serial.println("Connecting to WiFi...");
    if (initial_state == 18) {
      initial_state = 0;
      ESP.deepSleep(62e7);
      break;
    }
  }
  if (initial_state == 0) Serial.print("Unable connect to the WiFi network");
  else Serial.println("Connected to the WiFi network");
}
