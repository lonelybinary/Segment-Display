# TK51 - TM1637 4-Digit Display

## Function

TK51 is a **4-digit 7-segment LED display module** driven by **TM1637**. It uses a simple 2-wire interface (**CLK / DIO**) plus **VCC / GND**.

## What You Will Learn

- How to connect a display module to Arduino using **only 4 wires**
- How to install and use an **Arduino library** (TM1637Display)
- How to display a number on all 4 digits with a **single function call**
- What **brightness control** means in code
- How a `for` loop combined with `delay()` creates a timed animation

This folder provides:

- **Photos / images**: see `images/`
- **Arduino UNO R3 demo sketch**: see “Arduino Uno R3 Example” below and `codes/`

## Appearance

| ![Front](images/TK51-F.png) | ![Back](images/TK51-B.png) | ![Side](images/TK51-S.png) |
| :--: | :--: | :--: |
| **Front** | **Back** | **Side** |

## Assembly (Solder the Pin Header First)

The TK51 module ships with a **loose 4-pin header** (CLK / DIO / VCC / GND). **Solder it to the through-holes on the board before plugging the module into a breadboard or a PinPlus Shield.**

> Friction-fit, jumper-wire, or press-and-hold contacts through the un-soldered holes are **not reliable** — the display goes dark or shows random digits. Soldering the included pin header is the only reliable fix. See [Hardware Assembly (Soldering Required)](../README.md#hardware-assembly-soldering-required) in the main README.

## LED Color ↔ Silkscreen (P/N) Table

| LED color | Silkscreen / P/N |
| :-- | :-- |
| White | `5463BW-30` |
| Red | `5463BS1-1` |
| Blue | `5463BB` |
| Yellow | `5463BY` |
| Green | `5463BG-7.3` |
| Orange | `5643B0` |

## Quick Start (UNO R3)

1. Install the **TM1637Display** library in Arduino IDE (Library Manager: search `TM1637Display`).
2. Wire it as shown in “Arduino Uno R3 Example”.
3. Open `codes/Uno_TK51/Uno_TK51.ino`, select **Arduino Uno** and the correct port, then upload.

## Arduino Uno R3 Example

### Goal

Cycle through **0–9** on the 4-digit display.

### Wiring

![Wiring (Diagram)](images/wiring-diagram-uno-r3.png)

Example Arduino connections (change in code if you rewire):

- **VCC** → **5V** (or 3.3V)
- **GND** → **GND**
- **CLK** → D2
- **DIO** → D3

### Code

> **New to Arduino?** Read the [Key Concepts](#key-concepts) section below before looking at the code — it explains what `#include`, `setup()`, and `loop()` mean, and how `showNumberDec()` works.

File: `codes/Uno_TK51/Uno_TK51.ino`

```cpp
#include <TM1637Display.h>  // #include loads a library — pre-written code you can reuse

#define CLK_PIN 2   // CLK wire → Arduino pin D2 (change if you use a different pin)
#define DIO_PIN 3   // DIO wire → Arduino pin D3

TM1637Display display(CLK_PIN, DIO_PIN);  // create a display object

void setup() {
  // setup() runs once when the Arduino powers on.
  display.setBrightness(7);  // 0 (dimmest) to 7 (brightest)
}

void loop() {
  // loop() runs over and over forever.
  // i * 1111 makes all 4 digits show the same value: 0000, 1111, 2222 … 9999
  for (int i = 0; i < 10; i++) {
    display.showNumberDec(i * 1111, false);  // false = no leading zeros
    delay(1000);  // hold for 1 second
  }
}
```

### Effect

![Effect](images/TK51-uno.gif)

### Code Walkthrough

**1) Library and pin mapping**

```cpp
#include <TM1637Display.h>
#define CLK_PIN 2
#define DIO_PIN 3
```

- `TM1637Display.h`: driver library for TM1637-based 4-digit modules.
- `CLK_PIN` / `DIO_PIN`: change these if you wire to different Arduino pins.

**2) Create display instance**

```cpp
TM1637Display display(CLK_PIN, DIO_PIN);
```

- The object talks to the TM1637 using the two-wire interface (**CLK / DIO**).

