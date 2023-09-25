#include "thermostat.h"

float targetTemperature = 22; // NH_TODO: Get this value from MQTT
extern DHT dht;

void setupThermostat() {
    pinMode(COOLER_PIN, OUTPUT);
    pinMode(HEATER_PIN, OUTPUT);
}

void loopThermostat() {
    //NH_TODO: Add THERMOSTAT_CHECK_INTERVAL
    float temperature = dht.readTemperature();
    if (temperature > targetTemperature + HYSTERESIS) {
        tooHot();
    } else if (temperature < targetTemperature - HYSTERESIS) {
        tooCold();
    } else {
        idealTemperature();
    }
}

void idealTemperature() {
    digitalWrite(HEATER_PIN, LOW);
    digitalWrite(COOLER_PIN, LOW);
}

void tooCold() {
    digitalWrite(HEATER_PIN, HIGH);
    digitalWrite(COOLER_PIN, LOW);
}

void tooHot() {
    digitalWrite(COOLER_PIN, HIGH);
    digitalWrite(HEATER_PIN, LOW);
}