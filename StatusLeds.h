#ifndef STATUS_LEDS_H
#define STATUS_LEDS_H

#include <Arduino.h>
#include <IC74HC595.h>
 
class StatusLeds {

  public:
    typedef enum eLedState { on, off, flash, once, flashOn, flashOff } LedState;

    StatusLeds(unsigned int nleds, unsigned long processInterval, void (*callback)(unsigned char));
    void setStatus(unsigned char status);
    unsigned char getStatus();
    void setLedState(unsigned int led, LedState state);
    StatusLeds::LedState getLedState(unsigned int led);
    void process();

  private:
    unsigned int nleds;
    unsigned long processInterval;
    void (*callback)(unsigned char);    
    LedState *leds;

};

#endif