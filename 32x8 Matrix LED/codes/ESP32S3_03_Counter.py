# Example 3: Counter
#
# Board:   ESP32-S3 (running MicroPython)
# Display: 32x8 MAX7219 dot matrix (four 8x8 modules, "FC-16" 4-in-1 board)
# Library: max7219.py  (mcauser/micropython-max7219)
#
# Goal: show a live, updating value - a 4-digit counter that ticks up once
#       per second. The built-in font is 8 px wide, so four digits (4 x 8 = 32)
#       fill the screen exactly. A "MM:SS" clock needs 5 characters (40 px),
#       which is wider than 32 px - scroll it (see Example 2) if you need one.
#
# Wiring (ESP32-S3):
#   VCC -> 5V        DIN -> GPIO 11
#   GND -> GND       CLK -> GPIO 12
#                    CS  -> GPIO 10

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
    text = "{:04d}".format(count)   # always 4 digits, e.g. "0007"
    display.fill(0)
    display.text(text, 0, 0, 1)
    display.show()

    count = (count + 1) % 10000       # wrap back to 0 after 9999
    time.sleep(1)
