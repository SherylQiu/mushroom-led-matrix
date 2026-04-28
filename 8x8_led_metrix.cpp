// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>
#ifdef __AVR__
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 6  // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 64  // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500  // Time (in milliseconds) to pause between pixels

int colorState = 0;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.setBrightness(20);
  pixels.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)

  colorState = EEPROM.read(0);

  colorState++;

  if (colorState > 2) {
    colorState = 0;
  }

  EEPROM.write(0, colorState);

  showtime();
}

void loop() {
}

void showtime() {

  if (colorState == 0) {
    mushroom();
  } else if (colorState == 1) {
    frog();
  } else if (colorState == 2) {
    heart();
  }
}

// color area
uint32_t blank = pixels.Color(0, 0, 0);
uint32_t red = pixels.Color(200, 0, 0);
uint32_t darkred = pixels.Color(20, 10, 10);
uint32_t white = pixels.Color(200, 200, 200);
uint32_t gray = pixels.Color(18, 18, 25);

void mushroom() {

  // Row 1
  int32_t mushroom[64] = {
    blank, red, red, red, blank, blank, blank, blank,
    red, white, red, darkred, gray, gray, gray, blank,
    red, red, red, darkred, gray, white, white, gray,
    red, red, red, darkred, white, white, white, gray,
    white, red, red, darkred, white, white, gray, gray,
    red, red, red, darkred, white, white, white, gray,
    red, red, white, darkred, gray, gray, gray, blank,
    blank, red, red, red, blank, blank, blank, blank
  };

  for (int i = 0; i < 64; i++) {
    pixels.setPixelColor(i, mushroom[i]);
    pixels.show();
  }
}

void frog() {

  uint32_t green = pixels.Color(0, 200, 0);
  uint32_t darkgreen = pixels.Color(10, 20, 10);

  uint32_t frog[64] = {
    blank, blank, blank, blank, darkgreen, darkgreen, darkgreen, blank,
    blank, blank, blank, darkgreen, green, green, green, darkgreen,
    blank, blank, darkgreen, green, green, darkgreen, green, darkgreen,
    blank, darkgreen, green, green, green, darkgreen, green, darkgreen,
    blank, darkgreen, green, green, green, green, darkgreen, darkgreen,
    darkgreen, green, darkgreen, green, darkgreen, darkgreen, green, darkgreen,
    blank, darkgreen, green, green, darkgreen, blank, darkgreen, darkgreen,
    blank, blank, darkgreen, darkgreen, blank, blank, blank, blank
  };

  for (int i = 0; i < 64; i++) {
    pixels.setPixelColor(i, frog[i]);
    pixels.show();
  }
}

void heart() {

  uint32_t heart[64] = {
    blank, blank, red, red, red, blank, blank, blank,
    blank, red, red, red, red, red, blank, blank,
    blank, red, red, red, red, red, red, blank,
    blank, blank, red, red, red, red, red, red,
    blank, blank, red, red, red, red, red, red,
    blank, red, red, red, red, red, red, blank,
    blank, red, red, red, red, red, blank, blank,
    blank, blank, red, red, red, blank, blank, blank
  };

  for (int i = 0; i < 64; i++) {
    pixels.setPixelColor(i, heart[i]);
    pixels.show();
  }
}
