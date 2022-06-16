#include <Arduino.h>
#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(0x08);
  Wire.write(8);
  Wire.endTransmission();

  delay(1000);
}