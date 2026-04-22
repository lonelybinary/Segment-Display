// 0.28" eight-digit 7-segment module + MAX7219 — DIN / CLK / CS (LOAD) + GND / VCC
// VCC: 3.3 V or 5 V (both OK).
//
// Library required: "LedControl"
//   Install: Sketch → Include Library → Manage Libraries… → search "LedControl" → Install

#include "LedControl.h"  // #include loads a library — pre-written code for the MAX7219 chip

// ── VARIANT SELECTION ──────────────────────────────────────────────────
// Look at your display module and pick the right number:
//   Clock version         → change VARIANT_CLOCK to 1
//   Decimal-point version → change VARIANT_CLOCK to 0
#define VARIANT_CLOCK 1
// ───────────────────────────────────────────────────────────────────────

// Pin connections (change these numbers if you rewire)
const int DIN_PIN = 12;  // DIN → D12 (serial data into MAX7219)
const int CLK_PIN = 11;  // CLK → D11 (serial clock)
const int CS_PIN  = 10;  // CS  → D10 (chip select: LOW while sending, HIGH to latch)

// Create a LedControl object.
// Arguments: DIN pin, CLK pin, CS pin, number of cascaded MAX7219 chips (1 here).
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

// On the clock variant the colon LEDs share the "dot" signal on digit 1 and digit 5.
// Digit index: 0 = leftmost position, 7 = rightmost position.
#define COLON_LEFT_DIGIT  1  // turning dot ON for digit 1 lights the left colon
#define COLON_RIGHT_DIGIT 5  // turning dot ON for digit 5 lights the right colon

// ── HELPER FUNCTIONS ───────────────────────────────────────────────────
// "static" means these functions are private to this file — they are helpers
// used only here and are not meant to be called from other files.
// ───────────────────────────────────────────────────────────────────────

// Fill digit positions 0…7 from left to right, then clear the display.
static void show0to7Incremental() {
  lc.clearDisplay(0);
  for (int pos = 0; pos < 8; pos++) {
    // setDigit(device, position, digit, dot)
    //   device   = 0 (we only have one MAX7219 chip)
    //   position = 0 (leftmost) … 7 (rightmost)
    //   digit    = the number to show (0–9)
    //   dot      = true = decimal point on, false = decimal point off
    lc.setDigit(0, pos, (byte)pos, false);  // (byte) converts int to 8-bit value the library expects
    delay(180);
  }
  delay(350);
  lc.clearDisplay(0);
  delay(150);
}

// Decimal-point variant: same fill, but each digit's decimal point is also on.
static void show0to7WithDotsIncremental() {
  lc.clearDisplay(0);
  for (int pos = 0; pos < 8; pos++) {
    lc.setDigit(0, pos, (byte)pos, true);  // true = decimal point ON
    delay(180);
  }
  delay(600);
}

// Show two clock times side by side: "08:30" and "17:45".
// Clock variant: the colon LEDs are driven by the dot signal on digit 1 and digit 5.
static void showTwoTimes() {
#if VARIANT_CLOCK
  const bool colonL = true;   // light the left colon
  const bool colonR = true;   // light the right colon
#else
  const bool colonL = false;
  const bool colonR = false;
#endif

  // Left half "08:30"  (digit positions 0–3)
  lc.setDigit(0, 0, 0, false);
  lc.setDigit(0, 1, 8, colonL);  // dot on digit 1 = left colon (clock variant only)
  lc.setDigit(0, 2, 3, false);
  lc.setDigit(0, 3, 0, false);

  // Right half "17:45"  (digit positions 4–7)
  lc.setDigit(0, 4, 1, false);
  lc.setDigit(0, 5, 7, colonR);  // dot on digit 5 = right colon (clock variant only)
  lc.setDigit(0, 6, 4, false);
  lc.setDigit(0, 7, 5, false);
}

void setup() {
  // The MAX7219 powers up in "shutdown mode" (all outputs off) to avoid showing
  // random garbage on startup.  shutdown(0, false) means: device 0, shut down = false → ON.
  lc.shutdown(0, false);

  // Set brightness: 0 (dimmest) to 15 (brightest).
  lc.setIntensity(0, 8);

  // Clear all 8 digit positions before showing anything.
  lc.clearDisplay(0);

  // Stage 1: count up 0→7 across all 8 digits, then clear.
  show0to7Incremental();

  // Stage 2: depends on which variant you have (set by VARIANT_CLOCK above).
#if VARIANT_CLOCK
  showTwoTimes();               // clock variant: show 08:30 and 17:45 with colons
#else
  show0to7WithDotsIncremental(); // decimal-point variant: count 0→7 with dots on
#endif
}

void loop() {
  // All animation happens in setup() above.
  // loop() keeps running forever but does nothing — the final display image just stays on.
  delay(1000);
}