**3) Brightness**

```cpp
display.setBrightness(7);
```

- Brightness range is typically **0..7** (7 = brightest).

**4) Main loop**

```cpp
for (int i = 0; i < 10; i++) {
  display.showNumberDec(i * 1111, false);
  delay(1000);
}
```

- Loops `i = 0..9`.
- `i * 1111` makes all 4 digits show the same number (e.g. 2222, 5555).
- `delay(1000)` switches once per second.

## Key Concepts

### Why Is This the Easiest Project?

Most display projects require you to understand shift registers, binary patterns, or driver ICs. The TM1637 chip and its library handle all of that for you. Your code only needs **3 lines** to make the display work:

```cpp
display.setBrightness(7);          // set brightness
display.showNumberDec(1234, false); // show 1234
delay(1000);                        // wait 1 second
```

This makes TK51 a great first project.

### How `showNumberDec()` Works

`showNumberDec(number, leadingZero)` takes two arguments:

- **`number`**: the integer to display (0 to 9999).
- **`leadingZero`**: `true` = show leading zeros (e.g. `0042`); `false` = skip them (e.g. `  42`).

Examples:

```cpp
display.showNumberDec(0,    false);  // shows "   0"
display.showNumberDec(42,   true);   // shows "0042"
display.showNumberDec(1234, false);  // shows "1234"
```

### What Is the 2-Wire Interface?

The TM1637 uses only two signal wires:

- **CLK** — a clock signal that tells the chip when to read each bit of data.
- **DIO** — the data wire that carries the actual information.

Together they form a simple serial protocol. The library handles all the timing — you do not need to worry about how it works internally.

### What Does `setBrightness()` Do?

The TM1637 has 8 brightness levels: **0** (dimmest) to **7** (brightest). Call this once in `setup()` and the display keeps that brightness until you change it or power off.

```cpp
display.setBrightness(3);  // medium brightness
```

### Installing a Library

1. Open Arduino IDE.
2. Go to **Sketch → Include Library → Manage Libraries…**
3. In the search box type **TM1637Display**.
4. Click the result and press **Install**.
5. The library is now available for any sketch.

## More Examples

### Display Any 4-Digit Number

```cpp
void setup() {
  display.setBrightness(7);
  display.showNumberDec(1234, false);  // shows "1234"
}

void loop() { }  // nothing — number stays on screen
```

Change `1234` to any number from 0 to 9999. Use `true` instead of `false` to show leading zeros (e.g. `42` becomes `0042`).

### Simple Countdown

```cpp
void loop() {
  for (int i = 10; i >= 0; i--) {
    display.showNumberDec(i, false);
    delay(1000);
  }
  delay(3000);  // pause 3 seconds, then repeat
}
```

## Try It Yourself

1. **Count to 9999** — Change the loop to `i < 10000` and use `display.showNumberDec(i, true)`. Change `delay(1000)` to `delay(50)` so you can see it count fast.
2. **Show your birthday** — Remove the loop and use `display.showNumberDec(1225, false)` to show December 25. Change the number to your own birthday (MMDD format).
3. **Dim the display** — Change `setBrightness(7)` to `setBrightness(1)`. Compare the brightness difference.
4. **Count backwards** — Change `i++` to `i--` and start from `i = 9`. Now it counts 9999 → 8888 → … → 0.
5. **Show with leading zeros** — Change the second argument of `showNumberDec` from `false` to `true` and see how `0` displays as `0000` instead of just `   0`.

## Troubleshooting

| Problem | Likely cause | What to try |
| :-- | :-- | :-- |
| Display shows nothing | Wiring wrong or library not installed | Check VCC/GND connections; make sure TM1637Display library is installed |
| Display is very dim | Low brightness setting | Change `setBrightness(7)` (7 = maximum) |
| Only some digits light up | `showNumberDec` range | The maximum value is 9999; passing a larger number may show unexpected results |
| TM1637Display not found error | Library not installed | Open **Sketch → Include Library → Manage Libraries…** and install **TM1637Display** |
| Sketch does not upload | Wrong board or port | Go to **Tools → Board → Arduino Uno** and choose the correct **Port** |

