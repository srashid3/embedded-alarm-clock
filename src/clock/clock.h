#ifndef CLOCK_H
#define CLOCK_H

#ifdef DEBUG_MODE

#include <debug/mock.h>
#define EVENT_LOOP !exit_simulation

#else

#include <xc.h>
#define EVENT_LOOP 1

#endif

void configure_hardware();

void initialize_time();

void display();

void handle_input();

void check_alarm();

#endif
