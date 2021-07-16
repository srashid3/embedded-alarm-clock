#ifndef CLOCK_TIME_H
#define CLOCK_TIME_H

#ifdef DEBUG_MODE
#include <debug/mock.h>
#endif

#define DRIFT_OFFSET  21
#define SNOOZE_OFFSET 10

extern const char hours[];
extern const char minutes[];
extern const char periods[];
extern const char days[7][10];

extern int alarm_hr;
extern int alarm_min;
extern int alarm_pr;

extern volatile int cur_ms;
extern volatile int cur_sec;
extern volatile int cur_min;
extern volatile int cur_hr;
extern volatile int cur_pr;
extern volatile int cur_day;

extern int time_set;
extern int alarm_enabled;

extern int snooze_flag;
extern int snooze_counter;

extern volatile int reprint_time;
extern volatile int reprint_day;

void reset_seconds();

void increment_time();

#endif
