#ifndef HTTP_H
#define HTTP_H

int initial_state = 0;
int a[8];
bool c1 = false, c2 = false, c3 = false, c4 = false, c5 = false, c6 = false, c7 = false, c8 = false;
int previous_data = 999;
int request_cycle = 0;
bool isIdle = false;

void http_initialize(const char* wireless_ssid, const char* password);
void http_loop(void);
void update_relay(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8);
void convert_decimal_to_binary(int decimal);

#endif
