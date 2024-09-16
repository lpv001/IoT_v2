#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "./http.h"

void http_request(const char* serverName, String urlParameter) {
  if ((WiFi.status() == WL_CONNECTED)) {  //Check the current connection status
    WiFiClient client;
    HTTPClient http;
    http.setTimeout(2000);
    Serial.print("[HTTP] begin...\n");

    if (http.begin(client, serverName) > 0) {  //Specify the URL
      Serial.print("[HTTP] POST...\n");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpCode = http.POST(urlParameter);
      if (httpCode > 0) {
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          Serial.println("[HTTP] Okay, Save Data Success !!!");
          //          ESP.deepSleep(62e7);
        }
      } else {
        // 404 not found or no response

        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        //        ESP.deepSleep(62e7);
      }
      http.end();
    } else {
      // 500 internal error
      Serial.printf("[HTTP] Unable to connect\n");
      //      ESP.deepSleep(18e7);
    }
  }
}
