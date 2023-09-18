#include <Adafruit_GFX.h>
#include "shared/RGB/rgb.h"
#include "shared/WiFi/wifi.h"
#include "shared/MQTT/mqtt.h"

extern MQTTClient mqttClient;

void onMessageReceivedAlarm(String &topic, String &payload);

void setup() {
  Serial.begin(9600);
  setupRGB();
  bool success = setupWiFi();
  if (!success) {
    ledRed();
  }
  else {
    ledGreen();
  }
  bool mqttSuccess = setupMQTT("iot_googlelai_test", onMessageReceivedAlarm);
  if (mqttSuccess) {
    ledBlue();
  }
  else {
    Serial.println("MQTT connection failed!");
    ledRed();
  }
  mqttClient.subscribe("/google_test");
}

void loop() {
    mqttClient.loop();
}

void onMessageReceivedAlarm(String &topic, String &payload) {
  Serial.print("Topic: ");
  Serial.print(topic);
  Serial.print(" Payload: ");
  Serial.println(payload);
}