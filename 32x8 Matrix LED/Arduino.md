# Arduino IDE Example (ESP32-S3 **or** Arduino UNO R3)

## Goal

Use a **32×8 MAX7219 dot-matrix** display (four cascaded 8×8 modules) to show static text, scrolling messages, and a live clock. Written for beginners — each example is a complete, standalone sketch.

> **The same three sketches run unchanged on both the ESP32-S3 and the Arduino UNO R3.** They use software SPI on pins 11 / 12 / 10, which are valid digital pins on both boards — so the wiring and the code are identical. Pick your board's wiring table below.

## Before You Start

Never used the Arduino IDE before? Do these once:

1. **Install the Arduino IDE** on your computer — free from [arduino.cc/en/software](https://www.arduino.cc/en/software).
2. **Install the library this example needs:**
   - Open **Tools → Manage Libraries…**
   - Type **MD_Parola** in the search box, find the one **by majicDesigns**, and click **Install**.
   - If it offers to also install **MD_MAX72XX** (a library MD_Parola depends on), click **Install All**. Otherwise search **MD_MAX72XX** and install that too.
3. **ESP32-S3 only — add the board:** open **Tools → Board → Boards Manager…**, search **esp32**, and install **"esp32 by Espressif Systems"**. (For the UNO you need nothing extra — it is built in.)
4. **Connect your board** with the USB cable, then choose it under **Tools → Board** and select its port under **Tools → Port**.

**To run an example:** open the sketch (next section), click the round **➜ Upload** button at the top-left, and wait for **"Done uploading."** at the bottom.

## Wiring

The pin **numbers** are the same on both boards; only the label differs (`GPIO 11` on ESP32-S3 = `D11` on UNO).

**ESP32-S3**

| Module | ESP32-S3 |
| :-- | :-- |
| VCC | **5V** |
| GND | GND |
| DIN | GPIO 11 |
| CLK | GPIO 12 |
| CS  | GPIO 10 |

**Arduino UNO R3**

| Module | UNO R3 |
| :-- | :-- |
| VCC | **5V** |
| GND | GND |
| DIN | D11 |
| CLK | D12 |
| CS  | D10 |

> **Power (both boards):** four MAX7219 modules can draw up to ~1 A with every LED on. For **text at moderate brightness** the board's onboard 5V pin is fine. For a **bright, full-screen image**, use a separate **5V power supply** and connect its ground to the board's GND (common ground).
>
> **Logic levels:** the UNO is a 5V board, so it drives the MAX7219 directly with no extra parts. The ESP32-S3 uses 3.3V logic — usually fine, but if the display glitches add a 3.3V → 5V level shifter on DIN, CLK, and CS.

> _Add your wiring photos/diagrams to `images/` and link them here (one per board)._

---

## Example 1: First Light

Sketch: [`codes/01_FirstLight/01_FirstLight.ino`](codes/01_FirstLight/01_FirstLight.ino)

```cpp
#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4    // four 8x8 modules = 32x8 pixels

#define DATA_PIN 11      // DIN
#define CLK_PIN  12      // CLK
#define CS_PIN   10      // CS

MD_Parola display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup() {
  display.begin();
  display.setIntensity(5);    // brightness 0-15
  display.displayClear();
  display.setTextAlignment(PA_CENTER);
  display.print("HELLO");
}

void loop() {
}
```

### Code Walkthrough

- **`#include <MD_Parola.h>` / `<MD_MAX72XX.h>` / `<SPI.h>`:** Load the text library, the low-level matrix driver, and the SPI helper.
- **`#define HARDWARE_TYPE MD_MAX72XX::FC16_HW`:** Tells the library how your specific 4-in-1 board is wired internally. If text comes out rotated or mirrored, change this (see the README's "Common Gotcha" section).
- **`#define MAX_DEVICES 4`:** Four 8×8 modules are chained = a 32×8 display.
- **`DATA_PIN / CLK_PIN / CS_PIN`:** The three pins connected to DIN, CLK, and CS — the same numbers on ESP32-S3 and UNO. Change these if you wire differently.
- **`MD_Parola display = MD_Parola(...)`:** Creates the display object. Naming all three pins uses *software SPI*, which works the same on both boards.
- **`display.begin()`:** Initialises the display.
- **`display.setIntensity(5)`:** Sets brightness from 0 (dim) to 15 (bright).
- **`display.setTextAlignment(PA_CENTER)`:** Centres the text on the 32-pixel width.
- **`display.print("HELLO")`:** Shows the word. The built-in font is *proportional*, so "HELLO" fits within 32 pixels.

---

## Example 2: Scrolling Text

Sketch: [`codes/02_ScrollingText/02_ScrollingText.ino`](codes/02_ScrollingText/02_ScrollingText.ino)

```cpp
#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define DATA_PIN 11
#define CLK_PIN  12
#define CS_PIN   10

MD_Parola display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

const char *message = "Lonely Binary - 32x8 MAX7219";

void setup() {
  display.begin();
  display.setIntensity(5);
  display.displayClear();
  display.displayText(message, PA_LEFT, 80, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void loop() {
  if (display.displayAnimate()) {
    display.displayReset();
  }
}
```

### Code Walkthrough

- **`const char *message = "..."`:** The text to scroll — longer than the screen, which is the whole point of a 32×8 display.
- **`display.displayText(message, PA_LEFT, 80, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT)`:** Sets up the animation. The arguments are: the text, the alignment, the **scroll speed in milliseconds** (smaller = faster), the pause at the end, and the **entry** and **exit** effects (both scroll-left here).
- **`display.displayAnimate()`:** Called every `loop()`; it advances the scroll one step and returns `true` when the message has fully scrolled off.
- **`display.displayReset()`:** Restarts the message so it scrolls forever.

---

## Example 3: Scrolling Clock / Counter

Sketch: [`codes/03_Clock/03_Clock.ino`](codes/03_Clock/03_Clock.ino)

A stopwatch counting `MM:SS` since the board powered on — no extra hardware needed. It uses `millis()` (the board's internal millisecond timer). Swap in an NTP source (ESP32-S3) or an RTC module later to make it a real wall clock.

```cpp
#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define DATA_PIN 11
#define CLK_PIN  12
#define CS_PIN   10

MD_Parola display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

char timeBuf[6];                 // "MM:SS" + end marker
unsigned long lastUpdate = 0;

void updateTime() {
  unsigned long totalSeconds = millis() / 1000;
  int minutes = (totalSeconds / 60) % 100;
  int seconds = totalSeconds % 60;
  sprintf(timeBuf, "%02d:%02d", minutes, seconds);
}

void setup() {
  display.begin();
  display.setIntensity(5);
  display.displayClear();
  display.setTextAlignment(PA_CENTER);
  updateTime();
  display.print(timeBuf);
}

void loop() {
  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();
    updateTime();
    display.print(timeBuf);
  }
}
```

### Code Walkthrough

- **`char timeBuf[6]`:** A small text buffer holding the 5 characters of `"MM:SS"` plus the hidden end-of-string marker.
- **`updateTime()`:** Reads `millis()` (milliseconds since power-on), converts it to minutes and seconds, and formats them into `timeBuf` with `sprintf` so single digits get a leading zero (e.g. `03:07`).
- **`millis() - lastUpdate >= 1000`:** A non-blocking timer — instead of `delay()`, it checks whether a second has passed, then refreshes. This keeps the program responsive.
- **`display.print(timeBuf)`:** Redraws the time. The proportional font keeps `MM:SS` (5 characters incl. the colon) within the 32-pixel width.

## Effect

> _Add a demo GIF to `images/` and link it here._
