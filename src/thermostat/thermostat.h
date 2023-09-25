#ifndef ENERGY_IOT_THERMOSTAT_H
#define ENERGY_IOT_THERMOSTAT_H

#include <Arduino.h>
#include <DHT.h>

#define COOLER_PIN 4
#define HEATER_PIN 3
#define HYSTERESIS 2 //NH_TODO: Maybe get this from MQTT
#define THERMOSTAT_CHECK_INTERVAL (1000 * 1)

void setupThermostat();
void loopThermostat();
void tooCold();
void tooHot();
void idealTemperature();

#endif
