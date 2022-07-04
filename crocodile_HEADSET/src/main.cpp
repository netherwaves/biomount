#include <Arduino.h>

#include "adc.h"
#include "elcontrol.h"
#include "MQTT.h"



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // config EL wire
  setup_el();

  // config sensors (ADC)
  setup_adc();
  setup_sensors();    // IMPORTANT: set up ADC before sensors!

  // setup wifi + mqtt
  setup_wifi();
  //setup_mqtt();

  // testinge
  set_el_duty(EL_HEART, 255);
  set_el_duty(EL_RESP, 255);
}

void loop() {
  // put your main code here, to run repeatedly:
  //loop_mqtt();
  update_sensors();
}