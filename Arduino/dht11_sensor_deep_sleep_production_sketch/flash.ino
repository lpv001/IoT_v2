#include "./flash.h"

void flash_setup(){
  pinMode(D2, OUTPUT);
  digitalWrite(D2, HIGH);
}

void connection_success_flash(){
  for(int i = 0 ; i < 5 ; ++i){
    digitalWrite(D2, LOW);
    delay(50);
    digitalWrite(D2, HIGH);
    delay(50);
  }
}

void connection_lost_flash(){
    for(int i = 0 ; i < 3 ; ++i){
    digitalWrite(D2, LOW);
    delay(100);
    digitalWrite(D2, HIGH);
    delay(100);
  }
}
