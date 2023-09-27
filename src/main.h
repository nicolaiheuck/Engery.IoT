#ifndef ENERGY_IOT_MAIN_H
#define ENERGY_IOT_MAIN_H

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

void ensureConnectivity();
void onMessageReceivedAlarm(String &topic, String &payload);

#endif
