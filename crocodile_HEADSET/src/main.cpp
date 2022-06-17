#include <Arduino.h>

#include "MQTT.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  setup_wifi();
  setup_mqtt();
}

void loop() {
  // put your main code here, to run repeatedly:
  loop_mqtt();
}