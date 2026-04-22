// 0.56" single-digit 7-segment LED + 74HC595 driver board
// Three wires — silkscreen: SER / SRCLK / RCLK
//
// ── SETUP ──────────────────────────────────────────────────────────────
// 1. Check the silkscreen on your 7-segment digit module:
//      5161AS → common cathode → set COMMON_ANODE to 0, wire both common pins to GND
//      5161BS → common anode  → set COMMON_ANODE to 1, wire both common pins to 5V
// 2. Change the pin numbers below if you use different Arduino pins.
// ───────────────────────────────────────────────────────────────────────

#define COMMON_ANODE 0  // 0 = 5161AS (commons → GND)
                        // 1 = 5161BS (commons → 5V)

// Pin connections (change these numbers if you rewire)
const int PIN_SER   = 8;   // SER   → D8  (serial data, sent bit by bit to the 74HC595)
const int PIN_SRCLK = 12;  // SRCLK → D12 (shift clock: each pulse shifts in one bit)
const int PIN_RCLK  = 11;  // RCLK  → D11 (latch: copies the 8 shifted bits to the outputs)

const int stepDelayMs = 500;  // milliseconds to hold each digit on screen

// ── SEGMENT BIT LAYOUT ─────────────────────────────────────────────────
//
//  Each byte sent to the 74HC595 controls 8 segment LEDs.
//  Each bit in the byte maps to one segment letter:
//
//   Bit:  7  6  5  4  3  2  1  0
//   Seg:  H  G  F  E  D  C  B  A
//
//    AAA         Example: digit "0"
//   F   B          needs A B C D E F on, G off, H off
//   F   B          bits: 0 0 1 1 1 1 1 1
//    GGG            hex: 0x3F
//   E   C           bin: 0b00111111
//   E   C
//    DDD   H = decimal point (dot, top-right corner)
//
// ───────────────────────────────────────────────────────────────────────

// uint8_t means "8-bit unsigned integer" (value 0–255). One byte = one segment pattern.
const uint8_t kDigits[10] = {
  0b00111111, // 0  segments on: A B C D E F
  0b00000110, // 1  segments on: B C
  0b01011011, // 2  segments on: A B D E G
  0b01001111, // 3  segments on: A B C D G
  0b01100110, // 4  segments on: B C F G
  0b01101101, // 5  segments on: A C D F G
  0b01111101, // 6  segments on: A C D E F G
  0b00000111, // 7  segments on: A B C
  0b01111111, // 8  all segments on
  0b01101111  // 9  segments on: A B C D F G
};

// Send a pattern to the display:
//   1. Pull RCLK LOW  → lock the outputs so they don't flicker while data is shifting in
//   2. shiftOut()     → send 8 bits one at a time via SER, clocked by SRCLK
//                       MSBFIRST = "most significant bit first" = send bit 7, then 6, 5 … 0
//   3. Pull RCLK HIGH → latch: all 8 segment outputs update at exactly the same moment
static void shiftWrite(uint8_t data) {
  digitalWrite(PIN_RCLK, LOW);
  shiftOut(PIN_SER, PIN_SRCLK, MSBFIRST, data);
  digitalWrite(PIN_RCLK, HIGH);
}

// Common-anode displays need the opposite logic: segment ON = output LOW.
// The ~ operator is bitwise NOT — it flips every bit (0 becomes 1, 1 becomes 0).
//   Example: ~0b00111111 = 0b11000000
// So the same pattern that lights segments A–F on a common-cathode display
// will light segments G and H on a common-anode display — unless we invert it.
static uint8_t segOut(uint8_t raw) {
#if COMMON_ANODE
  return (uint8_t)~raw;  // invert all 8 bits for common-anode wiring
#else
  return raw;
#endif
}

// Return the byte that turns all segments off.
// Common cathode: 0 (all bits 0 → all outputs LOW → no current → off).
// Common anode:   0xFF = 0b11111111 (all bits 1 → all outputs LOW → no current → off).
static uint8_t blankPattern() {
#if COMMON_ANODE
  return 0xFF;
#else
  return 0;
#endif
}

void setup() {
  // pinMode(pin, OUTPUT) tells Arduino this pin will send voltage out.
  pinMode(PIN_SER,   OUTPUT);
  pinMode(PIN_SRCLK, OUTPUT);
  pinMode(PIN_RCLK,  OUTPUT);

  shiftWrite(blankPattern());  // start with all segments off
}

void loop() {
  // Show digits 0 through 9, one at a time, with a 500 ms pause between each.
  for (int i = 0; i <= 9; i++) {
    shiftWrite(segOut(kDigits[i]));  // look up the segment pattern for digit i, send it
    delay(stepDelayMs);
  }
}
