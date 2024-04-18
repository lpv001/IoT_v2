#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

#define LED_PIN D5
const char* ssid = "PozzVenhh";
const char* password = "012286451";


int initial_state = 0;
int counter = 0;

int a[8];

int previous_data = 333;
bool isIDLE = false;
bool c1 = false, c2 = false, c3 = false, c4 = false, c5 = false, c6 = false, c7 = false, c8 = false;

void setup() {
  // Start the I2C Bus as Master

  Serial.begin(9600);
  delay(4000);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  digitalWrite(D4, HIGH);

  update_relay(false, false, false, false, false, false, false, false);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    ++initial_state;
    Serial.println("Connecting to WiFi..");
    if (initial_state == 15) {
      initial_state = 0;
      break;
    }
  }

  for (int i = 0; i < 8; ++i) {
    a[i] = 0;
    delay(10);
  }

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  Serial.println("Connected to the WiFi network");
}

void loop() {

  if ((WiFi.status() == WL_CONNECTED)) {  //Check the current connection status
    WiFiClient client;
    HTTPClient http;

    if (http.begin(client, "http://128.199.192.199/api/user_route/instruction/get_instruction?mac_address=00:00:00:00:00:01") > 0) {  //Specify the URL
      digitalWrite(D4, LOW);
      int httpCode = http.GET();

      if (httpCode != 200) {
        for (int j = 0; j < 5; ++j) {
          digitalWrite(D4, HIGH);
          delay(100);
          digitalWrite(D4, LOW);
          delay(100);
        }
        if (!isIDLE) {
          isIDLE = true;
          update_relay(false, false, false, false, false, false, false, false);
          Serial.println("API Request Fail");
        }
      }

      String payload = http.getString();
      //      Serial.println(httpCode);
      // Serial.println(payload);

      //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
      unsigned int data = payload.toInt();

      if (httpCode == 200) {
        if (data != previous_data) {
          previous_data = data;
          convery_decimal_to_binary(data);

          update_relay(c1, c2, c3, c4, c5, c6, c7, c8);
          Serial.println("Updated Relay");
          // Serial.print(previous_data);
          // Serial.print(" ");
          // Serial.print(data);
        }
      }
      //-----------------------------------------------------------------------------------------------------------------------------------------------------------------


      //      Serial.println(counter);

      delay(4000);
    }

    digitalWrite(D4, HIGH);
    delay(1000);
    http.end();  //Free the resources
  } else {

    if (!isIDLE) {
      isIDLE = true;
      update_relay(false, false, false, false, false, false, false, false);
      Serial.println("lost connection");
      digitalWrite(D4, HIGH);
    }
  }
}

void update_relay(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) {

  digitalWrite(D1, a1);
  digitalWrite(D2, a2);

  digitalWrite(D5, a3);
  digitalWrite(D6, a4);
  digitalWrite(D7, a5);
  digitalWrite(D8, a6);
}

void convery_decimal_to_binary(int decimal) {

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
