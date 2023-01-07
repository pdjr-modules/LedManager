#include "StatusLeds.h"

StatusLeds::StatusLeds(unsigned int nleds, unsigned long updateInterval, void (*callback)(unsigned char)) {
  this->nleds = nleds;
  this->callback = callback;
  this->updateInterval = updateInterval;

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
      default:
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

void StatusLeds::update(bool force, bool performCallback) {
  static unsigned long deadline = 0UL;
  unsigned long now = millis();
  unsigned char status = this->getStatus();

  if ((now > deadline) || (force)) {
    for (unsigned int led = 0; led < this->nleds; led++) {
      switch (this->leds[led]) {
        case on: case off:
          break;
        case once:
          this->leds[led] = off;
          break;
        case twice:
          this->leds[led] = once;
          break;
        case thrice:
          this->leds[led] = twice;
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
    if (this->updateInterval) deadline = (now + this->updateInterval);
  }
  if ((performCallback) && (this->callback)) this->callback(status);
}
