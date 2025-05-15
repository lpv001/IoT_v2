#include "WEBSERVERHANDLER.h"
#include "MEMORY.h"  // Your EEPROM functions, e.g. save_wifi_to_memory()
#include <Arduino.h>

WebServerHandler::WebServerHandler(const char* apSSID, uint8_t ledPin, IPAddress apIP, uint16_t dnsPort, uint16_t webPort)
    : _apSSID(apSSID),
      _ledPin(ledPin),
      _apIP(apIP),
      _dnsPort(dnsPort),
      _webPort(webPort),
      _dnsServer(),
      _webServer(webPort)
{
    // empty constructor body
}

void WebServerHandler::begin() {
    pinMode(_ledPin, OUTPUT);
    digitalWrite(_ledPin, HIGH);

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(_apIP, _apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(_apSSID);

    _dnsServer.start(_dnsPort, "*", _apIP);

    // Setup web server routes
    _webServer.onNotFound([this]() { this->handleNotFound(); });
    _webServer.on("/post", [this]() { this->handlePost(); });

    _webServer.begin();

    digitalWrite(_ledPin, LOW);
    Serial.println("WEB SERVER INITIALIZED...");
}

void WebServerHandler::handle() {
    _dnsServer.processNextRequest();
    _webServer.handleClient();
}

void WebServerHandler::setIndexHTML(const String& html) {
    _indexHTML = html;
}

void WebServerHandler::setPostHTML(const String& html) {
    _postHTML = html;
}

void WebServerHandler::handleNotFound() {
    _webServer.send(HTTP_OK, "text/html", _indexHTML);
}

void WebServerHandler::handlePost() {
    // sanitize input helper
    auto sanitizeInput = [this](const String& argName) -> String {
        String val = _webServer.arg(argName);
        val.replace("<", "&lt;");
        val.replace(">", "&gt;");
        return val.substring(0, 200);
    };

    String ssid = sanitizeInput("p");
    String pass = sanitizeInput("m");

    MEMORY::saveWiFi(ssid, pass);

    _webServer.send(HTTP_OK, "text/html", _postHTML);
}
