# Function

This module is an 8×8 pixel matrix LED display (driven by the **MAX7219** chip) that can show characters, patterns, animations, and more. Controlled through an SPI-style interface, it can turn each of the 64 LEDs on or off individually, suitable for making information displays, animation effects, and other applications.

# Appearance

| ![Front](images/TK52-F.png) | ![Back](images/TK52-B.png) | ![Side](images/TK52-S.png) |
| :-----------------------: | :-----------------------: | :-----------------------: |
|          **Front**          |          **Back**          |          **Side**          |

The module has an 8×8 LED matrix display and a 6-pin header interface. Each pin can be identified by the silkscreen (text printed next to the pin).

# Pinout

- **GND** (negative): Like the negative terminal (-) of a battery, connect to the control board's GND
- **VCC** (positive): Like the positive terminal (+) of a battery, connect to the control board's 5V (this module requires 5V power supply)
- **CS** (chip select): SPI chip select signal, connect to the control board's digital pin (e.g. Arduino D10 or Pico GPIO 5)
- **DIN** (data input): SPI data input pin, connect to the control board's SPI data pin (e.g. Arduino D11 or Pico GPIO 19)
- **NC** (no connection): No actual circuit connection, included for unified interface, can be left unconnected
- **CLK** (clock): SPI clock signal, connect to the control board's SPI clock pin (e.g. Arduino D13 or Pico GPIO 18)

# Features

- 8×8 pixel monochrome display (64 individually controllable LEDs)
- MAX7219 driver, controlled over a 3-wire SPI-style interface
- Adjustable brightness (16 levels) and easy to cascade more modules
- Operating voltage: 5V

# Quick Wiring

1. GND → Control board GND
2. VCC → Control board 5V
3. CS → Control board digital pin (e.g. D10)
4. DIN → Control board SPI data pin (e.g. D11)
5. CLK → Control board SPI clock pin (e.g. D13)
