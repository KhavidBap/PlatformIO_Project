#ifndef __SOFTWARE_TIMER_H__
#define __SOFTWARE_TIMER_H__
#define MAX 10 

extern int flag[MAX];
extern int counter[MAX];


void Set_Timer(int index, int value);
void Timer_Run(void);

#endif