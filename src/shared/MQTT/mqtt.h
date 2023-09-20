#ifndef ENERGY_IOT_MQTT_H
#define ENERGY_IOT_MQTT_H

#include <MQTT.h>
#include "shared/RGB/rgb.h"

#define MQTT_USERNAME "program"
#define MQTT_PASSWORD "SuperSecretPassword1337"
#define MQTT_BROKER_ADDRESS "10.131.15.57"

bool setupMQTT(String clientBaseId, MQTTClientCallbackSimpleFunction messageReceivedCallback);

#endif