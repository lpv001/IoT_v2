#include <ArduinoOTA.h>
#include "./instruction.h"

void setup_instruction() {
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
}

void update_instruction(int decimal) {
  decimal_to_binary(decimal);
  digitalWrite(D1, c1);
  digitalWrite(D2, c2);
  digitalWrite(D5, c3);
  digitalWrite(D6, c4);
  digitalWrite(D7, c5);
  digitalWrite(D8, c6);
}

void decimal_to_binary(int decimal) {
  for (int i = 0; decimal > 0; ++i) {
    a[i] = decimal % 2;
    decimal = decimal / 2;
    delay(10);
  }
  if (a[0] == 1) {
    c1 = true;
  } else {
    c1 = false;
  }

  if (a[1] == 1) {
    c2 = true;
  } else {
    c2 = false;
  }

  if (a[2] == 1) {
    c3 = true;
  } else {
    c3 = false;
  }

  if (a[3] == 1) {
    c4 = true;
  } else {
    c4 = false;
  }

  if (a[4] == 1) {
    c5 = true;
  } else {
    c5 = false;
  }

  if (a[5] == 1) {
    c6 = true;
  } else {
    c6 = false;
  }

  if (a[6] == 1) {
    c7 = true;
  } else {
    c7 = false;
  }
  if (a[7] == 1) {
    c8 = true;
  } else {
    c8 = false;
  }
  for (int i = 0; i < 8; ++i) {
    Serial.print(a[i]);
    Serial.print(" ");
    a[i] = 0;
    delay(10);
  }
}
