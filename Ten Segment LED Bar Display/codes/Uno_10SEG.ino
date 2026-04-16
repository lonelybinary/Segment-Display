// UNO R3: D4~D13, active-low (LOW=on, HIGH=off)
const int firstPin = 4;
const int lastPin = 13;
const int stepDelayMs = 120;   // step delay
const int allOffDelayMs = 300; // all-off delay

void setup() {
  for (int pin = firstPin; pin <= lastPin; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
  }
}

void loop() {
  // Fill in one direction
  for (int pin = firstPin; pin <= lastPin; pin++) {
    digitalWrite(pin, LOW);
    delay(stepDelayMs);
  }

  // All off, then repeat
  for (int pin = firstPin; pin <= lastPin; pin++) {
    digitalWrite(pin, HIGH);
  }
  delay(allOffDelayMs);
}

