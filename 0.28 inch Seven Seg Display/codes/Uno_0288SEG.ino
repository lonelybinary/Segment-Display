// 0.28" eight-digit 7-segment module + MAX7219 — DIN / CLK / CS (LOAD) + GND / VCC
// VCC: 3.3 V or 5 V (both OK). Uses LedControl (Library Manager: "LedControl").

#include "LedControl.h"

// Variant selection:
// 0 = Decimal-point version (DP on digits)
// 1 = Clock version (middle colons are wired to digit dots; see COLON_* below)
#define VARIANT_CLOCK 1

const int DIN_PIN = 12;  // DIN — change if you rewire
const int CLK_PIN = 11;  // CLK
const int CS_PIN  = 10;  // CS / LOAD

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

// Clock-variant colon mapping (verified by dot scan):
// - digit 1 dot controls the left colon
// - digit 5 dot controls the right colon
// Digit index: 0 = leftmost, 7 = rightmost.
#define COLON_LEFT_DIGIT  1
#define COLON_RIGHT_DIGIT 5

// Count up 0…7 on digits left to right: show "0", then "01", … ending in "01234567", then blank.
static void show0to7Incremental() {
  lc.clearDisplay(0);
  for (int pos = 0; pos < 8; pos++) {
    lc.setDigit(0, pos, (byte)pos, false);
    delay(180);
  }
  delay(350);
  lc.clearDisplay(0);
  delay(150);
}

// Decimal-point version demo: show 01234567 with every digit dot on.
static void show0to7WithDotsIncremental() {
  lc.clearDisplay(0);
  for (int pos = 0; pos < 8; pos++) {
    // Fill digits left-to-right; each digit has its DP on.
    lc.setDigit(0, pos, (byte)pos, true);
    delay(180);
  }
  delay(600);
}

// Two demo times on one line: 08:30 and 17:45
// Clock variant: use digit dots as colons (digit 1 and digit 5).
// Decimal-point variant: use a different demo (all digits with dots).
static void showTwoTimes() {
#if VARIANT_CLOCK
  const bool colonL = true;
  const bool colonR = true;
#else
  const bool colonL = false;
  const bool colonR = false;
#endif

  lc.setDigit(0, 0, 0, false);
  lc.setDigit(0, 1, 8, colonL); // clock variant: left colon
  lc.setDigit(0, 2, 3, false);
  lc.setDigit(0, 3, 0, false);

  lc.setDigit(0, 4, 1, false);
  lc.setDigit(0, 5, 7, colonR); // clock variant: right colon
  lc.setDigit(0, 6, 4, false);
  lc.setDigit(0, 7, 5, false);
}

void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  show0to7Incremental();
#if VARIANT_CLOCK
  showTwoTimes();
#else
  show0to7WithDotsIncremental();
#endif
}

void loop() {
  delay(1000);
}
