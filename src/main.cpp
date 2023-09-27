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

extern MQTTClient mqttClient;
extern DS3231 clock;

void ensureConnectivity();
void onMessageReceivedAlarm(String &topic, String &payload);

void setup() {
//    randomSeed(analogRead(0));
//    setupTemp();
//    setupRGB();
//    setupRTC();
//    ensureConnectivity();
//    setupThermostat();
//    setupPower();
    setupDisplay();
}

void loop() {
//    ensureConnectivity();
//    mqttClient.loop();
//    loopTemp();
//    loopRoomPower();
//    loopThermostat();
    DisplayText(10, 20, "test1");
    delay(1234);
    DisplayText(20, 30, "test2");
    delay(1234);
    DisplayText(30, 40, "test3");
    delay(1234);
    DisplayText(40, 50, "test4");
    delay(1234);
    DisplayText(50, 60, "test5");
    delay(1234);
}

void ensureConnectivity() {
    if (WiFi.status() != WL_CONNECTED) {
        ledWhite();
        ensureWiFiSetup();
    }

    while (!mqttClient.connected()) {
        ledBlue();
        setupMQTT("EGON_IoT", onMessageReceivedAlarm);
        mqttClient.subscribe("EUC/51/244/sp/thermostat");
    }
}

void onMessageReceivedAlarm(String &topic, String &payload) {
    Serial.print("Topic: ");
    Serial.print(topic);
    Serial.print(" Payload: ");
    Serial.println(payload);

    if (topic.endsWith("/sp/thermostat")) {
        DynamicJsonDocument newSettings(256);
        deserializeJson(newSettings, payload);
        Serial.println("setThermostatSettings called");
        setThermostatSettings(newSettings["newTemperature"], newSettings["newHysteresis"]);
    }

    if (topic.endsWith("/location"))
}
