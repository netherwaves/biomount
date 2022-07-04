#pragma once

#include <Arduino.h>

#define EL_RESP     0U
#define EL_GSR1     2U
#define EL_GSR2     15U
#define EL_HEART    13U


void setup_el() {
  // for EL wire dimming
  // THIS IS IMPORTANT!!!!!
  analogWriteFreq(100);

  // set pins
  pinMode(EL_RESP, OUTPUT);
  pinMode(EL_GSR1, OUTPUT);
  pinMode(EL_GSR2, OUTPUT);
  pinMode(EL_HEART, OUTPUT);
}

void set_el_duty(uint8_t pin, uint8_t duty) {
    analogWrite(pin, duty);
}