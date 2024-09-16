#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "./wireless_connection.h"
#include "./flash.h"

void wireless_connection_initialize(const char* wifi_ssid, const char* wifi_password) {
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    ++initial_state;
    Serial.println("Connecting to WiFi...");
    connection_start_flash();
    if (initial_state == 25) {
      initial_state = 0;
      break;
    }
  }
  if (initial_state == 0) {
    Serial.print("Unable connect to the WiFi network");
    connection_lost_flash();
    delay(5000);
    ESP.restart();
  }
  else {
    Serial.println("Connected to the WiFi network");
    connection_success_flash();
  }
}
