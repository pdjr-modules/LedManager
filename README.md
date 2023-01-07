# StatusLeds

Class to provide a control interface and update mechanism for an
arbitrarily sized bank of LEDs. Each LED in the banks identified by
an integer index starting from zero.

## CONSTRUCTORS

### StatusLeds(nleds)

Create a StatusLeds instance for handling up to **nleds** LEDs with no
support for automatic processing. 

### StatusLeds(nleds, callback)

Create a StatusLeds instance for handling up to **nleds** and process
it automatically by executing the **callback** function every 200
milliseconds. **callback** must have the type signature
```void (**\*callback**)(unsigned char **status**)```

### StatusLeds(nleds, callback, processInterval)

Create a StatusLeds instance for handling up to **nleds** and process
automatically by executing the **callback** function every
**processInterval** milliseconds. **callback** must have the type
signature ```void (**\*callback**)(unsigned char **status**)```

## TYPES

### typedef enum eLedState { on, off, once, flash, flashOn, flashOff } LedState

The state of each LED in a StatusLeds collection can be set by the host
application to one of  ```on```, ```off```, ```once``` or ```flash```
(the values ```flashon``` and ```flashoff```) are used internally and,
together with ```once``` are re-assigned values each time getStatus()
is invoked.

## METHODS

### setStatus(status)

Sets the state of all LEDs in a single operation by interpreting bit
values in **status**. The least-significant bit corresponds to LED zero
and a binary 1 is mapped to ```on```, a binary 0 to ```off```.

### getStatus()

Returns the current state of all LEDs as an unsigned char where each bit
represents the ```on``` or ```off``` condition of the associated LED.

### getStatus(performUpdate)

As getStatus(), but if **performUpdate** is true, then execute the
update() method after computing the status return value.

### setLedState(led, state)

Set the state of the LED idexed by **led** to LedState **state**.

### getLedState(led)

Returns the current state of the LED indexed by **led** as an LedState
value: ```off``` maps to binary 0, all other states to binary 1.

### update()

Updates each LED channel by transforming ```once``` to ```off```,
```flash``` to ```flashon```, ```flashon``` to ```flashoff``` and
```flashoff``` to ```flashon```.

### process()

This method will typically be called from loop.

If the process interval (defined at instantiation) has elapsed, then
computes the current LED status using the getStatus() method and passes
the result as an argument to any defined callback function, afterwards
calling the update() method to automate any required LED state
transformations. 

### process(update)

As process(), except that the update() method is only called if
**update** is true.

### process(update, force)

As process(update), except that processing will be performed
immediately (i.e. without regard for any defined process interval).