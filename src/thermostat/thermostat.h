#ifndef ENERGY_IOT_THERMOSTAT_H
#define ENERGY_IOT_THERMOSTAT_H

#include <Arduino.h>
#include <DHT.h>

#define COOLER_PIN 4
#define HEATER_PIN 3
#define THERMOSTAT_CHECK_INTERVAL (1000 * 5)

void setupThermostat();
void loopThermostat();
void tooCold();
void tooHot();
void idealTemperature();
void setThermostatSettings(float newTargetTemperature, float newHysteresis);

#endif
