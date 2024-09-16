#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

// Replace with your network credentials
const char* ssid = "PozzVenhh";
const char* password = "012286451";

int initial_state = 0;
int a[8];
bool c1 = false, c2 = false, c3 = false, c4 = false, c5 = false, c6 = false, c7 = false, c8 = false;
int previous_data = 999;
int request_cycle = 0;
bool isIdle = false;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();
  Serial.println();
  Serial.println();

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  digitalWrite(D4, HIGH);
  //Connect to Wi-Fi

  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    ++initial_state;
    Serial.println("Connecting to WiFi...");
    if (initial_state == 15) {
      initial_state = 0;
      break;
    }
  }
  if (initial_state == 0) {
    Serial.print("Unable connect to the WiFi network");
    delay(5000);
    ESP.restart();
  }
  else Serial.println("Connected to the WiFi network");
}

void loop() {
  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;
    https.setTimeout(20000);
    Serial.print("[HTTPS] begin...\n");
    request_cycle = request_cycle + 1;
    if (https.begin(*client, "https://smartfarm.kasegro.com/api/instructions/?mac_address=2")) {
      Serial.print("[HTTPS] GET...\n");
      int httpCode = https.GET();
      if (httpCode > 0) {
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          unsigned int data = payload.toInt();
          if (data != previous_data) {
            previous_data = data;
            convert_decimal_to_binary(data);
            update_relay(c1, c2, c3, c4, c5, c6, c7, c8);
            Serial.println("Update relay successful");
          }
        }
        Serial.println("[HTTPS] Okay");
      } else {
        // 500 internal error
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        for (int j = 0; j < 15; ++j) {
          digitalWrite(D4, HIGH);
          delay(100);
          digitalWrite(D4, LOW);
          delay(100);
        }
        digitalWrite(D4, HIGH);
      }
      https.end();
    } else {
      // 404 not found or no response
      Serial.printf("[HTTPS] Unable to connect\n");
      for (int j = 0; j < 4; ++j) {
        digitalWrite(D4, HIGH);
        delay(500);
        digitalWrite(D4, LOW);
        delay(500);
      }
      digitalWrite(D4, HIGH);
    }
  }

  if ( isIdle && request_cycle == 2500 ) ESP.restart();

  Serial.println();
  delay(6000);
}


void update_relay(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {
  if (!a1 && !a2 && !a3 && !a4 && !a5 && !a6 && !a7 && !a8) isIdle = true;
  digitalWrite(D1, a1);
  digitalWrite(D2, a2);
  digitalWrite(D5, a3);
  digitalWrite(D6, a4);
  digitalWrite(D7, a5);
  digitalWrite(D8, a6);
}
void convert_decimal_to_binary(int decimal) {
  for (int i = 0; decimal > 0; ++i) {
    a[i] = decimal % 2;
    decimal = decimal / 2;
    delay(10);
  }
  if (a[0] == 1) {
    c1 = true;
  } else {
    c1 = false;
  }

  if (a[1] == 1) {
    c2 = true;
  } else {
    c2 = false;
  }

  if (a[2] == 1) {
    c3 = true;
  } else {
    c3 = false;
  }

  if (a[3] == 1) {
    c4 = true;
  } else {
    c4 = false;
  }

  if (a[4] == 1) {
    c5 = true;
  } else {
    c5 = false;
  }

  if (a[5] == 1) {
    c6 = true;
  } else {
    c6 = false;
  }

  if (a[6] == 1) {
    c7 = true;
  } else {
    c7 = false;
  }
  if (a[7] == 1) {
    c8 = true;
  } else {
    c8 = false;
  }
  for (int i = 0; i < 8; ++i) {
    Serial.print(a[i]);
    Serial.print(" ");
    a[i] = 0;
    delay(10);
  }
  Serial.println();
}
