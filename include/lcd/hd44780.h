#ifndef LCD_HD44780_H
#define LCD_HD44780_H

#ifdef DEBUG_MODE
#include <debug/mock.h>
#else
#include <xc.h>
#endif

#define SPACE    ' '
#define COLON    ':'
#define ASTERISK '*'

#define RW  LATCbits.LATC4    /* read or write */
#define EN  LATCbits.LATC5    /* data strobe */
#define RS  LATCbits.LATC6    /* register select */
#define VDD LATCbits.LATC7    /* LCD power */

#define LCD_DATA        LATB
#define LCD_FIRST_LINE  send_command(0x80);
#define LCD_SECOND_LINE send_command(0xC0);

#define UPPER_NIBBLE(byte) byte >> 4
#define LOWER_NIBBLE(byte) byte & 0xF

/* send_nibble - sends a nibble to the LCD
 *
 * Writes to the lower half of LATB on the falling edge
 */
void send_nibble(unsigned char nibble);

/* send_command - sends a command to the LCD
 *
 * Sends a byte to LATB with RS=0
 */
void send_command(unsigned char byte);

/* send_data - sends data to the LCD
 *
 * Sends a byte to LATB with RS=1
 */
void send_data(unsigned char byte);

/* configure_LCD - initalizes LCD display (Hitachi HD44780 LCD controller)
 *
 * The LCD is configured over LATC
 * VDD (positive) and VSS (ground) powers the LCD
 * VEE (negative) adjusts the contrast of the display (use external potentiometer)
 * RW is used to set read or write mode (wire to ground to always write)
 * RS (register select) specifies either data or commands for D0-D7
 * A data strobe is sent using EN (enable) with data stored on the falling edge
 * 4-bit mode uses half the pins with a trade-off of speed (bytes sent in nibbles)
 */
void configure_LCD();

/* clear_LCD - clears LCD display
 *
 * Sends a command with the value 1
 */
void clear_LCD();

#endif
