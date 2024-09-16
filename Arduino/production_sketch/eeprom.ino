#include <EEPROM.h>
#include "./eeprom.h"

void eeprom_initialize() {
  EEPROM.begin(eeprom_size);
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);
  delay(10);
}

void clean_up_memory() {
  for ( int i = 0; i < eeprom_size ; ++i ) EEPROM.write(i, 0x00);
}

void write_to_memory(int start_address, int end_address, String data) {
  for ( int i = start_address; i < end_address ; ++i ) EEPROM.write(i, data[i]);
  EEPROM.commit();
  for (int counter = 0; counter < 5; counter++)
  {
    // For blinking the LED.
    digitalWrite(D4, LOW);
    delay(300);
    digitalWrite(D4, HIGH);
    delay(300);
  }
}

void save_wifi_to_memory(String ssid, String pass) {
  for ( int i = 0; i < 100 ; ++i ) EEPROM.write(i, 0x00);
  for ( int i = 0; i < ssid.length() ; ++i ) EEPROM.write(i, ssid[i]);
  for ( int i = 0; i < pass.length() ; ++i ) EEPROM.write(32 + i, pass[i]);
  EEPROM.commit();
  for (int counter = 0; counter < 10; counter++)
  {
    // For blinking the LED.
    digitalWrite(D4, LOW);
    delay(300);
    digitalWrite(D4, HIGH);
    delay(300);
  }
}

String read_from_memory(int start_address, int end_address) {
  String data = "";
  for ( int i = start_address; i < end_address; ++i) data += char(EEPROM.read(i));
  return data;
}
