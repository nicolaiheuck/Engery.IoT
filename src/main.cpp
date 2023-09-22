#include <Adafruit_GFX.h>
#include <ArduinoJson.h>
#include "shared/RGB/rgb.h"
#include "shared/WiFi/wifi.h"
#include "shared/MQTT/mqtt.h"
#include "temp/temp.h"
#include "shared/DS3231/DS3231.h"
#include "power/power.h"
#include "shared/RTC/RTC.h"
#include "thermostat/thermostat.h"

extern MQTTClient mqttClient;
extern DS3231 clock;

void ensureConnectivity();
void onMessageReceivedAlarm(String &topic, String &payload);

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(0));
    setupTemp();
    setupRGB();
    setupPower();
    setupRTC();
    setupThermostat();
    ensureConnectivity();
}

void loop() {
    ensureConnectivity();
    mqttClient.loop();
    loopTemp();
    loopRoomPower();
    loopThermostat();
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
