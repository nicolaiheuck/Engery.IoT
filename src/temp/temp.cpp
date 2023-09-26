#include "temp.h"

extern MQTTClient mqttClient;
DHT dht(DHT11_PIN, DHT11);

ulong lastTemperatureReadingMillis = 0;
int temperatureInterval = 5000;

void setupTemp() {
    dht.begin();
}

float bullshitData() {
    long milliSeconds = millis();
    float result = 0;

    result = milliSeconds * 13.37;

    while (result > 50)
    {
        result = result / (13.37 * 0.5);
    }

    return result;
}

void loopTemp() {
    if (lastTemperatureReadingMillis + temperatureInterval < millis()) {
        lastTemperatureReadingMillis = millis();

//        float temperature = dht.readTemperature();
//        float humidity = dht.readHumidity();
        float temperature = bullshitData();
        float humidity = bullshitData();

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