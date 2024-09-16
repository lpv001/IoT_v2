#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "./https.h"

int https_get_request(const char* serverName) {
  int value = -1;
  if ((WiFi.status() == WL_CONNECTED)) {
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;
    https.setTimeout(10000);
    Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, serverName)) {
      Serial.print("[HTTPS] GET...\n");
      int httpCode = https.GET();
      if (httpCode > 0) {
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          unsigned int data = payload.toInt();
          value = data;
        } else {
          Serial.printf("[HTTPS] Server Busy or Something Went Wrong.");
        }

      } else {
        // 404 not found or no response
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    } else {
      // 500 internal error
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }
  return value;
}
