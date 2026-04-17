// Ten Seg LED Bar Display — Arduino Uno R3 demo sketch
// Ten GPIOs drive ten segments (D4..D13). Active-low: LOW = segment on, HIGH = off.

const int firstPin = 4;
const int lastPin = 13;
const int stepDelayMs = 120;   // delay after each new segment turns on (fill speed)
const int allOffDelayMs = 300; // pause with all segments off before repeating

void setup() {
  for (int pin = firstPin; pin <= lastPin; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH); // active-low: start with all segments off
  }
}

void loop() {
  // Light segments one by one from D4 toward D13
  for (int pin = firstPin; pin <= lastPin; pin++) {
    digitalWrite(pin, LOW);
    delay(stepDelayMs);
  }

  // Turn all segments off, then repeat
  for (int pin = firstPin; pin <= lastPin; pin++) {
    digitalWrite(pin, HIGH);
  }
  delay(allOffDelayMs);
}
