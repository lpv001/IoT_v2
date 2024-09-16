//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
//#include <WiFiClient.h>
//#include <ArduinoOTA.h>
//#include "DHT.h"
//#include "./wireless_connection.h"
//
//#define DHTPIN D7
//#define DHTTYPE DHT11
//DHT dht(DHTPIN, DHTTYPE);
//
//const char * wifi_ssid = "iPhone12";
//const char * wifi_password = "myfarm@123";
//const char* serverName = "http://128.199.192.199/api/user_route/sensor/load_data";
//
//
//void setup() {
//  Serial.begin(115200);
//  dht.begin();
//
//  wireless_connection_initialize(wifi_ssid, wifi_password);
//
//  // Change OTA port.
//  // Default: 8266
//  // ArduinoOTA.setPort(8266);
//
//  // Change the name of how it is going to
//  // show up in Arduino IDE.
//  // Default: esp8266-[ChipID]
//  ArduinoOTA.setHostname("myesp8266");
//
//  // Re-programming passowrd.
//  // No password by default.
//  // ArduinoOTA.setPassword("123");
//
//  ArduinoOTA.begin();
//}
//
//void loop() {
//
//
//  ArduinoOTA.handle();
//  float h = dht.readHumidity();
//  float t = dht.readTemperature();
//  delay(10);
//  Serial.println(t);
//  delay(1000);
//
//}

#include "./capacitive_v12.h"
#include "./http.h"
#include "./oat.h"
#include "./wireless_connection.h"
#include "./flash.h"
#include "./https.h"

const char* serverName = "https://kaseapp.kasegro.com/api/user_route/sensor/load_data";
const char* wifi_ssid = "kasegro";
const char* wifi_password = "myfarm@123";

int request_cycle = 0;

void setup() {
  Serial.begin(115200);
  oat_initialize();
  flash_setup();
  wireless_connection_initialize(wifi_ssid, wifi_password);
}

void loop() {
  oat_start();
  int data = getMoisture();
  float voltage = data / 765.0;
  int sensorUnits = 100 - voltage * 100;
  if ( sensorUnits < 0 ) sensorUnits = 0;

  String urlString = "mac_address=22:00:00:00:00:01&soil=" + String(sensorUnits);
  https_post_request(serverName, urlString);
  request_cycle = request_cycle + 1;
  if (request_cycle == 2500) ESP.restart();
}
