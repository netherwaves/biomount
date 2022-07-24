#pragma once
#ifndef H_LIGHTCTL
#define H_LIGHTCTL


// includes
#include <Arduino.h>
#include <FastLED.h>
#include "adc.h"

// EL stuff
#define EL_PIN          12U

// LED stuff
#define NUM_LEDS        3
#define NEOPIXEL_PIN    13U
CRGB leds[NUM_LEDS];

// nabbed from the original Song of Seven code
// 0=HEART    1=GSR1    2=GSR2    3=RESP
uint32_t colors[4] = { 0xfa00fa, 0x64fffa, 0x8c0af0, 0x0a30f0 };


// headers
void setLedBrightness(CRGB &led, uint32_t color, float brightness);


void setup_light() {
  // initialize pins
  pinMode(EL_PIN, OUTPUT);

  // initialize FastLED
  FastLED.addLeds<NEOPIXEL, NEOPIXEL_PIN>(leds, NUM_LEDS);
}

void update_light(SensorPack &packet) {
  // EL wire for respiration
  analogWrite(EL_PIN, packet.resp);

  // set LED colors w/ appropriate brightness
  setLedBrightness(leds[0], colors[0], packet.heart);
  setLedBrightness(leds[1], colors[1], packet.forehead);
  setLedBrightness(leds[2], colors[2], packet.neck);

  // update
  FastLED.show();
}


// utility for setting the brightness on a hex code
void setLedBrightness(CRGB &led, uint32_t color, float brightness) {
  led.setRGB(
    ((color >> 16) & 0xFF) * brightness,
    ((color >> 8)  & 0xFF) * brightness,
    ((color)       & 0xFF) * brightness
  );
}


#endif