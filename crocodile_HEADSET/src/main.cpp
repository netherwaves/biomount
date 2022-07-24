#include <Arduino.h>
#include <Ticker.h>

#include "adc.h"
#include "lightctl.h"
#include "MQTT.h"

Ticker ticker;
SensorPack packet;

void send_data();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);

  // config light controller
  setup_light();

  // config sensors (ADC)
  setup_adc();
  setup_sensors();    // IMPORTANT: set up ADC before sensors!

  // setup wifi + mqtt
  setup_wifi();
  setup_mqtt();

  // updated at around 60fps...
  ticker.attach_ms(15, send_data);
}

void loop() {
  // put your main code here, to run repeatedly:
  loop_mqtt();
  update_sensors();
}

void send_data() {
  packet = get_values();

  //send to EL wire
  update_light(packet);
  //send to ESP32
  send_to_esp32(packet);
}