#ifndef DEBUG_MOCK_H
#define DEBUG_MOCK_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define MOCK_HW(TGT, PIN, X)    \
unsigned char TGT##X;           \
struct TGT##X {                 \
    unsigned PIN##X##0:1;       \
    unsigned PIN##X##1:1;       \
    unsigned PIN##X##2:1;       \
    unsigned PIN##X##3:1;       \
    unsigned PIN##X##4:1;       \
    unsigned PIN##X##5:1;       \
    unsigned PIN##X##6:1;       \
    unsigned PIN##X##7:1;       \
} TGT##X##bits

#define MOCK_LAT(X)  MOCK_HW(LAT, LAT, X)
#define MOCK_PORT(X) MOCK_HW(PORT, R, X)
#define MOCK_TRIS(X) MOCK_HW(TRIS, R, X)

extern int exit_simulation;

unsigned char PR2;
unsigned char TMR0IF;

struct T0CON {
    unsigned PSA:1;
    unsigned T0CS:1;
    unsigned T08BIT:1;
    unsigned TMR0ON:1;
    unsigned char T0PS;
} T0CONbits;

struct T2CON {
    unsigned TMR2ON:1;
    unsigned char T2CKPS;
    unsigned char T2OUTPS;
} T2CONbits;

struct INTCON {
    unsigned GIE:1;
    unsigned PEIE:1;
    unsigned TMR0IE:1;
} INTCONbits;

struct IPR1 {
    unsigned TMR2IP:1;
} IPR1bits;

struct PIE1 {
    unsigned TMR2IE:1;
} PIE1bits;

MOCK_LAT(A);
MOCK_LAT(B);
MOCK_LAT(C);
MOCK_LAT(D);

MOCK_PORT(A);
MOCK_PORT(B);
MOCK_PORT(C);
MOCK_PORT(D);

MOCK_TRIS(A);
MOCK_TRIS(B);
MOCK_TRIS(C);
MOCK_TRIS(D);

void *mock_isr(void *unused);
void *mock_input(void *unused);

#endif
