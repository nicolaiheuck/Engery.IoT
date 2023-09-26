#include "thermostat.h"

float hysteresis = -1;
float targetTemperature = -1;
ulong lastCheckedTemperature = 0;
extern DHT dht;

void setupThermostat() {
    pinMode(COOLER_PIN, OUTPUT);
    pinMode(HEATER_PIN, OUTPUT);
}

void loopThermostat() {
    if (hysteresis == -1 || targetTemperature == -1) return;
    if (lastCheckedTemperature + THERMOSTAT_CHECK_INTERVAL < millis()) {
        lastCheckedTemperature = millis();

        float temperature = dht.readTemperature();
        if (temperature > targetTemperature + hysteresis) {
            tooHot();
        } else if (temperature < targetTemperature - hysteresis) {
            tooCold();
        } else {
            idealTemperature();
        }
    }
}

void setThermostatSettings(float newTargetTemperature, float newHysteresis) {
    targetTemperature = newTargetTemperature;
    hysteresis = newHysteresis;
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