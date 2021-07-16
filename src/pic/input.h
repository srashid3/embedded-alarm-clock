#ifndef PIC_INPUT_H
#define PIC_INPUT_H

#ifdef DEBUG_MODE
#include <debug/mock.h>
#else
#include <xc.h>
#endif

#define ALL_BUTTONS   PORTD
#define TIME_BUTTON   PORTDbits.RD0
#define ALARM_BUTTON  PORTDbits.RD1
#define HOUR_BUTTON   PORTDbits.RD2
#define MINUTE_BUTTON PORTDbits.RD3
#define DAY_BUTTON    PORTDbits.RD4
#define RED_BUTTON    PORTDbits.RD5

#include <pic/18f4520.h>

#define BUZZER     PORTAbits.RA4
#define ANY_BUTTON (ALL_BUTTONS & 0b011111) > 0

void handle_red_button();

void handle_time_button();

void handle_alarm_button();

#endif
