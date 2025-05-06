#include <Arduino.h>
#include "DHT20.h"
#include "software_timer.h"

#define TIMER_IDLE 0
#define TIMER_GREEN 1
#define TIMER_YELLOW 2
#define TIMER_RED 3
#define D7 10
#define D8 17

DHT20 humid;

int state = TIMER_IDLE;

void Humidfier_Run() {
    static float humidity;
    int standard = 70;
    switch (state) {
        case TIMER_IDLE:
            humid.read();
            humidity = humid.getHumidity();
            if (humidity <= standard) {
                digitalWrite(D7, HIGH);
                digitalWrite(D8, LOW);
                Set_Timer(1, 500);
                state = TIMER_GREEN;
            } else {
                clearTimerFlag(1);
                digitalWrite(D7, LOW);
                digitalWrite(D8, LOW);
                state = TIMER_IDLE;
            }
            break;

        case TIMER_GREEN:
            digitalWrite(D7, HIGH);
            digitalWrite(D8, LOW);
            if (isTimerExpired(1)) {
                clearTimerFlag(1);
                Set_Timer(1, 200);
                state = TIMER_YELLOW;
            }
            break;

        case TIMER_YELLOW:
            digitalWrite(D7, LOW);
            digitalWrite(D8, HIGH);
            if (isTimerExpired(1)) {
                clearTimerFlag(1);
                Set_Timer(1, 300);
                state = TIMER_RED;
            }
            break;

        case TIMER_RED:
            digitalWrite(D7, HIGH);
            digitalWrite(D8, HIGH);
            if (isTimerExpired(1)) {
                clearTimerFlag(1);
                humid.read();
                humidity = humid.getHumidity();
                if (humidity <= standard) {
                    digitalWrite(D7, HIGH);
                    digitalWrite(D8, LOW);
                    Set_Timer(1, 500);
                    state = TIMER_GREEN;
                } else {
                    clearTimerFlag(1);
                    digitalWrite(D7, LOW);
                    digitalWrite(D8, LOW);
                    state = TIMER_IDLE;
                }
            }
            break;
        }
}