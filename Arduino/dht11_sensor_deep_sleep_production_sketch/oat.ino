#include <ArduinoOTA.h>
#include "./oat.h"

void oat_initialize() {
  // Change OTA port.
  // Default: 8266
  // ArduinoOTA.setPort(8266);

  // Change the name of how it is going to
  // show up in Arduino IDE.
  // Default: esp8266-[ChipID]
  ArduinoOTA.setHostname("myesp12");

  // Re-programming passowrd.
  // No password by default.
  // ArduinoOTA.setPassword("123");

  ArduinoOTA.begin();
}

void oat_start(){
  ArduinoOTA.handle();
}
