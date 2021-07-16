#include <debug/mock.h>

#include "../pic/input.h"
#include "../clock/time.h"

int exit_simulation = 0;

void *
mock_isr(void *unused)
{
    while (!exit_simulation) {
        increment_time();
        delay_millisecond(1);
    }

    return NULL;
}

void *
mock_input(void *unused)
{
    char c;

    while (!exit_simulation) {
        c = getchar();

        switch(c) {
        case '1':
            ALARM_BUTTON = !ALARM_BUTTON;
            TIME_BUTTON = 0;
            ALL_BUTTONS = 1;
            printf("[LOG] alarm button pressed\n");
            printf("[LOG] alarm mode %s\n", ALARM_BUTTON ? "ON" : "OFF");
            break;
        case '2':
            TIME_BUTTON = !TIME_BUTTON;
            ALARM_BUTTON = 0;
            ALL_BUTTONS = 1;
            printf("[LOG] time button pressed\n");
            printf("[LOG] time mode %s\n", TIME_BUTTON ? "ON" : "OFF");
            break;
        case '3':
            HOUR_BUTTON = 1;
            delay_millisecond(1);
            HOUR_BUTTON = 0;
            ALL_BUTTONS = 1;
            printf("[LOG] hour button pressed\n");
            break;
        case '4':
            MINUTE_BUTTON = 1;
            delay_millisecond(1);
            MINUTE_BUTTON = 0;
            ALL_BUTTONS = 1;
            printf("[LOG] minute button pressed\n");
            break;
        case '5':
            DAY_BUTTON = 1;
            delay_millisecond(1);
            DAY_BUTTON = 0;
            ALL_BUTTONS = 1;
            printf("[LOG] day button pressed\n");
            break;
        case '6':
            MINUTE_BUTTON = 1;
            DAY_BUTTON = 1;
            delay_millisecond(1);
            MINUTE_BUTTON = 0;
            DAY_BUTTON = 0;
            ALL_BUTTONS = 1;
            printf("[LOG] snooze triggered\n");
            break;
        case '0':
            RED_BUTTON = !RED_BUTTON;
            ALL_BUTTONS = 1;
            printf("[LOG] red button pressed\n");
            break;
        case 'q':
            TIME_BUTTON = 0;
            ALARM_BUTTON = 0;
            RED_BUTTON = 0;
            ALL_BUTTONS = 1;
            exit_simulation = 1;
            printf("[LOG] exit simulation\n");
            break;
        default:
            break;
        }
  }

  return NULL;
}
