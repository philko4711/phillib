#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
//int led = 13;
#define PIN_NPXL 7
#define NUMPIXELS      1
// the setup routine runs once when you press reset:
static Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN_NPXL, NEO_RGB + NEO_KHZ800);
void setup() {                
  // initialize the digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);     
  pinMode(PIN_NPXL, OUTPUT);     
  
  //digitalWrite(PIN_NPXL, LOW);
   pixels.begin();

  // pixels.setPixelColor(0, pixels.Color(0,255,0));
  //  pixels.show();
}

// the loop routine runs over and over again forever:
void loop() {
  int r = random(0, 255);
  int g = random(0, 255);
  int b = random(0, 255);
    pixels.setPixelColor(0, pixels.Color(r,g,b));
    pixels.show();
  // digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
   delay(50);               // wait for a second
  // digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  // delay(1000);               // wait for a second
  // pixels.setPixelColor(0, pixels.Color(150,0,0));
  //  pixels.show();
}
