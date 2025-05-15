#include "MEMORY.h"
#include <EEPROM.h>

static int _eepromSize = 512;
static uint8_t _ledPin = LED_BUILTIN;

void MEMORY::initialize(int size, uint8_t ledPin) {
    _eepromSize = size;
    _ledPin = ledPin;
    EEPROM.begin(_eepromSize);
    pinMode(_ledPin, OUTPUT);
    digitalWrite(_ledPin, HIGH);
    delay(10);
}

void MEMORY::clean() {
    for (int i = 0; i < _eepromSize; i++) EEPROM.write(i, 0);
    EEPROM.commit();
}

void MEMORY::writeString(int start, int end, const String& data) {
    int len = end - start;
    for (int i = 0; i < len; i++) {
        if (i < data.length())
            EEPROM.write(start + i, data[i]);
        else
            EEPROM.write(start + i, 0);
    }
    EEPROM.commit();

    for (int i = 0; i < 5; i++) {
        digitalWrite(_ledPin, LOW);
        delay(300);
        digitalWrite(_ledPin, HIGH);
        delay(300);
    }
}

String MEMORY::readString(int start, int end) {
    String data = "";
    for (int i = start; i < end; i++) {
        char c = EEPROM.read(i);
        if (c == 0) break;
        data += c;
    }
    return data;
}

void MEMORY::saveWiFi(const String& ssid, const String& pass) {
    clean();
    writeString(0, 32, ssid);
    writeString(32, 96, pass);

    for (int i = 0; i < 10; i++) {
        digitalWrite(_ledPin, LOW);
        delay(300);
        digitalWrite(_ledPin, HIGH);
        delay(300);
    }
}
