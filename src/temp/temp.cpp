#include "temp.h"

extern MQTTClient mqttClient;
DHT dht(DHT11_PIN, DHT11);

ulong lastTemperatureReadingMillis = 0;
int temperatureInterval = 5000;

void setupTemp() {
    dht.begin();
}

void loopTemp() {
    if (lastTemperatureReadingMillis + temperatureInterval < millis()) {
        lastTemperatureReadingMillis = millis();

        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();

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