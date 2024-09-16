#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "./https.h"
#include "./flash.h"

void https_post_request(const char* serverName, String urlParameter) {
  if ((WiFi.status() == WL_CONNECTED)) {  //Check the current connection status
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;
    //    https.setTimeout(2000);
    Serial.print("[HTTP] begin...\n");

    if (https.begin(*client, serverName) > 0) {  //Specify the URL
      Serial.print("[HTTP] POST...\n");
      https.addHeader("Content-Type", "application/x-www-form-urlencoded");
      int httpCode = https.POST(urlParameter);
      if (httpCode > 0) {
        Serial.printf("[HTTP] POST... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          Serial.println("[HTTP] Okay, Save Data Success !!!");
          post_success();
          delay(5000);
//          ESP.deepSleep(128e7);
        } else {
          // if the server is busy
          delay(2500);
//          ESP.deepSleep(62e7);
        }
      } else {
        // 404 not found or no response
        Serial.printf("[HTTP] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
        delay(5000);
//        ESP.deepSleep(128e7);
      }
      https.end();
    } else {
      // 500 internal error
      Serial.printf("[HTTP] Unable to connect\n");
      delay(2500);
//      ESP.deepSleep(62e7);
    }
  }
}
