#ifndef ENERGY_IOT_WIFI_H
#define ENERGY_IOT_WIFI_H

#include <WiFiNINA.h>
#include "../secrets.h"
#include "shared/RGB/rgb.h"

bool setupWiFi();
void ensureWiFiSetup();

#endif