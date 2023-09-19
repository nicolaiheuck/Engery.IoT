#include "mqtt.h"
#include "../WiFi/wifi.h"

extern WiFiClient wifiClient;
MQTTClient mqttClient;
u_int8_t retries = 5;

bool setupMQTT(String clientBaseId, MQTTClientCallbackSimpleFunction messageReceivedCallback) {
    ledBlue();
    Serial.print("\nMQTT: Connecting...");

    String nonce = String(random(1, 1024));
    clientBaseId += "_" + nonce;
    char clientId[clientBaseId.length() + 1];
    clientBaseId.toCharArray(clientId, sizeof(clientId));

    mqttClient.begin(MQTT_BROKER_ADDRESS, wifiClient);
    mqttClient.onMessage(messageReceivedCallback);

    while (!mqttClient.connect(clientId, MQTT_USERNAME, MQTT_PASSWORD)) {
        Serial.println("Trying to connect to broker");
        delay(2500);
        retries--;
        if (retries == 0) {
            ledRed();
            return false;
        }
    }

    Serial.print("\nMQTT: Connected! (id: ");
    Serial.println(clientId + String(")"));
    ledGreen();
    return true;
}