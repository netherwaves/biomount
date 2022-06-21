#include <Arduino.h>

#include "MQTT.h"
#include "globals.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // biosignal multiplexer
  pinMode(PIN_A0, INPUT);
  pinMode(DIN_A, OUTPUT);
  pinMode(DIN_B, OUTPUT);
  pinMode(DIN_C, OUTPUT);

  // EL wire PWM outputs
  pinMode(EL_RESP, OUTPUT);
  pinMode(EL_GSR1, OUTPUT);
  pinMode(EL_GSR2, OUTPUT);
  pinMode(EL_HRT, OUTPUT);


  // Setup .
  setup_wifi();
  setup_mqtt();
}

void loop() {
  // put your main code here, to run repeatedly:
  loop_mqtt();
}