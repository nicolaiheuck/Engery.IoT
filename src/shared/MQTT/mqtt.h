#ifndef ENERGY_IOT_MQTT_H
#define ENERGY_IOT_MQTT_H

#include <MQTT.h>
#include "shared/RGB/rgb.h"
#include "shared/secrets.h"
#include "../WiFi/wifi.h"

#define MQTT_USERNAME "program"
#define MQTT_BROKER_ADDRESS "10.131.15.57"

// Topics
#define MQTT_TELEMETRY_TOPIC "EUC/51/244/pv/data"
#define MQTT_GET_THERMOSTAT_SETTINGS "EUC/51/244/sp/thermostat"
#define MQTT_GET_THERMOSTAT_SETTINGS_ENDS_WITH "/sp/thermostat"
#define MQTT_GET_LOCATION_INFO "EUC/51/244/location"
#define MQTT_GET_LOCATION_INFO_ENDS_WITH "/location"
#define MQTT_REQUEST_LOCATION_TOPIC "EUC/51/244/pv/requestlocation/location"

bool setupMQTT(String clientBaseId, MQTTClientCallbackSimpleFunction messageReceivedCallback);

#endif