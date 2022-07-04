#pragma once

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include <Heart.h>
#include <Respiration.h>
#include <SkinConductance.h>

#define HEART_ADC_CHAN 0
#define RESP_ADC_CHAN 1
#define FOREHEAD_ADC_CHAN 2
#define NECK_ADC_CHAN 3

Adafruit_ADS1015* ads;

Heart* heart;
Respiration* resp;
SkinConductance* foreheadGSR;
SkinConductance* neckGSR;

void setup_adc() {
  ads = new Adafruit_ADS1015();

  // config ADC
  ads->setGain(GAIN_ONE);
  ads->setDataRate(2000);

  if (!ads->begin()) {
    while(1) {
      Serial.println("Could not initialize ADS1015.");
      delay(1000);
    }
  }
}


void setup_sensors() {
  // initialize sensors
  heart = new Heart(HEART_ADC_CHAN, ads);
  heart->reset();

  resp = new Respiration(RESP_ADC_CHAN, ads);
  resp->reset();

  foreheadGSR = new SkinConductance(FOREHEAD_ADC_CHAN, ads);
  foreheadGSR->reset();

  neckGSR = new SkinConductance(NECK_ADC_CHAN, ads);
  neckGSR->reset();
}

void update_sensors() {
    heart->update();
    resp->update();
    foreheadGSR->update();
    neckGSR->update();
}