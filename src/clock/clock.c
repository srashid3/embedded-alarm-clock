#include "./clock.h"
#include "./time.h"

#include "../pic/input.h"
#include "../pic/output.h"

#pragma config OSC = HS     /* use external crystal (RA6 and RA7) */
#pragma config WDT = OFF    /* disable watchdog timer */

#ifndef DEBUG_MODE
void interrupt ISR() {
    if (TMR2IE && TMR2IF) {
        TMR2IF = 0;
        increment_time();
    }
}
#endif

void
configure_hardware()
{
    configure_IO();
    configure_TMR0();
    configure_TMR2();
    configure_LCD();

    alarm_enabled = RED_BUTTON;
}

void
initialize_time()
{
    int i;

    while (!time_set) {
        #ifdef DEBUG_MODE
        printf("[LOG] clock is uninitialized\n");
        #endif

        print_time();
        print_day();

        for (i = 0; i < 500; i++) {
            delay_millisecond(1);
            if (ANY_BUTTON) {
                time_set = 1;
                return;
            }
        }

        clear_LCD();

        for (i = 0; i < 500; i++) {
            delay_millisecond(1);
            if (ANY_BUTTON) {
                time_set = 1;
                print_time();
                print_day();
                return;
            }
        }
    }
}


void
handle_input()
{
    handle_red_button();
    handle_time_button();
    handle_alarm_button();
}

void
check_alarm()
{
    int i;

    if (snooze_flag) {
        if (cur_min == snooze_counter)
            goto activate;
        return;
    }

    if (cur_hr != alarm_hr || cur_min != alarm_min || cur_pr != alarm_pr)
        return;

activate:
    while (RED_BUTTON) {
        #ifdef DEBUG_MODE
        printf("[LOG] ALARM!\n");
        #endif

        BUZZER = 0;

        for (i = 0; i < 500; i++) {
            delay_millisecond(1);
            display();
            if (MINUTE_BUTTON && DAY_BUTTON) {
                snooze_counter = (cur_min + SNOOZE_OFFSET) % 60;
                snooze_flag = 1;
                return;
            }
        }

        BUZZER = 1;

        for (i = 0; i < 500; i++) {
            delay_millisecond(1);
            display();
            if (MINUTE_BUTTON && DAY_BUTTON) {
                snooze_counter = (cur_min + SNOOZE_OFFSET) % 60;
                snooze_flag = 1;
                BUZZER = 0;
                return;
            }
        }
    }
}

void
display()
{
    if (reprint_time) {
        print_time();
        reprint_time = 0;
    }

    if (reprint_day) {
        print_day();
        reprint_day = 0;
    }
}

int
main (int argc, char **argv)
{
    #ifdef DEBUG_MODE
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, mock_isr, NULL);
    pthread_create(&tid2, NULL, mock_input, NULL);
    #endif

    configure_hardware();

    initialize_time();

    while (EVENT_LOOP) {
        handle_input();
        check_alarm();
        display();
    }

    #ifdef DEBUG_MODE
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    #endif

    return 0;
}
