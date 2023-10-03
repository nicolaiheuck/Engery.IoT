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
    requestLocation();
}

void loop() {
    ensureConnectivity();
    mqttClient.loop();
    loopPower();
    loopRoomPower();
    loopThermostat();
    loopTelemetry();
    loopDisplay();
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
        mqttClient.subscribe(MQTT_GET_LOCATION_INFO);
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
        setThermostatSettings(newSettings["newTemperature"], newSettings["newHysteresis"]);
    }

    if (topic.endsWith(MQTT_GET_LOCATION_INFO_ENDS_WITH)) {
        DisplayDeserializeMQTTPayload(payload);
        setRoomSettings(payload);
    }
}
