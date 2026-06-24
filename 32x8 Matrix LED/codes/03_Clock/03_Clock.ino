/*
 * Example 3: Scrolling Clock / Counter
 *
 * Board:   ESP32-S3  or  Arduino UNO R3  (same sketch, same pins)
 * Display: 32x8 MAX7219 dot matrix (four 8x8 modules, "FC-16" 4-in-1 board)
 * Library: MD_Parola + MD_MAX72XX
 *
 * Goal: show a live, updating value - a stopwatch counting MM:SS since the
 *       board powered on. No extra hardware (no RTC) needed: it uses millis().
 *       Swap in an NTP or RTC time source later for a real wall clock.
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

char timeBuf[6];                 // holds "MM:SS" plus the end-of-string marker
unsigned long lastUpdate = 0;    // when we last refreshed the screen

// Build the "MM:SS" string from how long the board has been running.
void updateTime() {
  unsigned long totalSeconds = millis() / 1000;
  int minutes = (totalSeconds / 60) % 100;   // wrap at 99 minutes
  int seconds = totalSeconds % 60;
  sprintf(timeBuf, "%02d:%02d", minutes, seconds);
}

void setup() {
  display.begin();
  display.setIntensity(5);
  display.displayClear();
  display.setTextAlignment(PA_CENTER);

  updateTime();
  display.print(timeBuf);
}

void loop() {
  // Refresh once per second so the seconds tick.
  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();
    updateTime();
    display.print(timeBuf);
  }
}
