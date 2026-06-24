/*
 * Example 2: Scrolling Text
 *
 * Board:   ESP32-S3  or  Arduino UNO R3  (same sketch, same pins)
 * Display: 32x8 MAX7219 dot matrix (four 8x8 modules, "FC-16" 4-in-1 board)
 * Library: MD_Parola + MD_MAX72XX
 *
 * Goal: scroll a message across all 32 columns. This is the signature
 *       use of a 32x8 display - text longer than the screen scrolls by.
 *
 * Wiring (the pin numbers are the same on both boards):
 *   VCC -> 5V        DIN -> pin 11
 *   GND -> GND       CLK -> pin 12
 *                    CS  -> pin 10
 *
 * Power: for text at moderate brightness, the board's 5V pin is fine.
 *        For a bright, full-screen image use a separate 5V supply (common GND).
 */

#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define DATA_PIN 11
#define CLK_PIN  12
#define CS_PIN   10

MD_Parola display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

const char *message = "Lonely Binary - 32x8 MAX7219 on ESP32-S3";

void setup() {
  display.begin();
  display.setIntensity(5);
  display.displayClear();

  // displayText(text, alignment, scrollSpeed_ms, pauseAtEnd_ms, entryEffect, exitEffect)
  // Smaller scroll speed = faster scrolling.
  display.displayText(message, PA_LEFT, 80, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void loop() {
  // displayAnimate() returns true when the message finishes; restart it.
  if (display.displayAnimate()) {
    display.displayReset();
  }
}
