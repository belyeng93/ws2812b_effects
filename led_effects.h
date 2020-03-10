#include <Adafruit_NeoPixel.h>
#ifndef LED_EFFECTS_H // include guard
#define LED_EFFECTS_H
class LedEffects{
    public:
        LedEffects(Adafruit_NeoPixel strip, int number_of_leds);
        void rainbowCycle(int SpeedDelay);
        void bouncingBalls(byte red, byte green, byte blue, int BallCount);
        void colorWipe(byte red, byte green, byte blue, int SpeedDelay);
        void cylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
        void fadeInOut(byte red, byte green, byte blue);
        void fire(int Cooling, int Sparking, int SpeedDelay);
        void strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause);
        void theaterChaseRainbow(int SpeedDelay);
        void twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne);
        void sparkle(byte red, byte green, byte blue, int SpeedDelay);
    private:
        Adafruit_NeoPixel strip;
        int NUM_LEDS;

        byte * Wheel(byte WheelPos);
        void setPixelHeatColor (int Pixel, byte temperature);

        void showStrip();
        void setPixel(int Pixel, byte red, byte green, byte blue);
        void setAll(byte red, byte green, byte blue);
};

#endif;