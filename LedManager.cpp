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
LedManager::LedManager(void (*callback)(unsigned int status), unsigned long interval) {
  this->callback = callback;
  this->interval = interval;

  this->states = new int[LedManager::LED_COUNT];
  for (unsigned int i = 0; i < LedManager::LED_COUNT; i++) this->states[i] = LedManager::OFF;
  this->deadline = 0UL;
}

void LedManager::setStatus(unsigned int status) {
  for (unsigned int i = 0; i < LedManager::LED_COUNT; i++) this->states[i] = (status & (1 << i))?LedManager::ON:LedManager::OFF;
}

void LedManager::setLedState(unsigned int led, LedManager::Pattern pattern) {
  if (led < LedManager::LED_COUNT) this->states[led] = pattern;
}

void LedManager::update() {
  unsigned long now = millis();
  unsigned int status = 0;

  if (now > this->deadline) {
    for (unsigned int i = 0; i < LedManager::LED_COUNT; i++) {
      status <<= 1;
      switch (this->states[i]) {
        case LedManager::THRICE: status |= 1; this->states[i] = LedManager::THRICE_OFF; break;
        case LedManager::THRICE_OFF: this->states[i] = LedManager::TWICE; break;
        case LedManager::TWICE: status |= 1; this->states[i] = LedManager::TWICE_OFF; break;
        case LedManager::TWICE_OFF: this->states[i] = LedManager::ONCE; break;
        case LedManager::ONCE: status |= 1; this->states[i] = LedManager::OFF; break;
        case LedManager::FLASH: status |= 1; this->states[i] = LedManager::FLASH_OFF; break;
        case LedManager::FLASH_OFF: this->states[i] = LedManager::FLASH; break;
        case LedManager::ON: status |= 1; break;
        case LedManager::OFF: break;
      }
    }
    this->callback(status);
    this->deadline = (now + this->interval);
  }
}
