//
// Created by Jan Andreasen on 27/09/2023.
//

#include "Display.h"

unsigned char image[10240];
Paint paint(image, 0, 0);
Epd epd;

void setupDisplay() {
    epd.Init();
    epd.ClearFrameMemory(0xFF);
    epd.DisplayFrame();
}

void DisplayText(int x, int y, const char* t) {
    paint.SetRotate(ROTATE_270);
    paint.SetWidth(128);
    paint.SetHeight(296);
    paint.Clear(UNCOLORED);
    paint.DrawStringAt(0, 0, "IT WORKS!", &Font20, COLORED);
    paint.DrawStringAt(0, 100, "51.244 - Sibirien", &Font20, COLORED);
    paint.DrawStringAt(x, y, t, &Font20, COLORED);
    epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();
}