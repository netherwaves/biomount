#include <Arduino.h>
#include <Wire.h>

#include "MQTT.h"

void setup() {
  // put your setup code here, to run once:
  // Wire.begin();
  Serial.begin(115200);

  setup_wifi();
  setup_mqtt();
}


void loop() {
  loop_mqtt();

  
  // Wire.beginTransmission(0x08);
  // Wire.write(8);
  // Wire.endTransmission();

  // delay(1000);
}