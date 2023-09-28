//
// Created by Jan Andreasen on 27/09/2023.
//

#ifndef ENGERY_IOT_DISPLAY_H
#define ENGERY_IOT_DISPLAY_H

#include "SPI.h"
#include "shared/Display/epd2in9_V2.h"
#include "shared/Display/epdpaint.h"
#include "shared/Display/imagedata.h"
#include <ArduinoJson.h>

#define COLORED 0
#define UNCOLORED 1

void DisplayText(int x, int y, String data[], sFONT* font, bool header = false);
void DisplayDisplay(void);
void DisplayClear(int color);
void setupDisplay(void);
void DisplayDeserializeMQTTPayload(String payload);

#endif //ENGERY_IOT_DISPLAY_H
