#include <Arduino.h>
#include <Ticker.h>

#include "adc.h"
#include "elcontrol.h"
#include "MQTT.h"

Ticker ticker;

void send_data();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);

  // config EL wire
  setup_el();

  // config sensors (ADC)
  setup_adc();
  setup_sensors();    // IMPORTANT: set up ADC before sensors!

  // setup wifi + mqtt
  setup_wifi();
  setup_mqtt();

  // updated at around 60fps...
  ticker.attach_ms(1000, send_data);

  // testinge
  //set_el_duty(EL_HEART, 255);
  //set_el_duty(EL_RESP, 255);
}

void loop() {
  // put your main code here, to run repeatedly:
  loop_mqtt();
  update_sensors();
}

void send_data() {
  SensorPack packet = get_values();

  //send to EL wire
  update_el_wire(&packet);
  //send to ESP32
  send_to_esp32(&packet);
}