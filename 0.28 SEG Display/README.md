# 0.28 SEG Display

## Function

This is a **0.28" eight-digit 7-segment LED display module** driven by a **MAX7219** (serial LED driver). Use it for multi-digit numbers, counters, or time-style readouts.

**Two variants** (same **GND / VCC / DIN / CLK / CS** pinout and electrical design; only the digit / symbol layout on the panel differs):

- **Decimal point** — eight digits with per-digit decimal points for general numeric use.
- **Clock** — same interface; panel adds a **middle colon** (two colon dots between the two groups of digits) for time-style display.

**Interface (5 pins):**

| Pin | Role |
| --- | --- |
| **GND** | Ground |
| **VCC** | Power — **3.3 V** or **5 V** (both supported) |
| **DIN** | Serial data in (to the MAX7219) |
| **CLK** | Serial clock |
| **CS** | Chip select (**LOAD**) |

The driver is **MAX7219**: **DIN**, **CLK**, and **CS** (LOAD) plus **VCC** / **GND**.

This folder provides:

- **Photos / images**: see `images/`
- **Arduino UNO R3 demo sketch**: see “Arduino Uno R3 Example” below and `codes/`

## Quick Start (UNO R3)

1. Install the **LedControl** library in Arduino IDE (**Sketch → Include Library → Manage Libraries…** → search `LedControl`).
2. Open `codes/Uno_0288SEG.ino` and set **`DIN_PIN`**, **`CLK_PIN`**, **`CS_PIN`** to match your wiring.
3. Connect **GND**, **VCC**, **DIN**, **CLK**, **CS** per the table above.
4. Select **Arduino Uno** and the correct port, then upload.

## Arduino Uno R3 Example

### Goal

On power-up: **one** full-screen flash (**01234567** left to right, then off) to check wiring. Then stay on **two demo times** on one line: **08:30** and **17:45** (eight digits; decimal points separate hour/minute for each). Edit `showTwoTimes()` for your values.

### Wiring (example)

Example Arduino connections (change in code if you rewire):

- **DIN** → D12  
- **CLK** → D11  
- **CS** → D10  
- **VCC** → **3.3 V** or **5 V**  
- **GND** → **GND**  

### Code

File: `codes/Uno_0288SEG.ino`

Uses the **LedControl** library (**MAX7219**, **DIN / CLK / CS**). After it runs, extend `loop()` for your application (numbers, scrolling, clock variant layout, etc.).

### Effect

Add `images/effect-uno-r3.gif` (or similar) under `images/` when ready, then embed here.

### Code Walkthrough

**1) LedControl instance**

- Third parameter is **CS** (chip select). The last argument **`1`** is the number of cascaded MAX7219 chips (one chip drives up to 8 digits).

**2) `setup`**

- `shutdown(0, false)` turns the display on.  
- `setIntensity` sets brightness.  
- `clearDisplay` blanks all digits.

**3) `setDigit`**

- `setDigit(device, digit, value, dot)` — **`digit`** is **0…7**; on this module **0 = leftmost**, **7 = rightmost**. Startup runs **`flash01234567Once()`** once, then **`showTwoTimes()`** holds **08:30** and **17:45** (use **`dot`** to mimic colons).
