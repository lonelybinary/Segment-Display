// 0.56" single-digit 7-seg + 74HC595 driver board
// Interface: SER(DS), SRCLK(SHCP), RCLK(STCP)

const int PIN_SER   = 8;   // SER / DS
const int PIN_SRCLK = 12;  // SRCLK / SHCP
const int PIN_RCLK  = 11;  // RCLK / STCP

const int stepDelayMs = 500;

static void shiftWrite(uint8_t data) {
  digitalWrite(PIN_RCLK, LOW);
  shiftOut(PIN_SER, PIN_SRCLK, MSBFIRST, data);
  digitalWrite(PIN_RCLK, HIGH);
}

// Digit table: 0~9
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

  // Clear on power-up (all off)
  shiftWrite(0);
}

void loop() {
  for (int i = 0; i <= 9; i++) {
    shiftWrite(kDigits[i]);
    delay(stepDelayMs);
  }
}

