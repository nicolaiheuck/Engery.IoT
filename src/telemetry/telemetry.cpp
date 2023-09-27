#include "telemetry.h"

extern MQTTClient mqttClient;
extern double kiloWattHours;
extern int peakKiloWatt;

DHT dht(DHT11_PIN, DHT11);
ulong lastTelemetryReadingMillis = 0;

void setupTelemetry() {
    dht.begin();
}

void loopTelemetry() {
    if (lastTelemetryReadingMillis + TELEMETRY_INTERVAL < millis()) {
        lastTelemetryReadingMillis = millis();

        DynamicJsonDocument payloadAsJson(256);
        payloadAsJson["temperature"] = dht.readTemperature();
        payloadAsJson["humidity"] = dht.readHumidity();
        payloadAsJson["kiloWattHour"] = kiloWattHours;
        payloadAsJson["peakKiloWatt"] = peakKiloWatt;
        char payload[256];
        serializeJson(payloadAsJson, payload);

        Serial.print("MQTT Payload: ");
        Serial.println(payload);
        mqttClient.publish(MQTT_TELEMETRY_TOPIC, payload);

        resetPowerReadings();
    }
}