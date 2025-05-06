#include <Arduino.h>
#include "DHT20.h"
#include "software_timer.h"

#define TIMER_GREEN 1
#define TIMER_YELLOW 2
#define TIMER_RED 3
#define D7 10
#define D8 11

DHT20 humid;
int state = 0;

void idle() {
    digitalWrite(D7, LOW);
    digitalWrite(D8, LOW);
    Set_Timer(0, 100);
}

void led_timer_green() {
    digitalWrite(D7, LOW);
    digitalWrite(D8, HIGH);
    Set_Timer(TIMER_GREEN, 500);
    if(isTimerExpired(TIMER_GREEN)) {
        state = TIMER_YELLOW;
    }
}

void led_timer_yellow() {
    digitalWrite(D7, HIGH);
    digitalWrite(D8, LOW);
    Set_Timer(TIMER_YELLOW, 300);
    if (isTimerExpired(TIMER_YELLOW)) {
        state = TIMER_RED;
    }
}

void led_timer_red() {
    digitalWrite(D7, HIGH);
    digitalWrite(D8, HIGH);
    Set_Timer(TIMER_YELLOW, 200);
    if (isTimerExpired(TIMER_YELLOW)){
        state = TIMER_GREEN;
    }
}

void Humidfier_Run() {
    humid.read();
    float humidity = humid.getHumidity();
    if (humidity <= 40) {
        switch(state){
            case TIMER_GREEN:
                led_timer_green(); 
                break;
            case TIMER_YELLOW:
                led_timer_yellow();
                break;
            case TIMER_RED:
                led_timer_red();
                break;
        }
    } else {
        idle();  
    }
}