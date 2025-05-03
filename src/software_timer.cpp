#include "software_timer.h"
#define MAX 10 
int counter[MAX];
int flag[MAX];

void Set_Timer(int timer_id, int duration) {
    counter[timer_id] = duration;
    flag[timer_id] = 0;
  }
  
  void Timer_Run() {
    for (int i = 0; i < MAX; i++) {
        if (counter[i] > 0) {
            counter[i]--;
            if (counter[i] == 0) {
                flag[i] = 1;
            }
        }
    }
  }
  