/*
The MIT License (MIT)

Copyright (c) 2013 FastLED

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/


#include <Adafruit_NeoPixel.h>
#include <Keyboard.h>
#include "FastLED.h"
#include <FastLED.h>

#define D_KEY_PIN 18
#define F_KEY_PIN 19
#define J_KEY_PIN 20
#define K_KEY_PIN 21

#define D_KEY 'd'
#define F_KEY 'f'
#define J_KEY 'j'
#define K_KEY 'k'

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    15
//#define CLK_PIN   4
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    1
#define BRIGHTNESS  155

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);

  pinMode(D_KEY_PIN, INPUT_PULLUP);
  pinMode(F_KEY_PIN, INPUT_PULLUP);
  pinMode(J_KEY_PIN, INPUT_PULLUP);
  pinMode(K_KEY_PIN, INPUT_PULLUP);

  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip)
    .setDither(BRIGHTNESS < 255);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


void loop() {
  bool dPressed = digitalRead(D_KEY_PIN);
  bool fPressed = digitalRead(F_KEY_PIN);
  bool jPressed = digitalRead(J_KEY_PIN);
  bool kPressed = digitalRead(K_KEY_PIN);

  if(!dPressed){
    Keyboard.press(D_KEY);
  }else{
    Keyboard.release(D_KEY);
  }
  
  if(!fPressed){
    Keyboard.press(F_KEY);
  }else{
    Keyboard.release(F_KEY);
  }
  
  if(!jPressed){
    Keyboard.press(J_KEY);
  }else{
    Keyboard.release(J_KEY);
  }
  
  if(!kPressed){
    Keyboard.press(K_KEY);
  }else{
    Keyboard.release(K_KEY);
  }
  
  if(dPressed && fPressed && jPressed && kPressed){
    delay(10);
  }
  
  pride();
  FastLED.show();  
}

  void pride() 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    
    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS-1) - pixelnumber;
    
    nblend( leds[pixelnumber], newcolor, 64);
  }
}
