#include <Arduino.h>
#include "DHT20.h"

#define D3 6
#define D4 7

DHT20 temp;

void Heater_Run() {
    temp.read();
    float temperature = temp.getTemperature();
    if (temperature <= 35) {
        digitalWrite(D3, HIGH); 
        digitalWrite(D4, LOW);
    } else if (temperature <= 50) {
        digitalWrite(D3, LOW);
        digitalWrite(D4, HIGH);
    } else {
        digitalWrite(D3, HIGH);
        digitalWrite(D4, HIGH);
    }
}