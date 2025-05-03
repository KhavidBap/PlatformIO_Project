#include <Arduino.h>
#define LED_PIN 48

int led_status = 0;
void LED_Blinky(){
  led_status = 1 - led_status;
  digitalWrite(LED_PIN, led_status);
}