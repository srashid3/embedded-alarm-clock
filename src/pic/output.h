#ifndef PIC_OUTPUT_H
#define PIC_OUTPUT_H

#ifdef DEBUG_MODE
#include <debug/mock.h>
#endif

#include <lcd/hd44780.h>

void print_time();

void print_day();

void print_alarm();

void print_message();

#endif
