#include "temp.h"

extern MQTTClient mqttClient;
DHT dht(DHT11_PIN, DHT11);

ulong lastTemperatureReadingMillis = 0;

void setupTemp() {
    dht.begin();
}

void loopTemp() {
    if (lastTemperatureReadingMillis + TEMPERATURE_INTERVAL < millis()) {
        lastTemperatureReadingMillis = millis();

        float temperature = 13.37;
        float humidity = 13.37;

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