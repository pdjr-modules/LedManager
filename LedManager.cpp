/**********************************************************************
 * LedManager.cpp - manage an arbitrary number of leds.
 * 2020 (c) Paul Reeve <preeve@pdjr.eu>
 */

#include <cstddef>
#include "Arduino.h"
#include "LedManager.h"

/**********************************************************************
 * Create a new LedManager instance with optional <heartbeat> (in
 * milliseconds) and <interval> in heartbeats.
 * 
 * <heartbeat> defines the flasher's basic period and applies to both
 * on and off phases whilst <interval> defines the quiescent period
 * between flash cycles.
 */
tLedManager::tLedManager(void (*callback)(unsigned int status), unsigned long interval) {
  this->callback = callback;
  this->interval = interval;

  this->modes = new int[tLedManager::LED_COUNT];
  for (unsigned int i = 0; i < tLedManager::LED_COUNT; i++) this->modes[i] = tLedManager::OFF;
  this->deadline = 0UL;
}

void tLedManager::setStatus(unsigned int status) {
  for (unsigned int i = 0; i < tLedManager::LED_COUNT; i++) this->modes[i] = (status & (1 << i))?tLedManager::ON:tLedManager::OFF;
}

void tLedManager::setLedState(unsigned int led, tLedManager::Mode mode) {
  if (led < tLedManager::LED_COUNT) this->modes[led] = mode;
}

void tLedManager::update() {
  unsigned long now = millis();
  unsigned int status = 0;

  if (now > this->deadline) {
    for (unsigned int i = 0; i < tLedManager::LED_COUNT; i++) {
      status <<= 1;
      switch (this->modes[i]) {
        case tLedManager::THRICE: status |= 1; this->modes[i] = tLedManager::THRICE_OFF; break;
        case tLedManager::THRICE_OFF: this->modes[i] = tLedManager::TWICE; break;
        case tLedManager::TWICE: status |= 1; this->modes[i] = tLedManager::TWICE_OFF; break;
        case tLedManager::TWICE_OFF: this->modes[i] = tLedManager::ONCE; break;
        case tLedManager::ONCE: status |= 1; this->modes[i] = tLedManager::OFF; break;
        case tLedManager::FLASH: status |= 1; this->modes[i] = tLedManager::FLASH_OFF; break;
        case tLedManager::FLASH_OFF: this->modes[i] = tLedManager::FLASH; break;
        case tLedManager::ON: status |= 1; break;
        case tLedManager::OFF: break;
      }
    }
    this->callback(status);
    this->deadline = (now + this->interval);
  }
}
