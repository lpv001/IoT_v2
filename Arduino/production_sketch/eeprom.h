#ifndef EEPROM_H
#define EEPROM_H

int eeprom_size = 512;

void eeprom_initialize(void);
void clean_up_memory(void);
void write_to_memory(int start_address, int end_address, String data);
void save_wifi_to_memory(String ssid, String pass);
String read_from_memory(int start_address, int end_address);

#endif
