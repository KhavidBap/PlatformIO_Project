#ifndef HTSENSOR_H
#define HTSENSOR_H

#include <Arduino.h>
#include "DHT20.h"

extern DHT20 dht;

void HTSensor_Read();

#endif