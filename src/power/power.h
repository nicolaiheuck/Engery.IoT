#ifndef ENERGY_IOT_POWER_H
#define ENERGY_IOT_POWER_H

#include "EmonLib.h"

#define POWER_READING_PIN A6
#define POWER_READING_INTERVAL (1000 * 60)

void setupPower();
void loopPower();
void resetPowerReadings();

#endif
