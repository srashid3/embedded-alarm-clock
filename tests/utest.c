#include "pic/18f4520.h"
#include "lcd/hd44780.h"

int main(int argc, char **argv)
{
    configure_TMR0();

    printf("-----------------------\n");
    printf("TMR0 Configuration\n");
    printf("-----------------------\n");
    printf("TMR0IE > %d\n", INTCONbits.TMR0IE);
    printf("T08BIT > %d\n", T0CONbits.T08BIT);
    printf("T0CS   > %d\n", T0CONbits.T0CS);
    printf("PSA    > %d\n", T0CONbits.PSA);
    printf("T0PS   > %d\n", T0CONbits.T0PS);
    printf("TMR0ON > %d\n", T0CONbits.TMR0ON);
    printf("\n");

    configure_TMR2();

    printf("-----------------------\n");
    printf("TMR2 Configuration\n");
    printf("-----------------------\n");
    printf("TMR2IE  > %d\n", PIE1bits.TMR2IE);
    printf("TMR2IP  > %d\n", IPR1bits.TMR2IP);
    printf("T2CKPS  > %d\n", T2CONbits.T2CKPS);
    printf("PR2     > %d\n", PR2);
    printf("T2OUTPS > %d\n", T2CONbits.T2OUTPS);
    printf("TMR2ON  > %d\n", T2CONbits.TMR2ON);
    printf("GIE     > %d\n", INTCONbits.GIE);
    printf("PEIE    > %d\n", INTCONbits.PEIE);
    printf("\n");

    configure_LCD();

    printf("-----------------------\n");
    printf("LCD Initialization\n");
    printf("-----------------------\n");
    printf("TRISB   > %d\n", TRISB);
    printf("TRISC   > %d\n", TRISC);
    printf("VDD     > %d\n", VDD);
    printf("RW      > %d\n", RW);
    printf("RS      > %d\n", RS);
    printf("EN      > %d\n", EN);
    printf("\n");

    printf("-----------------------\n");
    printf("LCD Clear\n");
    printf("-----------------------\n");

    clear_LCD();

    return 0;
}
