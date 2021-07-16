#ifndef PIC_18F4520_H
#define PIC_18F4520_H

#ifdef DEBUG_MODE
#include <debug/mock.h>
#else
#include <xc.h>
#endif

/* configure_IO - setup ports for input and output
 *
 * Buttons are mapped to PORTD and the buzzer to PORTA
 */
void configure_IO();

/* configure_TMR0 - setup TMR0 for delays (approximate)
 *
 * The oscillator is set to 8MHz with an instruction cycle of 2MHz (Fcy = Fosc / 4)
 * A prescalar of 8 increases the instruction cycle to 0.5us * 8 = 4us
 * Therefore an 8-bit timer will overflow every 4us * 256 = 1.024ms
 *
 * Note that TMR0 has a delay from when the interrupt fires to when the timer is reloaded
 * Use TMR2 instead for more accuracy (which uses a compare module and auto-reload)
 */
void configure_TMR0();

/* configure_TMR2 - setup TMR2 for clock (accurate)
 *
 * The oscillator is set to 8MHz with an instruction cycle of 2MHz (Fcy = Fosc / 4)
 * A prescalar of 4 increases the instruction cycle to 0.5us * 4 = 2us
 * A period of 250 will cause TMR2 to match PR2 every 2us * 250 = 0.5ms
 * A postscalar of 2 will set the timer flag every 0.5ms * 2 = 1ms
 */
void configure_TMR2();

/* delay_millisecond - adds a delay in milliseconds
 *
 * Must call configure_TMR0() first to ensure correct behavior
 */
void delay_millisecond(int ms);

#endif
