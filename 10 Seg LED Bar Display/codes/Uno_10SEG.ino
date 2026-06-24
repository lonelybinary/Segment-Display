// Ten Seg LED Bar Display — Arduino Uno R3 demo sketch
//
// Ten digital pins (D4–D13) each control one LED segment independently.
// Active-low wiring: LOW = segment ON, HIGH = segment OFF.
//   (This is the opposite of what you might expect — it is a common electronics pattern.)

const int firstPin      = 4;    // first Arduino pin connected to the bar display (D4)
const int lastPin       = 13;   // last  Arduino pin connected to the bar display (D13)
const int stepDelayMs   = 120;  // milliseconds between each segment lighting up (animation speed)
const int allOffDelayMs = 300;  // milliseconds to pause with all segments off before repeating

void setup() {
  // setup() runs exactly once when the Arduino powers on or resets.
  // Configure all ten pins as outputs, then turn all segments off.
  for (int pin = firstPin; pin <= lastPin; pin++) {
    pinMode(pin, OUTPUT);     // OUTPUT = this pin sends voltage out (not reads it in)
    digitalWrite(pin, HIGH);  // active-low: HIGH = segment OFF; start with all segments dark
  }
}

void loop() {
  // loop() runs over and over forever after setup() finishes.

  // Fill the bar: light segments one by one from left (D4) to right (D13).
  for (int pin = firstPin; pin <= lastPin; pin++) {
    digitalWrite(pin, LOW);  // active-low: LOW = segment ON
    delay(stepDelayMs);      // wait before lighting the next segment
  }

  // Turn all segments off, then pause before the next fill cycle.
  for (int pin = firstPin; pin <= lastPin; pin++) {
    digitalWrite(pin, HIGH); // active-low: HIGH = segment OFF
  }
  delay(allOffDelayMs);
}
