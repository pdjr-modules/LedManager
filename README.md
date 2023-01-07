# StatusLeds

Manage and process the state of an arbitrarily sized collection of LEDs
where each LED in the banknis identified by a zero-based integer index.

An update mechanism (implemented by the update() method) supports
automation of some state transitions allowing flashing of individual LEDs
at a user determined rate.
Updates can be triggered manually, but will usually be invoked
periodically by a built-in timer.

A callback interface allows an external function to be updated with the
LED collection status at each update.
The callback function will typically be used by an application to
operate some specific interface so that it reflects StatusLeds'
internal state.

## CONSTRUCTORS

### StatusLeds()

Create a StatusLeds instance for handling up to eight LEDS. Automatic
update is disabled.

### StatusLeds(*nleds*)

Create a StatusLeds instance for handling up to *nleds* LEDs.
Automatic update is disabled.

### StatusLeds(*nleds*, *updateInterval*)

Create a StatusLeds instance for handling up to *nleds* with an
automatic update interval of *updateInterval* milliseconds.

### StatusLeds(*nleds*, *updateInterval*, *callback*)

Create a StatusLeds instance for handling up to *nleds* with an
automatic update interval *updateInterval* millisecods. At each
each update interval the function *callback* will be invoked with
the status of the LED collection passed as its only argument.

## TYPES

### typedef enum eLedState { on, off, once, twice, thrice, flash, flashOn, flashOff } LedState

The state of each LED in a StatusLeds collection can be set by the host
application to one of  ```on```, ```off```, ```once```, ```twice```,
```thrice``` or ```flash``` (the values ```flashon``` and ```flashoff```)
are used internally.

## METHODS

### setStatus(*status*)

Sets the state of all LEDs in a single operation by interpreting bit
values in *status*. The least-significant bit corresponds to LED zero
and a binary 1 is mapped to ```on```, a binary 0 to ```off```.

### getStatus()

Returns the current state of all LEDs as an unsigned char where each bit
represents the real-time state of the corresponding LED.

### getStatus(*performUpdate*)

As getStatus(), but if *performUpdate* is true, then execute the
update() method after computing the status return value.

### setLedState(*led*, *state*)

Set the state of the LED indexed by *led* to LedState *state*.

### getLedState(*led*)

Returns the current state of the LED indexed by *led* as an LedState
value.

### update()

If a non-zero updateInterval was defined at instantiation and the
interval since last update has expired, then update each LED channel
by transforming ```thrice``` to ```twice```, ```twice``` to ```once```,
```once``` to ```off```, ```flash``` to ```flashOn```, ```flashOn```
to ```flashOff``` and ```flashOff``` to ```flashOn```.
The update interval timer is reset. 

### update(*force*)

As above, except that the update can be performed immediately by
setting *force* to true.

### update(*force*, *performCallback*)

As above except after the update has been completed and if
*performCallback* is true and a callback function was defined
at instantiation the the callback function is executed with the
value of getStatus() as returned at the start of update.

