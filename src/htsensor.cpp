#include <Arduino.h>
#include "DHT20.h"
DHT20 dht;

void HTSensor_Read() {
  dht.read();
  float temperature = dht.getTemperature();
  float humidity = dht.getHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
}