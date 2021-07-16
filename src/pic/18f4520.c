#include <pic/18f4520.h>

void
configure_IO()
{
    #ifdef DEBUG_MODE
    printf("[LOG] configuring IO...\n");
    #endif

    /* input */
    TRISDbits.RD0 = 1;             /* adjust time */
    TRISDbits.RD1 = 1;             /* adjust alarm */
    TRISDbits.RD2 = 1;             /* hour */
    TRISDbits.RD3 = 1;             /* minute */
    TRISDbits.RD4 = 1;             /* day */
    TRISDbits.RD5 = 1;             /* toggle alarm */

    /* output */
    PORTAbits.RA4 = 0;             /* clear garbage */
    TRISAbits.RA4 = 0;             /* buzzer */
}

void
configure_TMR0()
{
    #ifdef DEBUG_MODE
    printf("[LOG] configuring TMR0...\n");
    #endif

    INTCONbits.TMR0IE = 0;         /* disable interrupts */
    T0CONbits.T08BIT = 1;          /* 8-bit timer */
    T0CONbits.T0CS = 0;            /* use internal oscillator */
    T0CONbits.PSA = 0;             /* enable prescalar */
    T0CONbits.T0PS = 0b010;        /* set prescalar to 8 */
    T0CONbits.TMR0ON = 1;          /* enable timer */
}

void
configure_TMR2()
{
    #ifdef DEBUG_MODE
    printf("[LOG] configuring TMR2...\n");
    #endif

    PIE1bits.TMR2IE = 1;           /* enable interrupts */
    IPR1bits.TMR2IP = 1;           /* interrupt priority high */
    T2CONbits.T2CKPS = 0b01;       /* set prescalar to 4 */
    PR2 = 249;                     /* set period to 250 (overflow at PR2 + 1) */
    T2CONbits.T2OUTPS = 0b0001;    /* set postscalar to 2 */
    T2CONbits.TMR2ON = 1;          /* enable timer */
    INTCONbits.GIE = 1;            /* enable global interrupt */
    INTCONbits.PEIE = 1;           /* enable peripheral interrupt */
}

void
delay_millisecond(int ms)
{
    int i;

    #ifdef DEBUG_MODE
    usleep(ms * 1000);
    #else
    for (i = 0; i < ms; i++) {
        while (!TMR0IF);
        TMR0IF = 0;
    }
    #endif
}
