#ifndef STATUS_LEDS_H
#define STATUS_LEDS_H

#include <Arduino.h>
#include <IC74HC595.h>

/**********************************************************************
 * Class to provide a control interface and update mechanism for a bank
 * of LEDs. The size of the bank is specified by the host application
 * and and the status of the bank is handed to a callback function at a
 * regular, user-defined, interval. The callback has responsibility for
 * setting the hardware to which real LEDs are connected to the
 * condition reported by status.
 * 
 * CONSTRUCTOR
 *
 * StatusLeds(nleds, processInterval, callback)
 * Create a new StatusLeds instance to operate <nleds> LEDs. If
 * automatic, periodic, status reporting is required then <callback>
 * should specify a function to which status can be passed at the
 * frequency defined by <processInterval> milliseconds.
 * 
 * METHODS
 * 
 * setStatus(status)
 * Sets the state of all LEDs to either on or off from the bit values
 * of <status>.
 * 
 * getStatus()
 * Returns an unsigned char representing the current state of al LEDs.
 * 
 * setLedState(led, state)
 * Set the state of LED <led> to the value supplied by state (i.e. one
 * of on, off, once or flash).
 * 
 * getLedState(led)
 * Returns unsigned char representing the current state of LED <led>.
 * The value should be cast into an enum in the following way:
 *   (StatusLeds::Ledstate) myStatusLeds.getState(4);
 */
 
class StatusLeds {

  public:
    enum LedState { on, off, flash, once, flashOn, flashOff };

    StatusLeds(unsigned int nleds, unsigned long processInterval, void (*callback)(unsigned char));

    void setStatus(unsigned char status);
    unsigned char getStatus();

    void setLedState(unsigned int led, LedState state);
    unsigned char getLedState(unsigned int led);

    void process();

  private:
    unsigned int nleds;
    unsigned long processInterval;
    void (*callback)(unsigned char);
    
    unsigned char *leds;

};

#endif