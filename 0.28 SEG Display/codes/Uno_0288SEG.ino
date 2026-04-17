// 0.28" eight-digit 7-segment module + MAX7219 — DIN / CLK / CS (LOAD) + GND / VCC
// VCC: 3.3 V or 5 V (both OK). Uses LedControl (Library Manager: "LedControl").

#include "LedControl.h"

const int DIN_PIN = 12;  // DIN — change if you rewire
const int CLK_PIN = 11;  // CLK
const int CS_PIN  = 10;  // CS / LOAD

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

// One full-screen flash: 01234567 left to right, then blank (digit 0 = leftmost).
static void flash01234567Once() {
  for (int pos = 0; pos < 8; pos++) {
    lc.setDigit(0, pos, (byte)pos, false);
  }
  delay(500);
  lc.clearDisplay(0);
  delay(150);
}

// Two demo times on one line: 08:30 and 17:45 (decimal points mimic colons after hour pairs).
static void showTwoTimes() {
  lc.setDigit(0, 0, 0, false);
  lc.setDigit(0, 1, 8, true);
  lc.setDigit(0, 2, 3, false);
  lc.setDigit(0, 3, 0, false);
  lc.setDigit(0, 4, 1, false);
  lc.setDigit(0, 5, 7, true);
  lc.setDigit(0, 6, 4, false);
  lc.setDigit(0, 7, 5, false);
}

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  flash01234567Once();
  showTwoTimes();
}

void loop() {
  delay(1000);
}
