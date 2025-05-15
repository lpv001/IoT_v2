#ifndef WEBSERVERHANDLER_H
#define WEBSERVERHANDLER_H

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

class WebServerHandler {
public:
    WebServerHandler(const char* apSSID, uint8_t ledPin, IPAddress apIP = IPAddress(172,0,0,1), uint16_t dnsPort = 53, uint16_t webPort = 80);

    void begin();
    void handle();

    // Set the HTML templates
    void setIndexHTML(const String& html);
    void setPostHTML(const String& html);

private:
    const char* _apSSID;
    uint8_t _ledPin;
    IPAddress _apIP;
    uint16_t _dnsPort;
    uint16_t _webPort;

    DNSServer _dnsServer;
    ESP8266WebServer _webServer;

    String _indexHTML;
    String _postHTML;

    // HTTP response code (usually 200)
    const int HTTP_OK = 200;

    // Handler functions
    void handleNotFound();
    void handlePost();
};

#endif
