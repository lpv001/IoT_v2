#include "./decoration.h"
#include "./eeprom.h"
#include "./webserver.h"
#include "./http.h"

String username = "IOT";
String password = "12345678";

bool processState = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(0, INPUT_PULLUP);
  Serial.begin(115200);
  delay(3000);
  processState = digitalRead(0);
  Serial.println(processState);
  eeprom_initialize();
  if (processState) {
    http_initialize(read_from_memory(0, 32).c_str(), read_from_memory(32, 100).c_str());
  } else {
    webserver_initialize();
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  if (processState) {
    http_loop();
  } else {
    webserver_loop();
  }
}
