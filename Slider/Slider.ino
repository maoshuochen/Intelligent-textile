//Board ESP8266
#include <FastLED.h>

//LED
#define DATA_PIN    D4
#define LED_TYPE    WS2812B
#define COLOR_ORDER RGB
#define NUM_LEDS    30
CRGB leds[NUM_LEDS];
#define BRIGHTNESS          250
#define FRAMES_PER_SECOND  120

//Slider
int threshold = 3;
int pin[] = {5, 4, 14, 12, 13}; //GPIO *
String pinName[] = {"D1", "D2", "D5", "D6", "D7"};
bool state[5];
bool statePrev[5];
int cap[5];
int capPrev[5];

void setup() {

  Serial.begin(9600);
  //setup slider
  for (int i = 0; i < 5; i++) {
    pinMode(pin[i], INPUT);
    cap[i] = readCapacitivePin(pin[i]);
    capPrev[i] = cap[i];
    state[i] = false;
    statePrev[i] = false;
    delay(10);
  }
  //setup LED
  pinMode(DATA_PIN, OUTPUT);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); // tell FastLED about the LED strip configuration
  FastLED.setBrightness(BRIGHTNESS); // set master brightness control
  FastLED.clear();

  delay(1000);
}

void loop()
{
  for (int i = 0; i < 5; i++) {
    cap[i] = readCapacitivePin(pin[i]);
    Serial.print(String(cap[i]) + " ");
    if (cap[i] > threshold) {
      state[i] = true;
      for (int j = 0 ; j < 2; j++) {
        leds[j + i * 2] = CHSV(100, 255, 165);
      }
      FastLED.show();
    }
    else {
      state[i] = false;
      for (int j = 0 ; j < 2; j++) {
        leds[j + i * 2] = CHSV(100, 255, 0);
      }
      FastLED.show();
    }
    statePrev[i] = state[i];
    delay(10);
  }
  Serial.println();
}



// readCapacitivePin
//  Input: Arduino pin number
//  Output: A number, from 0 to 17 expressing
//  how much capacitance is on the pin
//  When you touch the pin, or whatever you have
//  attached to it, the number will get higher

uint8_t readCapacitivePin(int pinToMeasure) {
  pinMode(pinToMeasure, OUTPUT);
  digitalWrite(pinToMeasure, LOW);
  delay(1);
  // Prevent the timer IRQ from disturbing our measurement
  noInterrupts();
  // Make the pin an input with the internal pull-up on
  pinMode(pinToMeasure, INPUT_PULLUP);
  // Now see how long the pin to get pulled up. This manual unrolling of the loop
  // decreases the number of hardware cycles between each read of the pin,
  // thus increasing sensitivity.

  uint8_t cycles = 17;
  if (digitalRead(pinToMeasure)) {
    cycles =  0;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles =  1;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles =  2;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles =  3;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles =  4;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles =  5;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles =  6;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles =  7;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles =  8;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles =  9;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles = 10;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles = 11;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles = 12;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles = 13;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles = 14;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles = 15;
  }
  else if (digitalRead(pinToMeasure)) {
    cycles = 16;
  }
  // End of timing-critical section
  interrupts();
  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  digitalWrite(pinToMeasure, LOW);
  pinMode(pinToMeasure, OUTPUT);
  return cycles;
}

