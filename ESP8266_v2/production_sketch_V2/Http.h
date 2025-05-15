#ifndef HTTP_H
#define HTTP_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Configuration
#define STATUS_LED_PIN D4
#define MAX_RETRIES 15
#define RESTART_CYCLE 2500

// Relay pin map
const int RELAY_PINS[6] = {D1, D2, D5, D6, D7, D8};
const char* API_URL = "http://128.199.192.199/api/user_route/instruction/get_instruction?mac_address=00:00:00:00:00:01";

// Global flags and counters
extern bool isIdle;
extern int request_cycle;
extern int previous_data;

void http_initialize(const char* wireless_ssid, const char* password);
void http_handle();
void update_relay(bool states[], int len);
void convert_decimal_to_binary(int decimal, bool* bits_out);

#endif