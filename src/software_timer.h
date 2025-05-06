#ifndef SOFTWARE_TIMER_H
#define SOFTWARE_TIMER_H

#include <Arduino.h>

#define MAX 10

void Set_Timer(int timer_id, int duration);
void Timer_Run();
bool isTimerExpired(int timer_id);
void clearTimerFlag(int timer_id);

#endif