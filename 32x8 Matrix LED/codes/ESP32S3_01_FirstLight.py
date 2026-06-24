# Example 1: First Light
#
# Board:   ESP32-S3 (running MicroPython)
# Display: 32x8 MAX7219 dot matrix (four 8x8 modules, "FC-16" 4-in-1 board)
# Library: max7219.py  (mcauser/micropython-max7219)
#          Copy max7219.py onto the board before running this file.
#
# Goal: show a word on the display. This confirms your wiring is correct.
#
# Wiring (ESP32-S3):
#   VCC -> 5V        DIN -> GPIO 11
#   GND -> GND       CLK -> GPIO 12
#                    CS  -> GPIO 10

from machine import Pin, SPI
import max7219

# Hardware SPI bus 1. These pins are remappable on the ESP32-S3, so they
# only need to match your wiring. (If you get errors, swap to SoftSPI.)
spi = SPI(1, baudrate=10000000, polarity=0, phase=0,
          sck=Pin(12), mosi=Pin(11))
cs = Pin(10, Pin.OUT)

# 4 cascaded 8x8 modules = 32x8 pixels
display = max7219.Matrix8x8(spi, cs, 4)

display.brightness(5)        # 0 (dim) to 15 (bright)
display.fill(0)              # clear the screen

# The built-in font is 8 pixels wide per character, so only 4 characters
# fit on a 32-pixel display at once. For longer words, scroll them (Example 2).
display.text("GOOD", 0, 0, 1)

display.show()               # push the buffer to the LEDs
