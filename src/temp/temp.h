#ifndef ENERGY_IOT_TEMP_H
#define ENERGY_IOT_TEMP_H

#include <DHT.h>
#include <ArduinoJson.h>
#include "../shared/MQTT/mqtt.h"

#define DHT11_PIN 7

void setupTemp();
void loopTemp();

#endif
