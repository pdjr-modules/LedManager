#ifndef STATUS_LEDS_H
#define STATUS_LEDS_H

#include <Arduino.h>
#include <IC74HC595.h>
 
class StatusLeds {

  public:
    typedef enum eLedState { on, off, flash, once, flashOn, flashOff } LedState;

    StatusLeds(unsigned int nleds, void (*callback)(unsigned char) = 0, unsigned long processInterval = 200UL);
    void setStatus(unsigned char status);
    unsigned char getStatus(bool performUpdate = false);
    void setLedState(unsigned int led, LedState state);
    StatusLeds::LedState getLedState(unsigned int led);
    void update();
    void process(bool performUpdate = true, bool force = false);

  private:
    unsigned int nleds;
    void (*callback)(unsigned char);    
    unsigned long processInterval;
    LedState *leds;

};

#endif