#ifndef LED_MANAGER_H
#define LED_MANAGER_H

#include <Arduino.h>
#include <IC74HC595.h>
 
/**
 * @brief Class for managing a bank of abstract LEDs.
 * 
 * LedManager is used to manage a bank of from 1 to 32 abstract LEDs.
 * The bank can be set and interrogated either en-masse or one LED at a
 * time.
 * 
 * The manager provides some simple flash-based automations based on a
 * user-defined update interval and supports a linked callback which
 * allows the host application to express the current state of the LED
 * bank on some external entity like a physical LED array or GUI.
 */
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
     * @brief Construct a new LED bank initialised to all off.
     * 
     * @param updateInterval - the frequency at which to update the LED
     *        bank (equates to the flash rate).
     * @param callback - function called by update() at the specified
     *        update interval with a bit-map representation of the LED
     *        bank status.
     */
    LedManager(unsigned long updateInterval = 200UL, void (*callback)(uint32_t) = 0);

    /**
     * @brief Set the state of LED bank from a bit map.
     * 
     * @param status - bit map specifying the bank state.
     */
    void setStatus(uint32_t status);
    
    /**
     * @brief Get the status of the LED bank as a bit-map.
     * 
     * @return unsigned int - a bitmap representing the current state
     * of the LED bank. 
     */
    uint32_t getStatus(bool performUpdate = false);

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
     * @brief Update the LED bank state, performing any automatic state
     * transitions.
     * 
     * This function should be called directly from loop(): it force is
     * omitted or set false then it will only execute once every
     * update interval as specified in the constructor. Normally the
     * configured callback will be invoked each time the LED bank is
     * updated.
     * 
     * @param force - if true, then ignore the configured update
     * interval and perform the LED bank update immediately.
     * @param performCallback - if false, then after any update do not
     * invoke the callback function. 
     */
    void update(bool force = false, bool performCallback = true);

  private:
    void (*callback)(unsigned char);    
    unsigned long updateInterval;
    LedState *leds;

};

#endif