// 0.56" single-digit 7-segment LED + 74HC595 driver board
// Three wires — silkscreen: SER / SRCLK / RCLK

const int PIN_SER   = 8;   // serial data to 595
const int PIN_SRCLK = 12;  // shift register clock
const int PIN_RCLK  = 11;  // storage register clock (latch)

const int stepDelayMs = 500;

// Shift one byte into the 595, then pulse RCLK to update the segment outputs.
static void shiftWrite(uint8_t data) {
  digitalWrite(PIN_RCLK, LOW);
  shiftOut(PIN_SER, PIN_SRCLK, MSBFIRST, data);
  digitalWrite(PIN_RCLK, HIGH);
}

// Segment bitmap for digits 0..9 (MSBFIRST). Bit layout matches this board + demo wiring.
const uint8_t kDigits[10] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

void setup() {
  pinMode(PIN_SER, OUTPUT);
  pinMode(PIN_SRCLK, OUTPUT);
  pinMode(PIN_RCLK, OUTPUT);

  shiftWrite(0); // blank display at startup
}

void loop() {
  for (int i = 0; i <= 9; i++) {
    shiftWrite(kDigits[i]);
    delay(stepDelayMs);
  }
}
