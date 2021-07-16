#include "./input.h"
#include "./output.h"

#include "../clock/time.h"

void
handle_red_button()
{
    if (RED_BUTTON != alarm_enabled) {
        print_time();
        alarm_enabled = RED_BUTTON;
    }
}

void
handle_time_button()
{
    while (TIME_BUTTON) {
        while (TIME_BUTTON && HOUR_BUTTON) {
            delay_millisecond(100);

            cur_hr++;

            if (cur_hr == 12) {
                cur_pr = (cur_pr + 1) % 2;
                cur_hr = 0;
            }

            print_time();
            reset_seconds();
            snooze_flag = 0;
        }

        while (TIME_BUTTON && MINUTE_BUTTON) {
            delay_millisecond(100);

            cur_min = (cur_min + 1) % 60;

            print_time();
            reset_seconds();
            snooze_flag = 0;
        }

        while (TIME_BUTTON && DAY_BUTTON) {
            delay_millisecond(100);

            cur_day = (cur_day + 1) % 7;

            print_day();
            snooze_counter = 0;
        }
    }
}

void
handle_alarm_button()
{
    int i;
    int init = 0;

    while (ALARM_BUTTON) {
        if (!init) {
            print_alarm();
            print_message();

            reprint_time = 1;
            reprint_day = 1;

            init = 1;
        }

        while (ALARM_BUTTON && HOUR_BUTTON) {
            delay_millisecond(100);

            alarm_hr++;
            if (alarm_hr == 12) {
                alarm_pr = (alarm_pr + 1) % 2;
                alarm_hr = 0;
            }

            print_alarm();
            snooze_flag = 0;
        }

        while (ALARM_BUTTON && MINUTE_BUTTON) {
            delay_millisecond(100);

            alarm_min = (alarm_min + 1) % 60;

            print_alarm();
            snooze_flag = 0;
        }
    }
}
