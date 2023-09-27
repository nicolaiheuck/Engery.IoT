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
#include "shared/Display/Display.h"
#include "main.h"

extern MQTTClient mqttClient;
extern DS3231 clock;

void setup() {
    setupDisplay();
    Serial.begin(9600);
    randomSeed(analogRead(0));
    setupRGB();
    setupRTC();
    setupTelemetry();
    setupThermostat();
    setupRoomPower();
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
        mqttClient.subscribe(MQTT_GET_THERMOSTAT_SETTINGS);
    }
}

void onMessageReceivedAlarm(String &topic, String &payload) {
    Serial.print("Topic: ");
    Serial.print(topic);
    Serial.print(" Payload: ");
    Serial.println(payload);

    if (topic.endsWith(MQTT_GET_THERMOSTAT_SETTINGS_ENDS_WITH)) {
        DynamicJsonDocument newSettings(256);
        deserializeJson(newSettings, payload);
        Serial.println("setThermostatSettings called");
        setThermostatSettings(newSettings["newTemperature"], newSettings["newHysteresis"]);
    }

    if (topic.endsWith("/location"))
}
