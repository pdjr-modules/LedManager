#include "StatusLeds.h"

StatusLeds::StatusLeds(unsigned int nleds, void (*callback)(unsigned char), unsigned long processInterval) {
  this->nleds = nleds;
  this->callback = callback;
  this->processInterval = processInterval;

  this->leds = new LedState [this->nleds];
  for (unsigned int i = 0; i < this->nleds; i++) this->leds[i] = off;
}

void StatusLeds::setStatus(unsigned char status) {
  for (unsigned int led = 0; led < this->nleds; led++) {
    this->leds[led] = ((status >> led) &0x01)?on:off;
  }
}

unsigned char getStatus(bool performUpdate) {
  unsigned char status = 0;

  for (unsigned int led = 0; led < this->nleds; led++) {
    switch (this->leds[led]) {
      case off: case flashoff:
        status &= ~(0x01 << led);
        break;
      case on: case once: case flashon:
        status |= (0x01 << led);
        break;
    }
  }
  if (performUpdate) this->update();
  return(status);

}

void StatusLeds::setLedState(unsigned int led, LedState state) {
  this->leds[led] = state;
}

StatusLeds::LedState StatusLeds::getLedState(unsigned int led) {
    return(this->leds[led]);
}

void StatusLeds::update() {
  for (unsigned int led = 0; led < this->nleds; led++) {
    switch (this->leds[led]) {
      case on: case off:
        break;
      case once:
        this->leds[led] = off;
        break;
      case flash:
        this->leds[led] = flashOn;
        break;
      case flashOn:
        this->leds[led] = flashOff;
      case flashOff:
        this->leds[led] = flashOn;
    }
  }
}

void StatusLeds::process(bool performUpdate, bool force) {
  static unsigned long deadline = 0UL;
  unsigned long now = millis();

  if ((now > deadline) || (force)) {
      if (this->callback) this->callback(this->getStatus(performUpdate));
      if (this->processInterval) deadline = (now + this->processInterval);
    }
  }
}
