#include <Arduino.h>
#include <DHT20.h>
#include "scheduler.h"
#include "software_timer.h"
#include "led_blinky.h"
#include "htsensor.h"
#include "heater.h"
#include "cooler.h"
#include "humidifier.h"

DHT20 dht20;
#define LED_PIN 48
#define D3 6
#define D4 7
#define D5 8
#define D6 9
#define D7 10
#define D8 11

void TIMER_ISR(void *pvParameters) {
  while(1) {
    SCH_Update();
    vTaskDelay(10);
  }
}

void setup() {
  SCH_Init();
  pinMode(LED_PIN, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  Serial.begin(115200); 
  Wire.begin(GPIO_NUM_11, GPIO_NUM_12);
  dht20.begin();
  xTaskCreate(TIMER_ISR, "TIMER_ISR", 2048, NULL, 2, NULL);
  SCH_Add_Task(Timer_Run, 0, 1);
  SCH_Add_Task(LED_Blinky, 0, 100);
  SCH_Add_Task(HTSensor_Read, 0, 500);
  SCH_Add_Task(Heater_Run, 0, 100);
  SCH_Add_Task(Cooler_Run, 0, 1);
  SCH_Add_Task(Humidfier_Run, 0, 1);
}

void loop() {
  SCH_Dispatch_Tasks();
}
