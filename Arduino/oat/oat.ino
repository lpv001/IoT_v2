#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoOTA.h>

const char * wifi_ssid = "PozzVenhh";
const char * wifi_password = "012286451";

int initial_state = 0;

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  WiFi.begin(wifi_ssid, wifi_password);
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

void loop() {


  ArduinoOTA.handle();
  digitalWrite(2, LOW);

}
