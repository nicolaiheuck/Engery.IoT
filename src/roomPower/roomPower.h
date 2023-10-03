#ifndef ENERGY_IOT_ROOMPOWER_H
#define ENERGY_IOT_ROOMPOWER_H

#include "shared/DS3231/DS3231.h"
#include <ArduinoJson.h>

#define ROOM_POWER_CHECK_INTERVAL (1000 * 60)
#define ROOM_POWER_RELAY_PIN 5

void setupRoomPower();
void loopRoomPower();

void turnOnPower();
void turnOffPower();
void serialPrintFormattedDateTime(RTCDateTime dateTime);
void setRoomSettings(String &payload);
void getHourAndMinuteFromDateTimeString(String &dateTime, int *hour, int *minute);

#endif
