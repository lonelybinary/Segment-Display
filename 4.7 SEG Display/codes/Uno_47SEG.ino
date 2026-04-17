// 4.7" seven-segment + 74HC595. MCU wires to first board DATAIN (SER) only; QH -> next DATAIN to cascade.
// How many 74HC595 / digit modules are chained in series
// 1 = single digit: 0–9 then decimal point only
// 2+ = all DPs blink 3×, then 0 … (10^NUM_DIGITS − 1)
#define NUM_DIGITS 2

#define SER   8   // DATAIN (SER) — change if you use other pins
#define CLK  12   // CLOCK (SRCLK)
#define LAT  11   // LATCH (RCLK)

#if NUM_DIGITS < 1
#error NUM_DIGITS must be >= 1
#endif

// Hex patterns for digits 0..9; 0x80 = decimal point (DP) only
const uint8_t d[] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

// Shift NUM_DIGITS bytes, then one LATCH edge to update the whole chain.
void outN(const uint8_t *buf) {
  digitalWrite(LAT, LOW);
  for (int i = 0; i < NUM_DIGITS; i++)
    shiftOut(SER, CLK, MSBFIRST, buf[i]);
  digitalWrite(LAT, HIGH);
}

void setup() {
  pinMode(SER, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LAT, OUTPUT);
  uint8_t z[NUM_DIGITS];
  for (int i = 0; i < NUM_DIGITS; i++) z[i] = 0;
  outN(z);
}

#if NUM_DIGITS == 1

void loop() {
  uint8_t b[1];
  for (int i = 0; i < 10; i++) {
    b[0] = d[i];
    outN(b);
    delay(400);
  }
  b[0] = 0x80;
  outN(b);
  delay(500);
}

#else

void loop() {
  uint8_t b[NUM_DIGITS];

  // Blink every decimal point a few times
  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < NUM_DIGITS; i++) b[i] = 0x80;
    outN(b);
    delay(200);
    for (int i = 0; i < NUM_DIGITS; i++) b[i] = 0;
    outN(b);
    delay(200);
  }

  unsigned long lim = 1UL;
  for (int i = 0; i < NUM_DIGITS; i++) lim *= 10UL;
  lim -= 1UL;

  // Count from 0 to lim; fill b[] with digit patterns (leading zeros included)
  for (unsigned long n = 0; n <= lim; n++) {
    unsigned long t = n;
    for (int i = NUM_DIGITS - 1; i >= 0; i--) {
      b[i] = d[t % 10UL];
      t /= 10UL;
    }
    outN(b);
    delay(400);
  }
}

#endif
