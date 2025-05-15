#include "MEMORY.h"
#include "WEBSERVERHANDLER.h"
#include "WEBSERVERDECORATION.h"
#include "HTTP.h"

const char* DEFAULT_SSID = "kasegro";
const char* DEFAULT_PASSWORD = "myfarm@123";

const char* AP_SSID = "MyESP_AP";
const uint8_t LED_PIN = D4;
WebServerHandler myWebServer(AP_SSID, LED_PIN);

bool processState = true;

void setup() {
  pinMode(0, INPUT_PULLUP);
  Serial.begin(115200);
  delay(1000);
  processState = digitalRead(0);

  MEMORY::initialize(512, LED_PIN);
  delay(10);

  if (processState) {
    String ssid = MEMORY::readString(0, 32);   // assumes EEPROM stores SSID at 0–31
    String pass = MEMORY::readString(32, 96);  // assumes EEPROM stores password at 32–95
    if (ssid.length() < 1 || pass.length() < 1) {
      ssid = DEFAULT_SSID;
      pass = DEFAULT_PASSWORD;
    }
    http_initialize(ssid.c_str(), pass.c_str());
    delay(10);
  } else {

    myWebServer.setIndexHTML(H + INDEX_BODY);
    myWebServer.setPostHTML(H + POST_BODY);
    myWebServer.begin();
    delay(10);
  }
}

void loop() {
  if (processState)
    http_handle();
  else
    myWebServer.handle();
}
