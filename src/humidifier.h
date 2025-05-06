#ifndef HUMIDIFIER_H
#define HUMIDIFIER_H

#include <Arduino.h>
#include "DHT20.h"
#include "software_timer.h"

// Define timer IDs
#define TIMER_GREEN 1
#define TIMER_YELLOW 2
#define TIMER_RED 3

// Define pins for the humidifier LEDs
#define D7 10
#define D8 11

// Function prototypes
void idle();
void led_timer_green();
void led_timer_yellow();
void led_timer_red();
void Humidfier_Run();

#endif // HUMIDIFIER_H