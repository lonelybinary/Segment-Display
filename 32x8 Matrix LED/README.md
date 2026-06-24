# What Is This?

This is a **32×8 LED matrix** — a grid of tiny lights, 32 across and 8 down (256 LEDs in total). From code you can switch each light on or off to spell words, scroll messages, or show numbers and small animations. Great for name badges, clocks, and mini scrolling signs.

The grid is really **four 8×8 squares joined end-to-end** (a popular board often sold as an "FC-16 4-in-1" module). A small chip on the back — the **MAX7219** — does the hard part of lighting the correct LEDs; your board just sends it simple instructions.

Your board talks to the MAX7219 over **SPI**, a common way for chips to exchange data using a few shared wires. In practice that means **only three signal wires** (plus power and ground), no matter how many 8×8 squares are chained together.

These examples run on two beginner-friendly boards:

- **Arduino UNO R3** — the classic starter board.
- **ESP32-S3** — a faster board that also has Wi-Fi.

The **Arduino code is identical on both boards.** The **MicroPython** examples are **ESP32-S3 only** (the UNO cannot run MicroPython).

> New to a word here (LED, GND, library, …)? See the **Glossary** in the [main README](../README.md#glossary), plus the [New Words](#new-words-used-here) table at the bottom of this page.

# What You Need

- The **32×8 MAX7219 matrix** module (this product)
- One board: an **Arduino UNO R3** *or* an **ESP32-S3**
- A **USB cable** to connect that board to your computer
- **5 jumper wires** (female-to-male works for most boards)
- Free software on your computer — **Arduino IDE** (for the Arduino examples) or **Thonny** (for the MicroPython examples)
- The pin header **soldered** onto the module — see the soldering note in the [main README](../README.md#hardware-assembly-soldering-required). Loose, un-soldered wires give flaky, hard-to-debug results.

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

> The output side of the module repeats these names (often labelled **DOUT** instead of DIN). Wire your board to the **input** side.

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

# New Words Used Here

| Word | Plain-English meaning |
| :-- | :-- |
| **Pixel** | One single LED in the grid — one dot of light. |
| **Dot matrix** | A grid of pixels (here 32 × 8) used to draw text and shapes. |
| **MAX7219** | The driver chip on the module that turns the LEDs on and off for you. |
| **SPI** | A simple scheme chips use to talk to each other over a few shared wires. |
| **Cascade / chain** | Joining modules end-to-end so one set of wires drives all of them. |
| **GPIO** | "General-purpose input/output" — a numbered signal pin on your board. |
| **Library** | Ready-made code you install once and reuse, instead of writing it yourself. |
| **Sketch** | The name for an Arduino program (a `.ino` file). |
| **Software SPI** | Letting you pick any pins for the data/clock wires (the code does the timing). |
