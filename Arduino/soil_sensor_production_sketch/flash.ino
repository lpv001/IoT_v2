#include "./flash.h"

void flash_setup() {
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}

void stable_flash() {
  digitalWrite(2, LOW);
}

void connection_start_flash() {
  for (int i = 0 ; i < 5 ; ++i) {
    digitalWrite(2, LOW);
    delay(50);
    digitalWrite(2, HIGH);
    delay(50);
  }
}

void connection_lost_flash() {
  for (int i = 0 ; i < 4 ; ++i) {
    digitalWrite(2, LOW);
    delay(500);
    digitalWrite(2, HIGH);
    delay(500);
  }
}

void connection_success_flash() {
  for (int i = 0 ; i < 4 ; ++i) {
    digitalWrite(2, LOW);
    delay(1500);
    digitalWrite(2, HIGH);
    delay(1500);
  }
}

void post_success() {
  for (int i = 0 ; i < 2 ; ++i) {
    digitalWrite(2, LOW);
    delay(500);
    digitalWrite(2, HIGH);
    delay(500);
  }
}
