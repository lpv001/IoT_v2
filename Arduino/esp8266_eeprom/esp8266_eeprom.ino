#include <EEPROM.h>
#include <ESP8266WiFi.h>

// simple variable
int initial_state = 0;

// eeprom
String esid = "";
String epass = "";
int eeprom_size = 512;

String a = "PozzVenhh";
String b = "012286451";

void setup() {
  Serial.begin(115200);
  delay(100);
  EEPROM.begin(eeprom_size);
  delay(10);

  Serial.println("Writing to EEPROM");
  for ( int i = 0; i < eeprom_size ; ++i ) EEPROM.write(i, 0x00);
  for ( int i = 0; i < a.length() ; ++i ) EEPROM.write(i, a[i]);
  for ( int i = 0; i < b.length() ; ++i ) EEPROM.write(32 + i, b[i]);
  EEPROM.commit();
  delay(100);
  Serial.println("Wrote to EEPROM");

  Serial.println("Startup");
  Serial.println("Reading EEPROM ssid");
  for ( int i = 0; i < 32; ++i) esid += char(EEPROM.read(i));
  Serial.println();
  Serial.print("SSID: ");
  delay(10);
  Serial.println(esid.c_str());
  Serial.println("Reading EEPROM pass");
  for ( int i = 32; i < 96; ++i) epass += char(EEPROM.read(i));
  Serial.print("PASS: ");
  Serial.println(epass.c_str());



  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  WiFi.begin(esid.c_str(), epass.c_str());
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
    delay(1000);
    ESP.restart();
  }
  else Serial.println("Connected to the WiFi network");
}

void loop() {

}
