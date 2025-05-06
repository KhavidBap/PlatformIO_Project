#include <Arduino.h>
#include "DHT20.h"
#include "software_timer.h"

DHT20 cool;

#define D5 8  // Cooler LED1
#define D6 9  // Cooler LED2

int threshold = 35;

enum CoolerState { COOLER_IDLE, COOLER_ACTIVE };
CoolerState coolerStatus = COOLER_IDLE;

void Cooler_Run() {
    static float lastTemperature = 0;

    switch (coolerStatus) {
        case COOLER_IDLE:
            cool.read();
            lastTemperature = cool.getTemperature();
            if (lastTemperature > threshold) { 
                digitalWrite(D5, HIGH);
                digitalWrite(D6, LOW);
                Set_Timer(0, 500); 
                coolerStatus = COOLER_ACTIVE;
            } else {
                digitalWrite(D5, LOW);
                digitalWrite(D6, LOW);
            }
            break;

        case COOLER_ACTIVE:
            cool.read();
            lastTemperature = cool.getTemperature();
            if (isTimerExpired(0)) {
                clearTimerFlag(0);
                if (lastTemperature > threshold) {
                    digitalWrite(D5, HIGH);
                    digitalWrite(D6, LOW);
                    Set_Timer(0, 500);
                    coolerStatus = COOLER_ACTIVE;
                } else {
                    clearTimerFlag(0);
                    digitalWrite(D5, LOW);
                    digitalWrite(D6, LOW);
                    coolerStatus = COOLER_IDLE;
                }
            }
            break;
    }
}