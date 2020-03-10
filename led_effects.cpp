#pragma once
#include <led_effects.h>

LedEffects::LedEffects(Adafruit_NeoPixel strip, int number_of_leds){
    this->strip = strip;
    this->NUM_LEDS = number_of_leds;
}

/*-----------------------------------------------------------*/
/*-----------------RAINBOW EFFECT----------------------------*/
/*-----------------------------------------------------------*/
void LedEffects::rainbowCycle(int SpeedDelay) {
    byte *c;
    uint16_t i, j;

    for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
        for(i=0; i< this->NUM_LEDS; i++) {
            c=Wheel(((i * 256 / this->NUM_LEDS) + j) & 255);
            LedEffects::setPixel(i, *c, *(c+1), *(c+2));
        }
        LedEffects::showStrip();
        delay(SpeedDelay);
    }
}

byte * LedEffects::Wheel(byte WheelPos) {
    static byte c[3];
    
    if(WheelPos < 85) {
        c[0]=WheelPos * 3;
        c[1]=255 - WheelPos * 3;
        c[2]=0;
    } else if(WheelPos < 170) {
        WheelPos -= 85;
        c[0]=255 - WheelPos * 3;
        c[1]=0;
        c[2]=WheelPos * 3;
    } else {
        WheelPos -= 170;
        c[0]=0;
        c[1]=WheelPos * 3;
        c[2]=255 - WheelPos * 3;
    }

    return c;
}
/*-----------------------------------------------------------*/
/*-----------------END RAINBOW EFFECT------------------------*/
/*-----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*-----------------BOUNCING BALL EFFECT---------------------*/
/*----------------------------------------------------------*/
void LedEffects::bouncingBalls(byte red, byte green, byte blue, int BallCount) {
  float Gravity = -9.81;
  int StartHeight = 1;
  
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
  
  for (int i = 0 ; i < BallCount ; i++) {   
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0; 
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2); 
  }

  while (true) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
  
      if ( Height[i] < 0 ) {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
  
        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }
  
    for (int i = 0 ; i < BallCount ; i++) {
      LedEffects::setPixel(Position[i],red,green,blue);
    }
    
    LedEffects::showStrip();
    LedEffects::setAll(0,0,0);
  }
}
/*----------------------------------------------------------*/
/*-----------------END BOUNCING BALL------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*-----------------COLOR WIPE EFFECT------------------------*/
/*----------------------------------------------------------*/
void LedEffects::colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for(uint16_t i=0; i<NUM_LEDS; i++) {
      LedEffects::setPixel(i, red, green, blue);
      LedEffects::showStrip();
      delay(SpeedDelay);
  }
}
/*----------------------------------------------------------*/
/*-----------------END WIPE---------------------------------*/
/*----------------------------------------------------------*/


/*----------------------------------------------------------*/
/*-----------------CYCLON EFFECT----------------------------*/
/*----------------------------------------------------------*/
void LedEffects::cylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    LedEffects::setAll(0,0,0);
    LedEffects::setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    LedEffects::setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    LedEffects::showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    LedEffects::setAll(0,0,0);
    LedEffects::setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    LedEffects::setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    LedEffects::showStrip();
    delay(SpeedDelay);
  }
  
  delay(ReturnDelay);
}
/*----------------------------------------------------------*/
/*-----------------END CYCLON ------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*-----------------FADE IN FADE OUT EFFECT------------------*/
/*----------------------------------------------------------*/
void LedEffects::fadeInOut(byte red, byte green, byte blue){
  float r, g, b;
      
  for(int k = 0; k < 256; k=k+1) { 
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    LedEffects::setAll(r,g,b);
    LedEffects::showStrip();
  }
     
  for(int k = 255; k >= 0; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    LedEffects::setAll(r,g,b);
    LedEffects::showStrip();
  }
}
/*----------------------------------------------------------*/
/*-----------------END FADE IN FADE OUT---------------------*/
/*----------------------------------------------------------*/


/*----------------------------------------------------------*/
/*-----------------FIRE EFFECT-------------------------------*/
/*----------------------------------------------------------*/

void LedEffects::fire(int Cooling, int Sparking, int SpeedDelay) {
  byte heat[this->NUM_LEDS];
  int cooldown;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < this->NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / this->NUM_LEDS) + 2);
    
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
  
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= this->NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
    
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < this->NUM_LEDS; j++) {
    LedEffects::setPixelHeatColor(j, heat[j] );
  }

  LedEffects::showStrip();
  delay(SpeedDelay);
}

void LedEffects::setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    LedEffects::setPixel(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    LedEffects::setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    LedEffects::setPixel(Pixel, heatramp, 0, 0);
  }
}

/*----------------------------------------------------------*/
/*-----------------END FIRE----------------------------------*/
/*----------------------------------------------------------*/



