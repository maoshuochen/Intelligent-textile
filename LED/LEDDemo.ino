#include <FastLED.h>

#define DATA_PIN    D4
#define LED_TYPE    WS2812B
#define COLOR_ORDER RGB
#define NUM_LEDS    30
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          250
#define FRAMES_PER_SECOND  120

void setup() {
  delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(23, 255, 165);
    FastLED.show();
    delay(50);
  }
}
