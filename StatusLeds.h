#ifndef STATUS_LEDS_H
#define STATUS_LEDS_H

#include <Arduino.h>
#include <IC74HC595.h>
 
class StatusLeds {

  public:
    typedef enum eLedState { on, off, flash, once, twice, thrice, flashOn, flashOff } LedState;

    StatusLeds(unsigned int nleds = 8, unsigned long updateInterval = 200UL, void (*callback)(unsigned char) = 0);
    void setStatus(unsigned char status);
    unsigned char getStatus(bool performUpdate = false);
    void setLedState(unsigned int led, LedState state);
    StatusLeds::LedState getLedState(unsigned int led);
    void update(bool force = false, bool performCallback = false);

  private:
    unsigned int nleds;
    void (*callback)(unsigned char);    
    unsigned long updateInterval;
    LedState *leds;

};

#endif