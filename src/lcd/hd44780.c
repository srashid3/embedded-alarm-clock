#include <lcd/hd44780.h>
#include <pic/18f4520.h>

void
send_nibble(unsigned char nibble)
{
    /* write to lower nibble of port */
    LCD_DATA = (LCD_DATA & 0xF0) + nibble;
    delay_millisecond(1);

    /* store data on falling edge */
    EN = 0;
    delay_millisecond(1);
    EN = 1;

    /* wait as long as slowest possible command (1.52ms) */
    delay_millisecond(2);
}

void
send_command(unsigned char byte)
{
    RS = 0;
    send_nibble(UPPER_NIBBLE(byte));
    send_nibble(LOWER_NIBBLE(byte));

    #ifdef DEBUG_MODE
    printf("[LOG] command issued: %d\n", byte);
    #endif
}

void
send_data(unsigned char byte)
{
    RS = 1;
    send_nibble(UPPER_NIBBLE(byte));
    send_nibble(LOWER_NIBBLE(byte));

    #ifdef DEBUG_MODE
    #ifndef QUIET_MODE
    printf("[LOG] data sent: %d\n", byte);
    #endif
    #endif
}

void
configure_LCD()
{
    #ifdef DEBUG_MODE
    printf("[LOG] initializing LCD...\n");
    #endif

    /* configure pins */
    TRISB = 0;                   /* set data pins to output */
    TRISC = 0;                   /* set control pins to output */

    VDD = 1;                     /* turn display on */
    RW = 0;                      /* enable write mode */
    RS = 0;                      /* send commands */
    EN = 1;                      /* enable data strobe */

    delay_millisecond(1000);

    /* initialize display (refer to figure 24 of HD44780 data sheet) */
    delay_millisecond(16);
    send_nibble(0b00000011);
    delay_millisecond(5);
    send_nibble(0b00000011);
    delay_millisecond(1);
    send_nibble(0b00000011);
    delay_millisecond(5);
    send_nibble(0b00000010);

    /* display settings */
    send_command(0b00101000);    /* function set (N=1 and F=0 ---> 2 lines with 5x7 font) */
    send_command(0b00001000);    /* display control (display off, cursor off, blink off) */
    send_command(0b00000001);    /* clear display */
    send_command(0b00000110);    /* set entry mode (ID=1 and S=0 ---> decrement cursor) */
    send_command(0b00001100);    /* display control (display on, cursor off, blink off) */
}

void
clear_LCD()
{
    #ifdef DEBUG_MODE
    printf("[LOG] clearing LCD...\n");
    #endif

    send_command(0b00000001);
}
