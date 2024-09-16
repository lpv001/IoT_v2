#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

// Wi-Fi connection parameters
const char * wifi_ssid = "PozzVenhh";
const char * wifi_password = "012286451";

int ledState = LOW; 
unsigned long previousMillis = 0;    
const long interval = 1000;

void setup() {
  Serial.begin(9600);
  Serial.println("Booting...");
  connectToWiFi();
  setUpOverTheAirProgramming();
  pinMode(2, OUTPUT);
}

void connectToWiFi() {
  Serial.printf("Connecting to '%s'\n", wifi_ssid);

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
  // ArduinoOTA.setHostname("myesp8266");

  // Re-programming passowrd. 
  // No password by default.
  // ArduinoOTA.setPassword("123");

  ArduinoOTA.begin();
}


void loop() {
  // Give processing time for ArduinoOTA
  ArduinoOTA.handle();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(2, ledState);
  }
}
