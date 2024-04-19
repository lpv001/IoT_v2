#ifndef WEBSERVER_H
#define WEBSERVER_H

const char* SSID_NAME = "Free WiFi";
const byte DNS_PORT = 53;
const byte HTTP_CODE = 200;

void webserver_initialize(void);
void webserver_loop(void);
String input(String parameter);

String index();
String post();

#endif
