#include "telemetry.h"

extern MQTTClient mqttClient;
extern double kiloWattHours;
extern int peakKiloWatt;

DHT dht(DHT11_PIN, DHT11);
ulong lastTemperatureReadingMillis = 0;

void setupTelemetry() {
    dht.begin();
}

void loopTelemetry() {
    if (lastTemperatureReadingMillis + TEMPERATURE_INTERVAL < millis()) {
        lastTemperatureReadingMillis = millis();

        DynamicJsonDocument payloadAsJson(256);
        payloadAsJson["temperature"] = dht.readTemperature();
        payloadAsJson["humidity"] = dht.readHumidity();
        payloadAsJson["kiloWattHour"] = kiloWattHours;
        payloadAsJson["peakKiloWatt"] = peakKiloWatt;
        char payload[256];
        serializeJson(payloadAsJson, payload);

        Serial.print("MQTT Payload: ");
        Serial.println(payload);
        mqttClient.publish(MQTT_TEMPERATURE_TOPIC, payload);
        resetPowerReadings();
    }
}