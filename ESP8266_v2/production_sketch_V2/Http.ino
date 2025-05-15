#include "./http.h"

bool isIdle = false;
int request_cycle = 0;
int previous_data = -1;
int initial_state = 0;

void http_initialize(const char* wireless_ssid, const char* password) {
  for (int i = 0; i < 6; ++i) {
    pinMode(RELAY_PINS[i], OUTPUT);
  }

  pinMode(STATUS_LED_PIN, OUTPUT);
  digitalWrite(STATUS_LED_PIN, HIGH);

  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  WiFi.begin(wireless_ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    ++initial_state;
    Serial.println("Connecting to WiFi...");
    if (initial_state >= MAX_RETRIES) {
      Serial.println("Unable to connect to the WiFi network. Restarting...");
      delay(5000);
      ESP.restart();
    }
  }

  Serial.println("Connected to WiFi.");
}

void http_handle() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    http.setTimeout(20000);
    request_cycle++;


    Serial.println("[HTTP] begin...");

    if (http.begin(client, API_URL)) {
      Serial.println("[HTTP] GET...");
      int httpCode = http.GET();

      if (httpCode > 0) {
        Serial.printf("[HTTP] GET code: %d\n", httpCode);

        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          unsigned int data = payload.toInt();

          if (data != previous_data) {
            previous_data = data;
            bool bit_states[8] = { 0 };
            convert_decimal_to_binary(data, bit_states);
            update_relay(bit_states, 6);
            Serial.println("Relay states updated.");
          }
        }
      } else {
        Serial.printf("[HTTP] failed, error: %s\n", http.errorToString(httpCode).c_str());
        for (int j = 0; j < 15; ++j) {
          digitalWrite(STATUS_LED_PIN, HIGH);
          delay(100);
          digitalWrite(STATUS_LED_PIN, LOW);
          delay(100);
        }
        digitalWrite(STATUS_LED_PIN, HIGH);
      }

      http.end();
    } else {
      Serial.println("[HTTP] Unable to connect");
      for (int j = 0; j < 4; ++j) {
        digitalWrite(STATUS_LED_PIN, HIGH);
        delay(500);
        digitalWrite(STATUS_LED_PIN, LOW);
        delay(500);
      }
      digitalWrite(STATUS_LED_PIN, HIGH);
    }
  }

  if (isIdle && request_cycle >= RESTART_CYCLE) {
    Serial.println("Idle timeout. Restarting...");
    ESP.restart();
  }

  Serial.println();
  delay(6000);
}

void update_relay(bool states[], int len) {
  isIdle = true;
  for (int i = 0; i < len; ++i) {
    digitalWrite(RELAY_PINS[i], states[i]);
    if (states[i]) isIdle = false;
  }
}

void convert_decimal_to_binary(int decimal, bool* bits_out) {
  for (int i = 0; i < 8; ++i) {
    bits_out[i] = (decimal >> i) & 1;
    Serial.print(bits_out[i]);
    Serial.print(" ");
  }
  Serial.println();
}