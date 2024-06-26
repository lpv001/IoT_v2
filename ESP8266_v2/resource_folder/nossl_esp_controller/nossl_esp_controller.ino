#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

SoftwareSerial esp(D0, D1);
#define LED_PIN D5
const char* ssid = "PozzVenhh";
const char* password = "012286451";


int initial_state = 0;
int counter = 0;



int previous_data = 333;

void setup() {
  // Start the I2C Bus as Master
  esp.begin(115200);
  Serial.begin(115200);
  delay(4000);
  pinMode(LED_PIN, OUTPUT);
  WiFi.begin(ssid, password);

  esp.write(0);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    ++initial_state;
    Serial.println("Connecting to WiFi..");
    if ( initial_state == 15 ){
      initial_state = 0;
      break;
    }
  }

  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
  Serial.println("Connected to the WiFi network");
    
}

void loop() {

  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    WiFiClient client;
    HTTPClient http;


    if (http.begin(client, "http://128.199.192.199/api/user_route/instruction/get_instruction?mac_address=00:00:00:00:00:00") > 0) { //Specify the URL
      
      int httpCode = http.GET();
      Serial.println(httpCode);
      if ( httpCode == 200 ) {
        digitalWrite(LED_PIN, HIGH);
      } else {
        digitalWrite(LED_PIN, LOW);
      }

      String payload = http.getString();
      //      Serial.println(httpCode);
            Serial.println(payload);

      //-----------------------------------------------------------------------------------------------------------------------------------------------------------------
      unsigned int data = payload.toInt();

      if ( httpCode == 200 ){
        if( data != previous_data){
          previous_data = data;
          esp.write(data);
          Serial.print(previous_data);
          Serial.print(" ");
          Serial.print(data);
        }
      }
      //-----------------------------------------------------------------------------------------------------------------------------------------------------------------


//      Serial.println(counter);

    delay(5000);
    }
     
    http.end(); //Free the resources

  }

}
