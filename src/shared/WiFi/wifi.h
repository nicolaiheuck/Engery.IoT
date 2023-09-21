#ifndef SVENDEPROVE_PROJECT_WIFI_H
#define SVENDEPROVE_PROJECT_WIFI_H

#include <WiFiNINA.h>
#include "../secrets.h"
#include "shared/RGB/rgb.h"

bool setupWiFi();
void ensureWiFiSetup();

#endif