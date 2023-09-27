#ifndef ENERGY_IOT_TELEMETRY_H
#define ENERGY_IOT_TELEMETRY_H

#include <DHT.h>
#include <ArduinoJson.h>
#include "power/power.h"
#include "shared/MQTT/mqtt.h"

#define DHT11_PIN 7
#define TELEMETRY_INTERVAL (1000 * 60)

void setupTelemetry();
void loopTelemetry();

#endif
