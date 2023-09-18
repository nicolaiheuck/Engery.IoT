#ifndef Svendeprove_PROJECT_MQTT_H
#define Svendeprove_PROJECT_MQTT_H

#include <MQTT.h>
#include "shared/RGB/rgb.h"

#define MQTT_USERNAME "program"
#define MQTT_PASSWORD "SuperSecretPassword1337"
#define MQTT_BROKER_ADDRESS "10.131.15.57"

bool setupMQTT(char* clientId, MQTTClientCallbackSimpleFunction messageReceivedCallback);

#endif