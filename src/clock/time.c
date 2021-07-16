#include "./time.h"

const char hours[] = "120102030405060708091011";

const char minutes[] = "00010203040506070809"
                       "10111213141516171819"
                       "20212223242526272829"
                       "30313233343536373839"
                       "40414243444546474849"
                       "50515253545556575859";

const char periods[] = "AMPM";

const char days[7][10] = {
    "Sunday    ",
    "Monday    ",
    "Tuesday   ",
    "Wednesday ",
    "Thursday  ",
    "Friday    ",
    "Saturday  "
};


int alarm_hr = 0;
int alarm_min = 30;
int alarm_pr = 0;

volatile int cur_day = 0;
volatile int cur_hr = 0;
volatile int cur_min = 0;
volatile int cur_pr = 0;
volatile int cur_sec = 0;
volatile int cur_ms = 0;

int time_set = 0;
int alarm_enabled = 0;

int snooze_flag = 0;
int snooze_counter = 0;

volatile int reprint_time = 0;
volatile int reprint_day = 0;

static int drift = 0;

static int
drift_correction()
{
    drift++;

    if (drift == DRIFT_OFFSET) {
        #ifdef DEBUG_MODE
        printf("[LOG] drift correction\n");
        #endif

        cur_ms = 999;
        drift = 0;
        return 1;
    }

    return 0;
}

void
reset_seconds()
{
    cur_ms = 0;
    cur_sec = 0;
}

void
increment_time()
{
    cur_ms++;

    if (cur_ms == 1000 && !drift_correction()) {
        cur_sec++;
        cur_ms = 0;
    } else return;

    if (cur_sec == 60) {
        cur_min++;
        cur_sec = 0;
        reprint_time = 1;
    } else return;

    if (cur_min == 60) {
        cur_hr++;
        cur_min = 0;
    } else return;

    if (cur_hr == 12) {
        cur_pr++;
        cur_hr = 0;
    } else return;

    if (cur_pr == 2) {
        cur_day++;
        cur_pr = 0;
        reprint_day = 1;
    } else return;

    if (cur_day == 7) {
        cur_day = 0;
    } else return;
}
