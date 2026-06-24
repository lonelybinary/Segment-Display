/*
 * TK51 – TM1637 4-Digit Display — Arduino Uno R3 example
 *
 * Wiring (change pin numbers in #define below if you rewire):
 *   VCC → 5V     GND → GND
 *   CLK → D2     DIO → D3
 *
 * Library required: "TM1637Display"
 *   Install: Sketch → Include Library → Manage Libraries… → search "TM1637Display" → Install
 */

#include <TM1637Display.h>  // #include loads a library — pre-written code you can reuse

#define CLK_PIN 2   // CLK wire → Arduino pin D2 (change if you use a different pin)
#define DIO_PIN 3   // DIO wire → Arduino pin D3

// Create a display object. All display commands go through this object.
TM1637Display display(CLK_PIN, DIO_PIN);

void setup() {
  // setup() runs once when the Arduino powers on.
  display.setBrightness(7);  // brightness: 0 (dimmest) to 7 (brightest)

  // Serial is optional — remove these two lines if you don't need debug output.
  Serial.begin(9600);
  Serial.println("TK51 demo started");
}

void loop() {
  // loop() runs over and over forever.

  // Cycle i from 0 to 9.
  // Multiplying by 1111 makes all four digits show the same value:
  //   i=0 → display shows 0000
  //   i=1 → display shows 1111  ...  i=9 → display shows 9999
  for (int i = 0; i < 10; i++) {
    display.showNumberDec(i * 1111, false);  // false = do not pad with leading zeros
    Serial.print("Showing: ");
    Serial.println(i * 1111);
    delay(1000);  // hold each number for 1 second before moving to the next
  }
}
