#include "StatusLeds.h"

StatusLeds::StatusLeds(unsigned int nleds, unsigned long processInterval, void (*callback)(unsigned char)) {
  this->nleds = nleds;
  this->processInterval = processInterval;
  this->callback = callback;
  this->leds = new LedState [this->nleds];

  for (unsigned int i = 0; i < this->nleds; i++) this->leds[i] = off;
}

void StatusLeds::setStatus(unsigned char status) {
  for (unsigned int led = 0; led < this->nleds; led++) {
    this->leds[led] = ((status >> led) &0x01)?on:off;
  }
}

void StatusLeds::setLedState(unsigned int led, LedState state) {
  this->leds[led] = state;
}

StatusLeds::LedState StatusLeds::getLedState(unsigned int led) {
    return(this->leds[led]);
}

unsigned char StatusLeds::getStatus() {
  unsigned char status = 0;

  for (unsigned int led = 0; led < this->nleds; led++) {
    switch (this->leds[led]) {
      case on:
        status |= (0x01 << led);
        break;
      case off:
        status &= ~(0x01 << led);
        break;
      case once:
        status |= (0x01 << led);
        this->leds[led] = off;
        break;
      case flash:
        this->leds[led] = flashOn;
        break;
      case flashOn:
        status |= (0x01 << led);
        this->leds[led] = flashOff;
      case flashOff:
        status &= ~(0x01 << led);
        this->leds[led] = flashOn;
    }
  }
  return(status);
}

void StatusLeds::process() {
  static unsigned long deadline = 0UL;
  unsigned long now = millis();

  if (now > deadline) {
    this->callback(this->getStatus());
    deadline = (now + this->processInterval);
  }
}
