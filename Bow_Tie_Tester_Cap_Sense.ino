#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 4
CapacitiveSensor   cs_4_3 = CapacitiveSensor(3,1);


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(28, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.


void setup() {

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(100); // This is where you can adjust the brightness.
  strip.show();
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  int i;
    
    rainbow(20);
  long total1 =  cs_4_3.capacitiveSensor(30);
  while(total1/50 <10){
    for(i=0; i<28; i++){
      strip.setPixelColor(i, 0,0,0);
    }
    strip.show();
    total1 =  cs_4_3.capacitiveSensor(30);
    if(total1/50 > 20){
      delay(200);
      break;
    }
  }
    
    
}

// Function for the rainbow effect.
void rainbow(uint8_t wait) {
  long total1 =  cs_4_3.capacitiveSensor(30);
  uint16_t i, j;
  int sleep = 0;
  
  while(total1/50 < 20){
    for(j=0; j<256; j++) {
      for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel((i+j) & 255));
      }
      strip.show();
      delay(wait);
      total1 =  cs_4_3.capacitiveSensor(30);
      if(total1/50 > 20){
        delay(200);
        sleep = 1;
        break;
    }
  } 
}
}



// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

