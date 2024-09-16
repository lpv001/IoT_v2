#include "./capacitive_v12.h"

int data;

//void initial_moisture_sensor(){
//  pinMode(MOISTURE_PIN, INPUT);
//}

int getMoisture(){
  data = analogRead(MOISTURE_PIN);
  return data;
}
