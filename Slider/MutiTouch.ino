//Board ESP8266
int threshold = 2;
int pin[] = {5, 4, 14, 12, 13};
bool state[] = {false, false, false, false, false};
bool statePrev[] = {false, false, false, false, false};
int cap[] = {1, 1, 1, 1, 1};
int capPrev[] = {1, 1, 1, 1, 1};
String pinName[] = {"D1", "D2", "D5", "D6", "D7"};

void setup()
{
  Serial.begin(9600);
  Serial.println("Touch senser");
  for (int i = 0; i < 5; i++) {
    cap[i] = readCapacitivePin(pin[i]);
    capPrev[i] = cap[i];
    delay(10);
  }
}

void loop ()
{
  for (int i = 0; i < 5; i++) {
    cap[i] = readCapacitivePin(pin[i]);
    Serial.print(String(cap[i]) + " ");
    if (cap[i] > threshold) {
      state[i] = true;
      if (state[i] != statePrev[i]) {
        Serial.print(String(i) + "On");
      }
    }
    else {
      state[i] = false;
      if (state[i] != statePrev[i]) {
        Serial.println(String(i) + "Off");
      }
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
