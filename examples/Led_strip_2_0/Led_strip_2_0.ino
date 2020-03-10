#include<led_effects.h>
#define PIN 6
#define NUM_LEDS 60

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
LedEffects le(strip, NUM_LEDS);

int effect = 0;
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  effect = 9;
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(effect)
  {
    case 1:
      le.rainbowCycle(20);
      break;
    case 2:
      le.bouncingBalls(0xff,0,0, 3);
      break;
    case 3:
      le.colorWipe(0x00,0xff,0x00, 50);
      le.colorWipe(0x00,0x00,0x00, 50);
      break;
    case 4:
      le.cylonBounce(0xff, 0, 0, 4, 10, 50);
      break;
    case 5:
      le.fadeInOut(0xff, 0x00, 0x00); // red
      le.fadeInOut(0xff, 0xff, 0xff); // white 
      le.fadeInOut(0x00, 0x00, 0xff); // blue
      break;
    case 6:
      le.strobe(0xff, 0xff, 0xff, 10, 50, 1000);
      break;
    case 7:
      le.theaterChaseRainbow(20);
      break;
    case 8:
      le.twinkle(0xff, 0, 0, 10, 100, false);
      break;
    case 9:
      le.sparkle(0xff, 0xff, 0xff, 0);
      break;

  }
}
