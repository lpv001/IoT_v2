//#include "DHT.h"
//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
//#include <WiFiClient.h>
//#include <ArduinoOTA.h>
//
//
//#define DHTPIN D2
//#define VCCPIN D1
//#define DHTTYPE DHT11
//
//DHT dht(DHTPIN, DHTTYPE);
//
//
//const char * wifi_ssid = "PozzVenhh";
//const char * wifi_password = "012286451";
//
//const char* serverName = "http://128.199.192.199/api/user_route/sensor/load_data";
//
//
//unsigned long lastTime = 0;
//unsigned long timerDelay = 60000;
//
//int initial_state = 0;
//
//float humidity = 0;
//float temperature = 0;
//
//void setup() {
//
//  Serial.begin(9600);
//
//  dht.begin();
//
//  connectToWiFi();
//  setUpOverTheAirProgramming();
//
//  pinMode(VCCPIN, OUTPUT);
//
//}
//
//void loop() {
//
//  ArduinoOTA.handle();
//  digitalWrite(VCCPIN, 1);
//  delay(1000);
//  float h = dht.readHumidity();
//  float t = dht.readTemperature();
//  delay(1000);
//  if (!isnan(h) || !isnan(t)) {
//    humidity = h;
//    temperature = t;
//    digitalWrite(VCCPIN, 0);
//  }
//
//  WiFiClient client;
//  HTTPClient http;
//
//  String urlString = "device_id=2&temperature=" + String(h) + "&humidity=" + String(t);
//  http.begin(client, serverName);
//  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//
//  int httpResponseCode = http.POST(urlString);
//  Serial.print("HTTP Response code: ");
//  Serial.println(httpResponseCode);
//
//
//  http.end();
//
//  ESP.deepSleep(20e6);
//
//}
//
//void connectToWiFi() {
//  WiFi.mode(WIFI_STA);
//  WiFi.begin(wifi_ssid, wifi_password);
//  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
//    Serial.print("Connected. IP: ");
//    Serial.println(WiFi.localIP());
//  } else {
//    Serial.println("Connection Failed!");
//  }
//}
//
//void setUpOverTheAirProgramming() {
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



#include "DHT.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoOTA.h>


#define DHTPIN D2
//#define VCCPIN D1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


const char * wifi_ssid = "PozzVenhh";
const char * wifi_password = "012286451";

const char* serverName = "http://128.199.192.199/api/user_route/sensor/load_data";


unsigned long lastTime = 0;
unsigned long timerDelay = 60000;

bool state = false;

void setup() {
  Serial.begin(9600);

  dht.begin();

  connectToWiFi();
  setUpOverTheAirProgramming();
  if ( digitalRead(D0) == 0 ) {
    pinMode(2, OUTPUT);
    state = true;
  }

}

void loop() {

  if (state) {
    ArduinoOTA.handle();
    digitalWrite(2, LOW);
  } else {

    float h = dht.readHumidity();
    float t = dht.readTemperature();
    delay(10);
    Serial.println(t);
    if (!isnan(h) || !isnan(t)) {
      WiFiClient client;
      HTTPClient http;

      String urlString = "device_id=2&temperature=" + String(t) + "&humidity=" + String(h);
      http.begin(client, serverName);
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      int httpResponseCode = http.POST(urlString);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);


      http.end();

      if (httpResponseCode == 200) {
        ESP.deepSleep(360e6);
      }
      
    }
    ESP.deepSleep(180e6);

  }
}

void connectToWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);
  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
    Serial.print("Connected. IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Connection Failed!");
  }
}

void setUpOverTheAirProgramming() {

  // Change OTA port.
  // Default: 8266
  // ArduinoOTA.setPort(8266);

  // Change the name of how it is going to
  // show up in Arduino IDE.
  // Default: esp8266-[ChipID]
  ArduinoOTA.setHostname("myesp8266");

  // Re-programming passowrd.
  // No password by default.
  // ArduinoOTA.setPassword("123");

  ArduinoOTA.begin();
}
