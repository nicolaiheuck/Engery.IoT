#include <Arduino.h>
#include "light.h"
#include "shared/MQTT/mqtt.h"

extern MQTTClient mqttClient;

void setupLight() {
    pinMode(LIGHT_PIN, OUTPUT);
}

void updateLight(bool on) {
    digitalWrite(LIGHT_PIN, on);
}