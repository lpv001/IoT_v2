#include "./flash.h"

void flash_setup() {
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);
}

void stable_flash() {
  digitalWrite(D4, LOW);
}

void connection_start_flash() {
  for (int i = 0 ; i < 5 ; ++i) {
    digitalWrite(D4, LOW);
    delay(50);
    digitalWrite(D4, HIGH);
    delay(50);
  }
}

void connection_lost_flash() {
  for (int i = 0 ; i < 4 ; ++i) {
    digitalWrite(D4, LOW);
    delay(500);
    digitalWrite(D4, HIGH);
    delay(500);
  }
}

void connection_success_flash() {
  for (int i = 0 ; i < 4 ; ++i) {
    digitalWrite(D4, LOW);
    delay(1500);
    digitalWrite(D4, HIGH);
    delay(1500);
  }
}
