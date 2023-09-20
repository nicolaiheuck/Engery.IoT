#include <Adafruit_GFX.h>
#include "shared/RGB/rgb.h"
#include "shared/WiFi/wifi.h"
#include "shared/MQTT/mqtt.h"
#include "light/light.h"

extern MQTTClient mqttClient;

void ensureConnectivity();
void onMessageReceivedAlarm(String &topic, String &payload);

void setup() {
    randomSeed(analogRead(0));
    Serial.begin(9600);
    setupRGB();
    ensureConnectivity();
    setupLight();
}

void loop() {
    ensureConnectivity();
    mqttClient.loop();
}


void ensureConnectivity() {
    if (WiFi.status() != WL_CONNECTED) {
        ledWhite();
        ensureWiFiSetup();
    }

    while (!mqttClient.connected()) {
        ledBlue();
        setupMQTT("EGON_IoT", onMessageReceivedAlarm);
    }
}

void onMessageReceivedAlarm(String &topic, String &payload) {
    Serial.print("Topic: ");
    Serial.print(topic);
    Serial.print(" Payload: ");
    Serial.println(payload);

    if (topic == MQTT_LIGHT_CONTROL) {
        //NH_TODO: Parse payload
        updateLight(true);
    }
}
