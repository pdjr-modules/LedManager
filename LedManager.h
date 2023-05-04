/**********************************************************************
 * LedManager.h - manage an arbitrary number of leds.
 * 2020 (c) Paul Reeve <preeve@pdjr.eu>
 */

#ifndef LEDMANAGER_H
#define LEDMANAGER_H

/**
 * @brief Class providing the logic for operating one or more notional
 * LEDs. 
 */
class tLedManager {

  public:
    /**
     * @brief Maximum number of LEDs in a control group. LED state is
     * output as an unsigned integer, so this value has a maximum equal
     * to the number of bits in an integer on the host platform.
     */
    static const unsigned int LED_COUNT = 16;

    /**
     * @brief Enum defining possible LED states.
     * 
     * ON and OFF provide steady-state control. FLASH implies continuous
     * isophase flashing. ONCE, TWICE and THRICE imply the indicated
     * number of flashes.
     */
    enum Mode { ON, FLASH, ONCE, TWICE, THRICE, OFF, FLASH_OFF, TWICE_OFF, THRICE_OFF };

    /**
     * @brief Construct a new tLedManager instance
     * 
     * @param callback - function to operate a physical output device.
     * @param interval - equiphase heartbeat interval in milliseconds.
     * 
     * Instantiates a new control group with the state of all LEDs
     * initialised to OFF.
     * 
     * Every @ref interval milliseconds the @ref callback function is
     * invoked with its @ref status argument set to represent the
     * current state of the control group: a 0 bit value says 'off'; a
     * 1 bit value says 'on'.
     */
    tLedManager(void (*callback)(unsigned int status), unsigned long interval = 200);

    /**
     * @brief Set the Mode of each LED in the contro group to ON or
     * OFF.
     * 
     * @param status - Set the LedManager::Mode of the LED group.
     * 
     * If a bit in @ref is 1, the corresponding LED Mode is set ON; a 0
     * bit sets the corresponding LED Mode to OFF.
     */
    void setStatus(unsigned int status);

    /**
     * @brief Set the state of particular LED.
     * 
     * @param led - index of the LED to be updated.
     * @param mode - the Mode to be assigned.
     */
    void setLedState(unsigned int led, tLedManager::Mode mode);
    
    /**
     * @brief Perform a mode transition on all LEDs in the control
     * group at the specified update interval.
     * 
     * This method should be called from the host loop().
     */
    void update();

  private:
    void (*callback)(unsigned int status);
    unsigned int interval;
    int *modes;
    unsigned long deadline;
};

#endif
