# Segment-Display

This repository contains display products and Arduino UNO R3 demo sketches.

## What Is This?

This repository is a collection of **LED segment display** projects for Arduino. Each project shows you how to wire a display, upload code, and make it show numbers or animations. Everything uses an **Arduino UNO R3** — a small, beginner-friendly microcontroller board.

You do not need prior electronics experience. Just follow the wiring diagrams and code in each folder.

## What You Need to Get Started

- An **Arduino UNO R3** board
- A **USB cable** (Type-A to Type-B) to connect the Arduino to your computer
- **Arduino IDE** installed on your computer (free at [arduino.cc](https://www.arduino.cc/en/software))
- Jumper wires
- The display kit for whichever project you choose

## Recommended Learning Order (Start Here)

If you are new to Arduino, work through the projects in this order — from simplest to most advanced:

| Step | Project | Why start here? |
| :--: | :-- | :-- |
| 1 | **TK51 – TM1637 4-Digit Display** | Only 4 wires; one simple library call. Perfect for a first project. |
| 2 | **Ten Seg LED Bar Display** | Controls 10 LEDs directly — great for learning `digitalWrite` and `for` loops. |
| 3 | **0.56 inch Seven Seg Display** | Introduces shift registers and binary segment patterns. |
| 4 | **0.28 inch Eight-Digit Seven Seg Display** | Introduces a driver IC library (MAX7219) and multi-digit control. |
| 5 | **4 inch Seven Seg Display** | Larger display, external power, and chaining (cascading) multiple modules. |

## Products

### Ten Seg LED Bar Display Kit

- Docs: `Ten Seg LED Bar Display/README.md`
- Arduino UNO R3 sketch: `Ten Seg LED Bar Display/codes/Uno_10SEG.ino`

### 0.56 inch Seven Seg Display Kit

- Docs: `0.56 inch Seven Seg Display/README.md`
- Arduino UNO R3 sketch: `0.56 inch Seven Seg Display/codes/Uno_056SEG.ino`

### 0.28 inch Eight-Digit Seven Seg Display

- Docs: `0.28 inch Seven Seg Display/README.md`
- Arduino UNO R3 sketch: `0.28 inch Seven Seg Display/codes/Uno_0288SEG.ino` (requires **LedControl** library; **MAX7219** **DIN / CLK / CS**)

### 4 inch Seven Seg Display

- Docs: `4 inch Seven Seg Display/README.md`
- Arduino UNO R3 sketch: `4 inch Seven Seg Display/codes/Uno_47SEG.ino` (set `NUM_DIGITS` for one module or a cascade chain)

### TK51 – TM1637 4-Digit Display

- Docs: `TK51 - TM1637 4-Digit Display/README.md`
- Arduino UNO R3 sketch: `TK51 - TM1637 4-Digit Display/codes/Uno_TK51.ino` (requires **TM1637Display** library)
