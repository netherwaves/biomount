#include <i2c_driver_wire.h>

void receiveEvt(int howMany);

void setup() {
  Serial.begin(9600);

  // put your setup code here, to run once:
  Wire1.begin(0x08);
  Wire1.onReceive(receiveEvt);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void receiveEvt(int howMany) {
  while (Wire1.available() > 0) {
    int i = Wire1.read();
    Serial.println(i);
  }
}