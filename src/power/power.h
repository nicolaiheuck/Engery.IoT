#ifndef ENERGY_IOT_POWER_H
#define ENERGY_IOT_POWER_H

#include "shared/DS3231/DS3231.h"

#define ROOM_CHECK_INTERVAL (1000 * 1)
#define POWER_RELAY_PIN 4

void setupPower();
void loopRoomPower();

void turnOnPower();
void turnOffPower();
void serialPrintFormattedDateTime(RTCDateTime dateTime);

#endif
