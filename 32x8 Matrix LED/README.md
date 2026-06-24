# Function

This module is a **32×8 pixel matrix LED display** driven by the **MAX7219** chip. It is built from **four 8×8 LED modules cascaded** in a row (the common "FC-16" 4-in-1 board), giving 256 individually controllable LEDs. It can show text, scrolling messages, numbers, and animations — perfect for name tags, clocks, and simple scrolling signs.

It is controlled over a 3-wire **SPI** interface, so you only need three signal pins on your microcontroller no matter how many 8×8 modules are chained together.

These examples work on both an **ESP32-S3** and an **Arduino UNO R3** board. The Arduino sketches are identical on both boards; MicroPython is ESP32-S3 only (the UNO cannot run MicroPython).

# Appearance

The board is a strip of four 8×8 dot-matrix LEDs. One short edge has a 5-pin **input** header (VCC, GND, DIN, CS, CLK) and the opposite edge has a matching **output** header so you can chain more modules.

> _Add your own board photos to the `images/` folder and link them here._

# Pinout

| Pin | Plain-English meaning |
| :-- | :-- |
| **VCC** (positive) | Power in. Like the **+** terminal of a battery. Connect to **5V**. |
| **GND** (negative) | Ground, the **0 V** reference. Connect to the board's GND. |
| **DIN** (data in) | SPI data. Connect to the board's data pin (ESP32-S3 GPIO 11). |
| **CS** (chip select) | Tells the chip "this message is for you". Connect to any GPIO (ESP32-S3 GPIO 10). |
| **CLK** (clock) | SPI clock — keeps data in sync. Connect to the board's clock pin (ESP32-S3 GPIO 12). |

> The output side of the board repeats these names (often labelled **DOUT** instead of DIN). Wire your microcontroller to the **input** side.

# Features

- 32×8 = **256 pixels** in one strip (four cascaded 8×8 modules)
- **MAX7219** driver — only **3 signal wires** (DIN, CLK, CS)
- Easily chained: add more modules for a longer display
- Software-adjustable brightness (16 levels)
- Operating voltage: **5V**

# Quick Wiring

The pin **numbers** are the same on both boards, so the wiring (and the Arduino code) is identical — only the label differs.

| Module | ESP32-S3 | Arduino UNO R3 |
| :-- | :-- | :-- |
| VCC | **5V** | **5V** |
| GND | GND | GND |
| DIN | GPIO 11 | D11 |
| CLK | GPIO 12 | D12 |
| CS  | GPIO 10 | D10 |

> **Power:** four MAX7219 modules can draw up to ~1 A with every LED lit. For text at moderate brightness, the board's 5V pin is fine; for a bright, full-screen image use a separate **5V supply** sharing a common ground.
>
> **Logic levels:** the UNO is 5 V and drives the MAX7219 directly — no extra parts. The ESP32-S3 uses 3.3 V logic; this usually works, but if the display flickers, shows garbage, or stays dark, add a **3.3 V → 5 V level shifter** on DIN, CLK, and CS.

# Examples

| File | What it teaches |
| :-- | :-- |
| [Arduino.md](Arduino.md) | Arduino IDE (C++) versions — same sketches run on **ESP32-S3 and Arduino UNO R3** |
| [MicroPython.md](MicroPython.md) | MicroPython versions — **ESP32-S3 only** (the UNO cannot run MicroPython) |

Both guides cover the same three beginner steps:

1. **First Light** — show a word, confirm wiring and brightness.
2. **Scrolling Text** — scroll a message across all 32 columns.
3. **Clock / Counter** — show a live, updating value.

# Libraries

- **Arduino:** [`MD_Parola`](https://github.com/MajicDesigns/MD_Parola) + [`MD_MAX72XX`](https://github.com/MajicDesigns/MD_MAX72XX) by majicDesigns. Install both from the Arduino IDE Library Manager. `MD_Parola` handles scrolling text and animations across the cascaded modules for you.
- **MicroPython:** [`max7219.py`](https://github.com/mcauser/micropython-max7219) by mcauser. Copy the single `max7219.py` file onto your board.

# Common Gotcha: Hardware Type / Orientation

If your text appears **rotated, mirrored, or scrambled**, the library's *hardware type* doesn't match your board. This is the #1 issue with these modules — it is **not** a wiring mistake.

- **Arduino (MD_Parola):** change `HARDWARE_TYPE` — try `FC16_HW`, `GENERIC_HW`, `PAROLA_HW`, or `ICSTATION_HW`.
- **MicroPython:** the `max7219.py` library targets the FC-16 layout; if a row reads backwards, your modules are a different variant.
