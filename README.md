# Segment-Display

This repository contains display products and Arduino UNO R3 demo sketches.

## What Is This?

This repository is a collection of **LED segment and matrix display** projects. Each project shows you how to wire a display, upload code, and make it show numbers or animations. Most projects use an **Arduino UNO R3** — a small, beginner-friendly microcontroller board — and some also include **ESP32-S3** or **Raspberry Pi Pico** examples.

You do not need prior electronics experience. Just follow the wiring diagrams and code in each folder.

## What You Need to Get Started

- An **Arduino UNO R3** board
- A **USB cable** (Type-A to Type-B) to connect the Arduino to your computer
- **Arduino IDE** installed on your computer (free at [arduino.cc](https://www.arduino.cc/en/software))
- Jumper wires
- A **soldering iron and solder** — required to attach the pin headers on the driver / display modules (see below)
- The display kit for whichever project you choose

## Hardware Assembly (Soldering Required)

The driver boards and display modules in these kits ship with the **pin headers loose in the bag**. Before you plug a module into a breadboard, a PinPlus Shield, or any other socket, you **must solder the pin header to the row of through-holes** on the module.

> **Friction-fit / jumper-wire / press-and-hold connections through the un-soldered holes are not reliable.** The contact resistance is too high and changes every time a wire shifts, so the display will show wrong segments, missing digits, or nothing at all — symptoms that are very easy to mis-diagnose as a wiring error or a code bug. Soldering the pin header is the only way to get a clean, repeatable connection.

A basic 25–40 W iron and a few minutes per module is all you need. Once the headers are soldered, the module plugs straight into a breadboard or the PinPlus Shield.

## Recommended Learning Order (Start Here)

If you are new to Arduino, work through the projects in this order — from simplest to most advanced:

| Step | Project | Why start here? |
| :--: | :-- | :-- |
| 1 | **TK51 – TM1637 4-Digit Display** | Only 4 wires; one simple library call. Perfect for a first project. |
| 2 | **Ten Seg LED Bar Display** | Controls 10 LEDs directly — great for learning `digitalWrite` and `for` loops. |
| 3 | **0.56 inch Seven Seg Display** | Introduces shift registers and binary segment patterns. |
| 4 | **0.28 inch Eight-Digit Seven Seg Display** | Introduces a driver IC library (MAX7219) and multi-digit control. |
| 5 | **4 inch Seven Seg Display** | Larger display, external power, and chaining (cascading) multiple modules. |
| 6 | **TK52 – 8×8 Matrix LED** | Your first dot-matrix — draw patterns pixel by pixel with the MAX7219. |
| 7 | **32×8 Matrix LED** | Four chained 8×8 modules for scrolling text and clocks (ESP32-S3 or UNO). |

## Glossary

New to electronics? Here are the key words used throughout this repository:

| Term | Plain-English meaning |
| :-- | :-- |
| **LED** | Light-Emitting Diode — a tiny light that turns on when electricity flows through it |
| **Segment** | One individual LED bar inside a 7-segment or bar display |
| **Digital pin** | A pin on the Arduino that outputs either 5 V (HIGH) or 0 V (LOW) — like a light switch |
| **Active-low** | A wiring style where `LOW` (0 V) turns the LED **on** and `HIGH` (5 V) turns it **off** — the opposite of what you might expect |
| **GND** | Ground — the 0 V reference for all circuits; every component must share a common GND |
| **Shift register** | A chip (e.g. 74HC595) that converts **3 wires** of serial data into **8 parallel outputs**, so you can control 8 LEDs with just 3 Arduino pins |
| **Cascade / chain** | Connecting multiple modules in a line so one set of 3 wires controls all of them |
| **Common cathode** | A 7-segment display where all segment LEDs share a single GND pin; a segment turns on when its pin goes HIGH |
| **Common anode** | A 7-segment display where all segment LEDs share a single 5 V pin; a segment turns on when its pin goes LOW |
| **Library** | A collection of pre-written code you can reuse; install once and call its functions instead of writing everything yourself |
| **`#define`** | A way to give a name to a number (e.g. `#define CLK_PIN 2` means "wherever I write `CLK_PIN`, use the number 2") |
| **`#include`** | Loads a library into your sketch so you can use its functions |
| **Binary** | A number written using only 0s and 1s; in code, written as `0b00111111`. Each bit can turn one LED segment on or off |
| **Hexadecimal (hex)** | A compact way to write binary numbers using digits 0–9 and letters A–F; in code, written as `0x3F` |
| **Multiplexing** | Switching between display positions very rapidly (faster than your eye can see) so a single driver chip can control many digits |
| **`%` (modulo)** | Gives the remainder after division; `37 % 10 = 7` extracts the ones digit from 37 |
| **`setup()`** | An Arduino function that runs **once** when the board powers on — use it to configure pins and set starting states |
| **`loop()`** | An Arduino function that runs **over and over forever** — use it for animations and ongoing behavior |

## Products

### Ten Seg LED Bar Display Kit

- Docs: `10 Seg LED Bar Display/README.md`
- Arduino UNO R3 sketch: `10 Seg LED Bar Display/codes/Uno_10SEG.ino`

### 0.56 inch Seven Seg Display Kit

- Docs: `0.56-inch Seven Seg Display/README.md`
- Arduino UNO R3 sketch: `0.56-inch Seven Seg Display/codes/Uno_056SEG.ino`

### 0.28 inch Eight-Digit Seven Seg Display

- Docs: `0.28-inch Seven Seg Display/README.md`
- Arduino UNO R3 sketch: `0.28-inch Seven Seg Display/codes/Uno_0288SEG.ino` (requires **LedControl** library; **MAX7219** **DIN / CLK / CS**)

### 4 inch Seven Seg Display

- Docs: `4-inch Seven Seg Display/README.md`
- Arduino UNO R3 sketch: `4-inch Seven Seg Display/codes/Uno_47SEG.ino` (set `NUM_DIGITS` for one module or a cascade chain)

### TK51 – TM1637 4-Digit Display

- Docs: `4-Digit Display (TK51)/README.md`
- Arduino UNO R3 sketch: `4-Digit Display (TK51)/codes/Uno_TK51.ino` (requires **TM1637Display** library)

### TK52 – 8×8 Matrix LED (MAX7219)

- Docs: `8x8 Matrix LED (TK52)/README.md`
- Arduino UNO R3 sketch: `8x8 Matrix LED (TK52)/codes/Arduino_TK52.ino` (requires **LedControl** library)
- MicroPython script (Raspberry Pi Pico): `8x8 Matrix LED (TK52)/codes/MicroPython_TK52.py`

### 32×8 Matrix LED (MAX7219)

- Docs: `32x8 Matrix LED/README.md`
- Arduino sketches: `32x8 Matrix LED/codes/0*.ino` — the **same sketches run on both ESP32-S3 and Arduino UNO R3** (requires **MD_Parola** + **MD_MAX72XX** libraries; four cascaded 8×8 MAX7219 modules)
- MicroPython scripts: `32x8 Matrix LED/codes/ESP32S3_*.py` — **ESP32-S3 only** (requires **max7219.py** library)
- Beginner examples: First Light → Scrolling Text → Clock / Counter.
