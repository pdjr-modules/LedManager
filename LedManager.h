#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include <Arduino.h>
#include <IC74HC595.h>
 
class LedManager {

  public:
    /**
     * @brief Enum type defining the supported LED static and dynamic states.
     * 
     * on     - LED is permanently on.
     * off    - LED is permanently off.
     * flash  - LED is permanently equi-phase flashing.
     * once   - LED will flash once then revert to off.
     * twice  - LED will flash twice then revert to off.
     * thrice - LED will flash three times then revert to off.
     */
    typedef enum { on, off, flash, once, twice, thrice, twiceOff, thriceOff, flashOff } LedState;

    /**
     * @brief Construct a new Led Manager object.
     * 
     * @param nleds - the number of LEDs in the bank.
     * @param updateInterval - the frequency at which to update the LED
     *        bank (equates to the flash rate).
     * @param callback - function called by update() at the specified
     *        update interval with a bit-map representation of the LED
     *        bank status.
     */
    LedManager(unsigned int nleds = 8, unsigned long updateInterval = 200UL, void (*callback)(unsigned char) = 0);

    /**
     * @brief Set the state of LEDs in the bank en-masse.
     * 
     * @param status - bit map specifying the bank state.
     */
    void setStatus(unsigned char status);
    
    /**
     * @brief Get the status of the LED bank as a bit-map and
     * (optionally) invoke the update callback.
     * 
     * @param performUpdate - whether or not to invoke the update
     * callback.
     * @return unsigned char - a bitmap representing the current state
     * of the LED bank. 
     */
    unsigned char getStatus(bool performUpdate = false);

    /**
     * @brief Set the state of a single LED.
     * 
     * @param led - the index number of the LED.
     * @param state - the new LED state.
     */
    void setLedState(unsigned int led, LedState state);

    /**
     * @brief Get the state of a single LED.
     * 
     * @param led  - the index number of the LED.
     * @return LedManager::LedState - the current state of the selected
     * LED.
     */
    LedManager::LedState getLedState(unsigned int led);

    /**
     * @brief Update the LED bank state, performing all
     * necessary state transitions.
     * 
     * @param force - if true, then ignore the configured update
     * interval and perform the LED bank update immediately.
     * @param performCallback - if true, then after any update invoke
     * the callback function. 
     */
    void update(bool force = false, bool performCallback = false);

  private:
    unsigned int nleds;
    void (*callback)(unsigned char);    
    unsigned long updateInterval;
    LedState *leds;

};

#endif