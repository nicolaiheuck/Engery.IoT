#include <Adafruit_GFX.h>
#include <ArduinoJson.h>
#include "shared/RGB/rgb.h"
#include "shared/WiFi/wifi.h"
#include "shared/MQTT/mqtt.h"
#include "telemetry/telemetry.h"
#include "roomPower/roomPower.h"
#include "shared/DS3231/DS3231.h"
#include "shared/RTC/RTC.h"
#include "thermostat/thermostat.h"
#include "power/power.h"

extern MQTTClient mqttClient;
extern DS3231 clock;

void ensureConnectivity();
void onMessageReceivedAlarm(String &topic, String &payload);

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(0));
    setupRGB();
    setupRTC();
    setupTelemetry();
    setupThermostat();
    setupPower();
    ensureConnectivity();
}

void loop() {
    ensureConnectivity();
    mqttClient.loop();
    loopPower();
    loopRoomPower();
    loopThermostat();
    loopTelemetry();
}

void ensureConnectivity() {
    if (WiFi.status() != WL_CONNECTED) {
        ledWhite();
        ensureWiFiSetup();
    }

    while (!mqttClient.connected()) {
        ledBlue();
        setupMQTT("EGON_IoT", onMessageReceivedAlarm);
        mqttClient.subscribe("EUC/51/244/sp/thermostat"); //NH_TODO: Move to #define
    }
}

void onMessageReceivedAlarm(String &topic, String &payload) {
    Serial.print("Topic: ");
    Serial.print(topic);
    Serial.print(" Payload: ");
    Serial.println(payload);

    if (topic.endsWith("/sp/thermostat")) { //NH_TODO: Move to #define
        DynamicJsonDocument newSettings(256);
        deserializeJson(newSettings, payload);
        Serial.println("setThermostatSettings called");
        setThermostatSettings(newSettings["newTemperature"], newSettings["newHysteresis"]);
    }
}
