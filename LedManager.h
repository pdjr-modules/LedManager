#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include <Arduino.h>
#include <IC74HC595.h>
 
class LedManager {

  public:
    typedef enum { on, off, once, twice, twiceOff, thrice, thriceOff, flash, flashOff } LedState;

    LedManager(unsigned int nleds = 8, unsigned long updateInterval = 200UL, void (*callback)(unsigned char) = 0);
    void setStatus(unsigned char status);
    unsigned char getStatus(bool performUpdate = false);
    void setLedState(unsigned int led, LedState state);
    LedManager::LedState getLedState(unsigned int led);
    void update(bool force = false, bool performCallback = false);

  private:
    unsigned int nleds;
    void (*callback)(unsigned char);    
    unsigned long updateInterval;
    LedState *leds;

};

#endif