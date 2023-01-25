#include "LedManager.h"

LedManager::LedManager(unsigned long updateInterval, void (*callback)(uint32_t)) {
  this->updateInterval = updateInterval;
  this->callback = callback;
  this->leds = new LedState[32];
  for (unsigned int i = 0; i < 32; i++) this->leds[i] = off;
}

void LedManager::setStatus(uint32_t status) {
  for (unsigned int led = 0; led < 32; led++) {
    this->leds[led] = ((status >> led) &0x01)?on:off;
  }
}

uint32_t LedManager::getStatus() {
  uint32_t status = 0;

  for (unsigned int led = 0; led < 32; led++) {
    switch (this->leds[led]) {
      case off: case flashOff: case twiceOff: case thriceOff:
        status &= ~(0x01 << led);
        break;
      default:
        status |= (0x01 << led);
        break;
    }
  }
  return(status);
}

void LedManager::setLedState(unsigned int led, LedState state) {
  this->leds[led] = state;
}

LedManager::LedState LedManager::getLedState(unsigned int led) {
    return(this->leds[led]);
}

void LedManager::update(bool force, bool performCallback) {
  static unsigned long deadline = 0UL;
  unsigned long now = millis();
  unsigned char status = this->getStatus();

  if (((this->updateInterval) && (now > deadline)) || (force)) {
    for (unsigned int led = 0; led < 32; led++) {
      switch (this->leds[led]) {
        case on: case off:
          break;
        case once:
          this->leds[led] = off;
          break;
        case twice:
          this->leds[led] = twiceOff;
          break;
        case twiceOff:
          this->leds[led] = once;
          break;
        case thrice:
          this->leds[led] = thriceOff;
          break;
        case thriceOff:
          this->leds[led] = twice;
          break;
        case flash:
          this->leds[led] = flashOff;
          break;
        case flashOff:
          this->leds[led] = flash;
      }
    }
    if (this->updateInterval) deadline = (now + this->updateInterval);
  }
  if ((performCallback) && (this->callback)) this->callback(this->getStatus());
}