/*----------------------------------------------------------*/
/*-----------------STROBE EFFECT-------------------------------*/
/*----------------------------------------------------------*/
void LedEffects::strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause){
  for(int j = 0; j < StrobeCount; j++) {
    LedEffects::setAll(red,green,blue);
    LedEffects::showStrip();
    delay(FlashDelay);
    LedEffects::setAll(0,0,0);
    LedEffects::showStrip();
    delay(FlashDelay);
  }
 delay(EndPause);
}
/*----------------------------------------------------------*/
/*-----------------END STROBE----------------------------------*/
/*----------------------------------------------------------*/




/*----------------------------------------------------------*/
/*-----------------THEATER RAINBOW EFFECT-------------------------------*/
/*----------------------------------------------------------*/

void LedEffects::theaterChaseRainbow(int SpeedDelay) {
  byte *c;
  
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < NUM_LEDS; i=i+3) {
          c = LedEffects::Wheel( (i+j) % 255);
          LedEffects::setPixel(i+q, *c, *(c+1), *(c+2));    //turn every third pixel on
        }
        LedEffects::showStrip();
       
        delay(SpeedDelay);
       
        for (int i=0; i < NUM_LEDS; i=i+3) {
          LedEffects::setPixel(i+q, 0,0,0);        //turn every third pixel off
        }
    }
  }
}

/*----------------------------------------------------------*/
/*-----------------END THEATER RAINBOW ----------------------------------*/
/*----------------------------------------------------------*/


/*----------------------------------------------------------*/
/*-----------------EFF TWINKLE-------------------------------*/
/*----------------------------------------------------------*/

void LedEffects::twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne) {
  LedEffects::setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
     LedEffects::setPixel(random(NUM_LEDS),red,green,blue);
     LedEffects::showStrip();
     delay(SpeedDelay);
     if(OnlyOne) { 
       LedEffects::setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

/*----------------------------------------------------------*/
/*-----------------END EFF----------------------------------*/
/*----------------------------------------------------------*/



/*----------------------------------------------------------*/
/*-----------------EFF EFFECT-------------------------------*/
/*----------------------------------------------------------*/

void LedEffects::sparkle(byte red, byte green, byte blue, int SpeedDelay) {
  int Pixel = random(NUM_LEDS);
  LedEffects::setPixel(Pixel,red,green,blue);
  LedEffects::showStrip();
  delay(SpeedDelay);
  LedEffects::setPixel(Pixel,0,0,0);
}

/*----------------------------------------------------------*/
/*-----------------END EFF----------------------------------*/
/*----------------------------------------------------------*/




/*----------------------------------------------------------*/
/*-----------------EFF EFFECT-------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*-----------------END EFF----------------------------------*/
/*----------------------------------------------------------*/




/*----------------------------------------------------------*/
/*-----------------EFF EFFECT-------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*-----------------END EFF----------------------------------*/
/*----------------------------------------------------------*/




/*----------------------------------------------------------*/
/*-----------------EFF EFFECT-------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*-----------------END EFF----------------------------------*/
/*----------------------------------------------------------*/





/*----------------------------------------------------------*/
/*-----------------EFF EFFECT-------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*-----------------END EFF----------------------------------*/
/*----------------------------------------------------------*/




/*----------------------------------------------------------*/
/*-----------------EFF EFFECT-------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*-----------------END EFF----------------------------------*/
/*----------------------------------------------------------*/




/*----------------------------------------------------------*/
/*-----------------EFF EFFECT-------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*-----------------END EFF----------------------------------*/
/*----------------------------------------------------------*/




/*----------------------------------------------------------*/
/*-----------------EFF EFFECT-------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*-----------------END EFF----------------------------------*/
/*----------------------------------------------------------*/




/*----------------------------------------------------------*/
/*-----------------EFF EFFECT-------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*-----------------END EFF----------------------------------*/
/*----------------------------------------------------------*/




/*----------------------------------------------------------*/
/*-----------------EFF EFFECT-------------------------------*/
/*----------------------------------------------------------*/

/*----------------------------------------------------------*/
/*-----------------END EFF----------------------------------*/
/*----------------------------------------------------------*/



/*----------------------------------------------------------*/
/*-----------------STANDARD METHODS ------------------------*/
/*----------------------------------------------------------*/

void LedEffects::showStrip() {
    this->strip.show();
}

void LedEffects::setPixel(int Pixel, byte red, byte green, byte blue) {
    this->strip.setPixelColor(Pixel, this->strip.Color(red, green, blue));
}

void LedEffects::setAll(byte red, byte green, byte blue) {
    for(int i = 0; i < this->NUM_LEDS; i++ ) {
        LedEffects::setPixel(i, red, green, blue); 
    }
    LedEffects::showStrip();
}

/*----------------------------------------------------------*/
/*-----------------END STANDARD METHODS --------------------*/
/*----------------------------------------------------------*/

