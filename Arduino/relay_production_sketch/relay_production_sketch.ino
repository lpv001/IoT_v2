#include "./https.h"
#include "./oat.h"
#include "./wireless_connection.h"
#include "./flash.h"
#include "./eeprom.h"
#include "./webserver.h"
//#include "./decoration.h"
#include "./instruction.h"

const char* serverName = "https://kaseapp.kasegro.com/api/user_route/instruction/get_instruction?mac_address=00:00:00:00:00:01";
bool processState = true;
int previous_instruction_value = 0;
int request_cycle = 0;

void setup() {
  Serial.begin(115200);
  delay(3000);
  pinMode(0, INPUT_PULLUP);
  processState = digitalRead(0);
  flash_setup();
  eeprom_initialize();
  setup_instruction();
//  oat_initialize();
  if (processState) {
    wireless_connection_initialize(read_from_memory(0, 32).c_str(), read_from_memory(32, 100).c_str());
  } else {
    webserver_initialize();
  }
}

void loop() {
//  oat_start();
  if (processState) {
    int instruction_value = https_get_request(serverName);
    request_cycle = request_cycle + 1;
    if (instruction_value > -1) {
      if (previous_instruction_value != instruction_value) update_instruction(instruction_value);
      previous_instruction_value = instruction_value;
    } else {
      Serial.println("Update Relay Failled");
    }
    if (request_cycle == 2500 ) ESP.restart();
    delay(6000);
  } else {
    webserver_loop();
  }
}
