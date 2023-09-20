#include <Adafruit_GFX.h>
#include "shared/RGB/rgb.h"
#include "shared/WiFi/wifi.h"
#include "shared/MQTT/mqtt.h"
#include "temp/temp.h"
#include "light/light.h"

extern MQTTClient mqttClient;

void ensureConnectivity();
void onMessageReceivedAlarm(String &topic, String &payload);

void setup() {
    Serial.begin(9600);
    setupTemp();
    randomSeed(analogRead(0));
    setupRGB();
    ensureConnectivity();
    setupLight();
}

void loop() {
    ensureConnectivity();
    mqttClient.loop();
    loopTemp();
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
