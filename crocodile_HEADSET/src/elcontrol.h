#pragma once

#include <Arduino.h>

#include "adc.h"

#define EL_HEART_PWM        0U
#define EL_RESP_PWM         2U
#define EL_FOREHEAD_PWM     15U
#define EL_NECK_PWM         13U


void setup_el() {
  // for EL wire dimming
  // THIS IS IMPORTANT!!!!!
  analogWriteFreq(100);

  // initialize pins
  pinMode(EL_HEART_PWM, OUTPUT);
  pinMode(EL_RESP_PWM, OUTPUT);
  pinMode(EL_FOREHEAD_PWM, OUTPUT);
  pinMode(EL_NECK_PWM, OUTPUT);
}

void set_el_duty(uint8_t pin, uint8_t duty) {
    analogWrite(pin, duty);
}

void update_el_wire(SensorPack* packet) {
  set_el_duty(EL_HEART_PWM, packet->heart * 255);
  set_el_duty(EL_RESP_PWM, packet->resp * 255);
  set_el_duty(EL_FOREHEAD_PWM, packet->forehead * 255);
  set_el_duty(EL_NECK_PWM, packet->neck * 255);
}