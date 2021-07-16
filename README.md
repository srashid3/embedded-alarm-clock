# Embedded Alarm Clock

<div align="left">
  <img src=images/display.jpg width="250" /> <img src=images/overview.jpg width="250" /> <img src=images/internals.jpg width="250" />
</div>

## Environment

Microcontroller: PIC18F4520  
IDE: MPLAB-X  
Compiler: XC8  

## Overview

A custom alarm clock built using interrupts on a PIC microcontroller. After the initial power cycle, the LCD will blink until any input is detected. To adjust the time, hold down the time button and press either the hour, minute, or day button. Follow the same steps except with the alarm button held down to change the alarm. To turn the alarm on, use the red toggle switch. To snooze the alarm, press the minute and day button at the same time.

## Hardware

The I/O is handled on PORTA and PORTD. There are a total of six inputs — five buttons for configuring the clock and one red toggle switch for the alarm. The only output is the buzzer for the alarm. The LCD is configured in 4-bit mode and reads from LATB and LATC. Time is handled using timers TMR0 and TMR2. TMR0 uses the internal oscillator to provide approximate delays during setup. TMR2 uses an external 8MHz crystal to track time with high accuracy. For more detail on the hardware configuration, refer to the public header files.

| PORT     | Function           | Pins         |
|:---------|:-------------------|:-------------|
| PORTA    | Buzzer, Crystal    | RA4, RA6-RA7 |
| PORTD    | Buttons            | RD0-RD5      |
| LATB     | LCD Data           | LATB0-LATB3  |
| LATC     | LCD Configuration  | LATC4-LATC7  |


## Build

To build the application, run the following command:

```
$ make all
```

This will produce both a `main` and `utest` executable. By default the application is built in debug mode, which mocks all the hardware and logs output to the console. To install the application on a PIC, you must build in MPLAB-X with a PICkit programmer. Note that debug mode was implemented after the final product. Therefore, there may be possible compile time errors to fix in MPLAB-X.

The current implementation of the clock also features experimental drift correction. The goal of drift correction is to account for the PPM of the crystal and improve the overall accuracy of the timer in software. This value was determined empirically and can be adjusted by updating `DRIFT_OFFSET` in `<clock/time.h>`. The drift will vary per crystal, so increase or decrease the offset as needed.

## Simulator

To start the simulator, run the `main` executable. Since getchar() is used to mock input, you will need to press enter after each key. The alarm, time, hour, minute, and day buttons are mapped to keys 1-5. The alarm and time buttons will remain held until pressed again. The snooze function is mapped to key 6 and the red toggle switch is mapped to key 0. You may exit the simulation at any time by pressing Q.
