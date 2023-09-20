#include "temp.h"
#include "../shared/MQTT/mqtt.h"

extern MQTTClient mqttClient;
DHT dht(DHT11_PIN, DHT11);

ulong lastTemperatureReadingMillis = 0;
int temperatureInterval = 1000;

void setupTemp() {
    dht.begin();
}

void loopTemp() {
    if (lastTemperatureReadingMillis + temperatureInterval < millis()) {
        lastTemperatureReadingMillis = millis();

        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();

        String payload = String("{\"temperature\":\"") + String(temperature) + "\",\"humidity\":\"" + String(humidity) + String("\"}");
        Serial.print("MQTT Payload: ");
        Serial.println(payload);
        mqttClient.publish(MQTT_TEMPERATURE_TOPIC, payload);
    }
}