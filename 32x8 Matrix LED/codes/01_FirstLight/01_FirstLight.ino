/*
 * Example 1: First Light
 *
 * Board:   ESP32-S3  or  Arduino UNO R3  (same sketch, same pins)
 * Display: 32x8 MAX7219 dot matrix (four 8x8 modules, "FC-16" 4-in-1 board)
 * Library: MD_Parola + MD_MAX72XX  (install both from the Arduino Library Manager)
 *
 * Goal: show a word on the display. This is the first test to confirm your
 *       wiring and HARDWARE_TYPE are correct.
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

// The most common 4-in-1 module is the FC-16 type. If your text shows up
// rotated, mirrored, or scrambled, try a different value here:
//   FC16_HW, GENERIC_HW, PAROLA_HW, or ICSTATION_HW
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

#define MAX_DEVICES 4    // four 8x8 modules = 32x8 pixels

#define DATA_PIN 11      // DIN
#define CLK_PIN  12      // CLK
#define CS_PIN   10      // CS

// Create the display object (software SPI: we name all three pins so the
// same wiring and code work on both boards - the ESP32-S3 and the UNO).
MD_Parola display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup() {
  display.begin();            // initialise the display
  display.setIntensity(5);    // brightness: 0 (dim) to 15 (bright)
  display.displayClear();     // turn every LED off

  display.setTextAlignment(PA_CENTER);
  display.print("HELLO");     // proportional font, so "HELLO" fits in 32 px
}

void loop() {
  // Nothing to do: the text stays on screen.
}
