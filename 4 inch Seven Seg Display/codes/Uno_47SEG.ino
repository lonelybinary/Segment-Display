// 4" seven-segment + 74HC595. MCU wires to first board DATAIN (SER) only; QH → next DATAIN to cascade.
//
// ── CONFIGURATION ──────────────────────────────────────────────────────
// Set NUM_DIGITS to match how many modules you have wired together.
//   1 = single module:  counts 0–9, then shows decimal point only
//   2 = two modules:    blinks DPs, then counts 00–99
//   3 = three modules:  blinks DPs, then counts 000–999  (and so on)
#define NUM_DIGITS 2

// Pin connections (change these numbers if you use different Arduino pins)
#define SER   8   // DATAIN (SER)   → Arduino D8
#define CLK  12   // CLOCK  (SRCLK) → Arduino D12
#define LAT  11   // LATCH  (RCLK)  → Arduino D11

#if NUM_DIGITS < 1
#error NUM_DIGITS must be >= 1
#endif

// Segment patterns for digits 0–9, stored as hexadecimal values.
// Each value is an 8-bit number; each bit controls one LED segment (A–G + decimal point).
// 0x80 = only the decimal point (DP) segment on.
//
//   Index:   0      1      2      3      4      5      6      7      8      9
const uint8_t d[] = {
  0x3F,  // 0 — segments A B C D E F
  0x06,  // 1 — segments B C
  0x5B,  // 2 — segments A B D E G
  0x4F,  // 3 — segments A B C D G
  0x66,  // 4 — segments B C F G
  0x6D,  // 5 — segments A C D F G
  0x7D,  // 6 — segments A C D E F G
  0x07,  // 7 — segments A B C
  0x7F,  // 8 — all segments on
  0x6F   // 9 — segments A B C D F G
};

// Send the segment patterns for all NUM_DIGITS modules, then latch once to update everything.
//
// How cascading works:
//   - Pull LAT LOW before sending (locks outputs so they don't flicker mid-update).
//   - Call shiftOut() once per module. As each new byte shifts in, the previous
//     bytes "flow" down the chain to the next module automatically.
//   - Pull LAT HIGH after the last byte — all modules update at the same moment.
//
// buf[0] = leftmost digit pattern, buf[NUM_DIGITS-1] = rightmost digit pattern.
void updateDisplay(const uint8_t *buf) {
  digitalWrite(LAT, LOW);                          // lock outputs while sending
  for (int i = 0; i < NUM_DIGITS; i++)
    shiftOut(SER, CLK, MSBFIRST, buf[i]);          // MSBFIRST = send bit 7 first, then 6, 5 … 0
  digitalWrite(LAT, HIGH);                         // latch: all modules update at once
}

void setup() {
  // Tell Arduino these three pins send data out (OUTPUT), not receive it.
  pinMode(SER, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LAT, OUTPUT);

  // Start with all segments off (pattern 0 = all bits 0 = no segments lit).
  uint8_t z[NUM_DIGITS];
  for (int i = 0; i < NUM_DIGITS; i++) z[i] = 0;
  updateDisplay(z);
}

#if NUM_DIGITS == 1
// ── SINGLE MODULE ──────────────────────────────────────────────────────
void loop() {
  uint8_t b[1];
  for (int i = 0; i < 10; i++) {    // show digits 0 through 9
    b[0] = d[i];
    updateDisplay(b);
    delay(400);
  }
  b[0] = 0x80;   // 0x80 = decimal point only
  updateDisplay(b);
  delay(500);
}

#else
// ── CASCADED MODULES ───────────────────────────────────────────────────
void loop() {
  uint8_t b[NUM_DIGITS];

  // Blink all decimal points 3 times as a startup animation.
  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < NUM_DIGITS; i++) b[i] = 0x80;  // all DP on
    updateDisplay(b);
    delay(200);
    for (int i = 0; i < NUM_DIGITS; i++) b[i] = 0;     // all off
    updateDisplay(b);
    delay(200);
  }

  // Calculate the highest number to display.
  //   2 digits → lim = 10^2 − 1 = 99
  //   3 digits → lim = 10^3 − 1 = 999
  // "unsigned long" holds large values; the "UL" suffix tells the compiler
  // to treat the literal as unsigned long (not plain int).
  unsigned long lim = 1UL;
  for (int i = 0; i < NUM_DIGITS; i++) lim *= 10UL;
  lim -= 1UL;

  // Count from 0 to lim and display each number.
  for (unsigned long n = 0; n <= lim; n++) {
    unsigned long t = n;

    // Extract individual digits using % (modulo) and / (integer division).
    // We fill the array from right to left so the ones digit goes to the rightmost module.
    //
    //   Example: n = 37, NUM_DIGITS = 2
    //     i=1: b[1] = d[37 % 10] = d[7]   (ones digit)   t becomes 3
    //     i=0: b[0] = d[ 3 % 10] = d[3]   (tens digit)   t becomes 0
    for (int i = NUM_DIGITS - 1; i >= 0; i--) {
      b[i] = d[t % 10UL];   // t % 10 extracts the rightmost decimal digit (0–9)
      t /= 10UL;             // drop the rightmost digit, shift everything one place right
    }
    updateDisplay(b);
    delay(400);
  }
}
#endif
