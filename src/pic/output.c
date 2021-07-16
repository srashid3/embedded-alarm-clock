#include "./input.h"
#include "./output.h"

#include "../clock/time.h"

void print_alarm()
{
    LCD_FIRST_LINE;

    send_data(hours[(alarm_hr * 2)]);
    send_data(hours[(alarm_hr * 2) + 1]);

    send_data(COLON);

    send_data(minutes[(alarm_min * 2)]);
    send_data(minutes[(alarm_min * 2) + 1]);

    send_data(SPACE);

    send_data(periods[(alarm_pr * 2)]);
    send_data(periods[(alarm_pr * 2) + 1]);

    #ifdef DEBUG_MODE
    printf("[LOG] %c%c%c%c%c%c%c%c\n",
           hours[alarm_hr * 2], hours[alarm_hr * 2 + 1], COLON,
           minutes[alarm_min * 2], minutes[alarm_min * 2 + 1], SPACE,
           periods[alarm_pr * 2], periods[alarm_pr * 2 + 1]
    );
    #endif
}

void print_time()
{
    LCD_FIRST_LINE;

    send_data(hours[(cur_hr * 2)]);
    send_data(hours[(cur_hr * 2) + 1]);

    send_data(COLON);

    send_data(minutes[(cur_min * 2)]);
    send_data(minutes[(cur_min * 2) + 1]);

    send_data(SPACE);

    send_data(periods[(cur_pr * 2)]);
    send_data(periods[(cur_pr * 2) + 1]);

    RED_BUTTON ? send_data(ASTERISK) :  send_data(SPACE);

    #ifdef DEBUG_MODE
    printf("[LOG] %c%c%c%c%c%c%c%c%c\n",
           hours[cur_hr * 2], hours[cur_hr * 2 + 1], COLON,
           minutes[cur_min * 2], minutes[cur_min * 2 + 1], SPACE,
           periods[cur_pr * 2], periods[cur_pr * 2 + 1],
           RED_BUTTON ? ASTERISK : SPACE
    );
    #endif
}

void print_day()
{
    int i;

    LCD_SECOND_LINE;

    for (i = 0; i < sizeof(days[cur_day]); i++)
        send_data(days[cur_day][i]);

    #ifdef DEBUG_MODE
    printf("[LOG] %*.*s\n", 10, 10, days[cur_day]);
    #endif
}

void print_message()
{
    int i;
    const char message[] = "SET ALARM ";

    LCD_SECOND_LINE;

    for (i = 0; i < sizeof(alarm) - 1; i++)
        send_data(message[i]);

    #ifdef DEBUG_MODE
    printf("[LOG] %s\n", message);
    #endif
}
