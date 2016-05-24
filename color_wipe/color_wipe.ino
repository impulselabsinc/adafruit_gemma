#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <avr/sleep.h>

// CONFIGURABLE STUFF ------------------------------------------------------

#define NUM_LEDS      107 // Actual number of LEDs in NeoPixel strip
#define CIRCUMFERENCE 40 // Shoe circumference, in pixels, may be > NUM_LEDS
#define FPS           50 // Animation frames per second
#define LED_DATA_PIN   1 // NeoPixels are connected here
#define MOTION_PIN     0 // Vibration switch from here to GND
#define BATT_MIN_MV 3350 // Some headroom over battery cutoff near 2.9V
#define BATT_MAX_MV 4000 // And little below fresh-charged battery near 4.1V
Adafruit_NeoPixel    strip(NUM_LEDS, LED_DATA_PIN);
void                 sleep(void); // Power-down function
extern const uint8_t gamma[];     // Table at the bottom of this code

void setup() {
  // put your setup code here, to run once:
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Allow 16 MHz Trinket too
#endif
#ifdef POWER_PIN
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, LOW);    // Power-on LED strip
#endif
  strip.begin();                   // Allocate NeoPixel buffer
  strip.clear();                   // Make sure strip is clear
  strip.show();                    // before measuring battery
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t red = 0;
  uint8_t green = 127;
  uint8_t blue = 0;
  uint32_t c = strip.Color(red, green, blue);
  uint8_t wait = 50;
    for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }

}
