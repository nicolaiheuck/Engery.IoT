#include <Adafruit_GFX.h>
//#include <ArduinoJson.h>
//#include "shared/RGB/rgb.h"
//#include "shared/WiFi/wifi.h"
//#include "shared/MQTT/mqtt.h"
//#include "temp/temp.h"
//#include "shared/DS3231/DS3231.h"
//#include "power/roomPower.h"
//#include "shared/RTC/RTC.h"
//#include "thermostat/thermostat.h"
#include "power/power.h"

//extern MQTTClient mqttClient;
//extern DS3231 clock;
//
//void ensureConnectivity();
//void onMessageReceivedAlarm(String &topic, String &payload);
//
void setup() {
    pinMode(A6, INPUT);
    Serial.begin(9600);
    setupPower();
//    randomSeed(analogRead(0));
//    setupTemp();
//    setupRGB();
//    setupRTC();
//    ensureConnectivity();
//    setupThermostat();
//    setupPower();
}
//
void loop() {
    int A0Value = analogRead(A6);
    double resultFromEmon = getUsageInAmps();
//    ensureConnectivity();
//    mqttClient.loop();
//    loopTemp();
//    loopRoomPower();
//    loopThermostat();
    Serial.println("A6: " + String(A0Value) + " Test: " + String(A0Value - 780) + " Emon result: " + String(resultFromEmon));
    delay(200);
}
//
//void ensureConnectivity() {
//    if (WiFi.status() != WL_CONNECTED) {
//        ledWhite();
//        ensureWiFiSetup();
//    }
//
//    while (!mqttClient.connected()) {
//        ledBlue();
//        setupMQTT("EGON_IoT", onMessageReceivedAlarm);
//        mqttClient.subscribe("EUC/51/244/sp/thermostat");
//    }
//}
//
//void onMessageReceivedAlarm(String &topic, String &payload) {
//    Serial.print("Topic: ");
//    Serial.print(topic);
//    Serial.print(" Payload: ");
//    Serial.println(payload);
//
//    if (topic.endsWith("/sp/thermostat")) {
//        DynamicJsonDocument newSettings(256);
//        deserializeJson(newSettings, payload);
//        Serial.println("setThermostatSettings called");
//        setThermostatSettings(newSettings["newTemperature"], newSettings["newHysteresis"]);
//    }
//}
