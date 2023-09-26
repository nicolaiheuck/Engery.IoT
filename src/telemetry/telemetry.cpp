#include "telemetry.h"
#include "power/power.h"

extern MQTTClient mqttClient;
DHT dht(DHT11_PIN, DHT11);

ulong lastTemperatureReadingMillis = 0;

void setupTelemetry() {
    dht.begin();
    setupPower();
    //NH_TODO: Begin power
}

void loopTelemetry() {
    if (lastTemperatureReadingMillis + TEMPERATURE_INTERVAL < millis()) {
        lastTemperatureReadingMillis = millis();

        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();
        double powerUsageInAmps = getUsageInAmps();
        double watt = powerUsageInAmps * 230;

        DynamicJsonDocument payloadAsJson(128);
        payloadAsJson["temperature"] = temperature;
        payloadAsJson["humidity"] = humidity;
        char payload[128];
        serializeJson(payloadAsJson, payload);

        Serial.print("MQTT Payload: ");
        Serial.println(payload);
        mqttClient.publish(MQTT_TEMPERATURE_TOPIC, payload);
    }
}