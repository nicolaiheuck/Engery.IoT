#include "RTC.h"
DS3231 clock;

void setupRTC() {
    clock.begin();
    clock.setDateTime(__DATE__, __TIME__);
}