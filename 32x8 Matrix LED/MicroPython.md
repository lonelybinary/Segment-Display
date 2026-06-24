# ESP32-S3 Example (MicroPython)

## Goal

Use a **32×8 MAX7219 dot-matrix** display (four cascaded 8×8 modules) on an **ESP32-S3** running MicroPython to show static text, scrolling messages, and a counter. Written for beginners — each example is a complete, standalone script.

## Before You Start

MicroPython lets you run Python code directly on the board. Set it up once:

1. **Install Thonny** — a simple, beginner-friendly Python editor — from [thonny.org](https://thonny.org/).
2. **Put MicroPython on the board:** plug the ESP32-S3 into USB, then in Thonny open **Run → Configure interpreter → Install or update MicroPython** and follow the prompts. (Full guide: [micropython.org/download](https://micropython.org/download/).)
3. **Copy the driver library onto the board:** download **`max7219.py`** from [mcauser/micropython-max7219](https://github.com/mcauser/micropython-max7219), open it in Thonny, then choose **File → Save as → MicroPython device** and save it with the name `max7219.py`.
4. **Wire the display** as shown below.

**To run an example:** open the `.py` file in Thonny and click the green **Run** button. Press **Ctrl-C** in the shell (the bottom panel) to stop a scrolling/looping example.

## Wiring

| Module | ESP32-S3 |
| :-- | :-- |
| VCC | **5V** |
| GND | GND |
| DIN | GPIO 11 |
| CLK | GPIO 12 |
| CS  | GPIO 10 |

> _Add your wiring photo/diagram to `images/` and link it here._

---

## Example 1: First Light

Script: [`codes/ESP32S3_01_FirstLight.py`](codes/ESP32S3_01_FirstLight.py)

```python
from machine import Pin, SPI
import max7219

spi = SPI(1, baudrate=10000000, polarity=0, phase=0,
          sck=Pin(12), mosi=Pin(11))
cs = Pin(10, Pin.OUT)

display = max7219.Matrix8x8(spi, cs, 4)   # 4 modules = 32x8 pixels

display.brightness(5)        # 0-15
display.fill(0)              # clear
display.text("GOOD", 0, 0, 1)
display.show()
```

### Code Walkthrough

- **`from machine import Pin, SPI`:** `Pin` controls GPIO pins; `SPI` handles the serial data link.
- **`import max7219`:** The driver library you copied onto the board.
- **`spi = SPI(1, ...)`:** Opens hardware SPI bus 1. `sck=Pin(12)` and `mosi=Pin(11)` name the clock and data pins — on the ESP32-S3 these are remappable, so they just need to match your wiring. (If this errors, swap to `from machine import SoftSPI`.)
- **`cs = Pin(10, Pin.OUT)`:** The chip-select pin as a digital output.
- **`max7219.Matrix8x8(spi, cs, 4)`:** Creates the display object for **4** chained 8×8 modules.
- **`display.brightness(5)`:** Brightness 0 (dim) to 15 (bright).
- **`display.fill(0)`:** Turns every pixel off (`1` would turn them all on).
- **`display.text("GOOD", 0, 0, 1)`:** Draws text at x=0, y=0 in colour `1` (on). The built-in font is **8 pixels wide per character**, so only **4 characters** fit on a 32-pixel screen at once — for longer words, scroll them (Example 2).
- **`display.show()`:** Pushes the buffer to the LEDs. **Nothing appears until you call this.**

---

## Example 2: Scrolling Text

Script: [`codes/ESP32S3_02_ScrollingText.py`](codes/ESP32S3_02_ScrollingText.py)

```python
from machine import Pin, SPI
import max7219
import time

spi = SPI(1, baudrate=10000000, polarity=0, phase=0,
          sck=Pin(12), mosi=Pin(11))
cs = Pin(10, Pin.OUT)

display = max7219.Matrix8x8(spi, cs, 4)
display.brightness(5)

message = "Lonely Binary - 32x8 MAX7219 on ESP32-S3   "

while True:
    width = len(message) * 8
    for x in range(32, -width, -1):
        display.fill(0)
        display.text(message, x, 0, 1)
        display.show()
        time.sleep_ms(50)
```

### Code Walkthrough

- **`message = "...   "`:** The text to scroll. The trailing spaces leave a gap before it repeats.
- **`width = len(message) * 8`:** The full pixel width of the message (each character is 8 pixels wide).
- **`for x in range(32, -width, -1)`:** Steps the starting x-position from just off the **right** edge (32) to fully past the **left** edge, moving 1 pixel at a time.
- **`display.fill(0)` then `display.text(message, x, 0, 1)`:** Clear, then redraw the whole message shifted to position `x`. Only the part overlapping the 32-pixel screen is visible — that creates the scroll.
- **`display.show()`:** Pushes each frame to the LEDs.
- **`time.sleep_ms(50)`:** Controls scroll speed (smaller = faster).

---

## Example 3: Counter

Script: [`codes/ESP32S3_03_Counter.py`](codes/ESP32S3_03_Counter.py)

A 4-digit counter that ticks up once per second.

> **Why a counter and not a `MM:SS` clock here?** MicroPython's built-in font is fixed at **8 pixels wide** per character, so four digits (4 × 8 = 32) fill the screen exactly. A `MM:SS` clock needs 5 characters (40 pixels), which is wider than 32 — so on MicroPython you'd **scroll** the time (using the Example 2 pattern) instead of showing it static. (The Arduino guide's clock fits because its font is *proportional*, i.e. variable width.)

```python
from machine import Pin, SPI
import max7219
import time

spi = SPI(1, baudrate=10000000, polarity=0, phase=0,
          sck=Pin(12), mosi=Pin(11))
cs = Pin(10, Pin.OUT)

display = max7219.Matrix8x8(spi, cs, 4)
display.brightness(5)

count = 0
while True:
    text = "{:04d}".format(count)
    display.fill(0)
    display.text(text, 0, 0, 1)
    display.show()
    count = (count + 1) % 10000
    time.sleep(1)
```

### Code Walkthrough

- **`count = 0`:** The number to show, starting at zero.
- **`"{:04d}".format(count)`:** Formats the number as **4 digits** with leading zeros (e.g. `7` → `"0007"`), so it always fills the screen neatly.
- **`display.fill(0)` → `display.text(...)` → `display.show()`:** Clear, draw the number, push it to the LEDs.
- **`count = (count + 1) % 10000`:** Adds one, wrapping back to `0` after `9999`.
- **`time.sleep(1)`:** Waits one second between updates.

## Effect

> _Add a demo GIF to `images/` and link it here._
