#include <Arduino.h>
#include "software_timer.h"
#include "state_machine.h"

#define RED_GREEN 1
#define RED_AMBER 2
#define GREEN_RED 3
#define AMBER_RED 4
#define LED_PIN 48
#define D3 6
#define D4 7
#define D5 8
#define D6 9

int state = RED_GREEN;             

void led_red_green() {
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
    digitalWrite(D5, HIGH);
    digitalWrite(D6, LOW);

    if (flag[1] == 1) {
        Set_Timer(1, 1);
    }
    if (flag[0] == 1) {
        state = RED_AMBER;
        Set_Timer(0, 2);
    }
}

void led_red_amber() {
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
    digitalWrite(D5, LOW);
    digitalWrite(D6, HIGH);

    if (flag[1] == 1) {
        Set_Timer(1, 1);
    }
    if (flag[0] == 1) {
        state = GREEN_RED;
        Set_Timer(0, 3);
    }
}

void led_green_red() {
    digitalWrite(D3, HIGH);
    digitalWrite(D4, LOW);
    digitalWrite(D5, HIGH);
    digitalWrite(D6, HIGH);

    if (flag[1] == 1) {
        Set_Timer(1, 1);
    }
    if (flag[0] == 1) {
        state = AMBER_RED;
        Set_Timer(0, 2);
    }
}

void led_amber_red() {
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH);
    digitalWrite(D5, HIGH);
    digitalWrite(D6, HIGH);

    if (flag[1] == 1) {
        Set_Timer(1, 1);
    }
    if (flag[0] == 1) {
        state = RED_GREEN;
        Set_Timer(0, 3);
    }
}

void task() {
    switch (state) {
        case RED_GREEN:
            led_red_green();
            break;
        case RED_AMBER:
            led_red_amber();
            break;
        case GREEN_RED:
            led_green_red();
            break;
        case AMBER_RED:
            led_amber_red();
            break;
    }
}
