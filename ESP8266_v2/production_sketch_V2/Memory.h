#ifndef MEMORY_H
#define MEMORY_H

#include <Arduino.h>

class MEMORY {
public:
    static void initialize(int size, uint8_t ledPin);
    static void clean();
    static void writeString(int start, int end, const String& data);
    static String readString(int start, int end);
    static void saveWiFi(const String& ssid, const String& pass);
};

#endif
