# StatusLeds

Class to provide a control interface and update mechanism for an
arbitrarily sized bank of LEDs.

Each LED in the bank can be set by the host application to ON,
OFF, ONCE or FLASH

A process callback function can be scheduled to execute at a defined
interval and be used by the application to update LED indicators,
either real or virtual, using an appropriate mechanism.

Example:

```
void myCallback(unsigned char status) {
    for (int i = 0; i < 8; i++) {
        
    }
}
StatusLeds myLeds(8, 200, myCallback);

using whatever mechanism 
which correspondsThe size of the bank is specified by the host application
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