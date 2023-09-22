#include <Adafruit_GFX.h>
#include <ArduinoJson.h>
#include "shared/RGB/rgb.h"
#include "shared/WiFi/wifi.h"
#include "shared/MQTT/mqtt.h"
#include "temp/temp.h"
#include "shared/DS3231/DS3231.h"
#include "power/power.h"

extern MQTTClient mqttClient;
extern DS3231 clock;

void ensureConnectivity();
void onMessageReceivedAlarm(String &topic, String &payload);

void setup() {
    Serial.begin(9600);
    setupTemp();
    randomSeed(analogRead(0));
    setupRGB();
    ensureConnectivity();
    setupPower();

    clock.begin();
    clock.setDateTime(__DATE__, "11:21:50");
}

void loop() {
    ensureConnectivity();
    mqttClient.loop();
    loopTemp();
    loopRoomPower();
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
}
