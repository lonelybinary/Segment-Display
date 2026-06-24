# Example 2: Scrolling Text
#
# Board:   ESP32-S3 (running MicroPython)
# Display: 32x8 MAX7219 dot matrix (four 8x8 modules, "FC-16" 4-in-1 board)
# Library: max7219.py  (mcauser/micropython-max7219)
#
# Goal: scroll a message across all 32 columns - the signature 32x8 demo.
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

# Trailing spaces give a clean gap before the message repeats.
message = "Lonely Binary - 32x8 MAX7219 on ESP32-S3   "

while True:
    # Each character is 8 pixels wide.
    width = len(message) * 8
    # Slide the text from just off the right edge (x=32) to fully off the left.
    for x in range(32, -width, -1):
        display.fill(0)
        display.text(message, x, 0, 1)
        display.show()
        time.sleep_ms(50)     # smaller = faster scrolling
