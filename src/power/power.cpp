#include "power.h"

extern DS3231 clock;

int roomOnHour = 0;
int roomOnMinute = 0;
int roomOffHour = 0;
int roomOffMinute = 0;
bool roomCurrentState = false;
ulong roomLastCheckedMillis = 0;

void loopRoomPower() {
    RTCDateTime dateTime = clock.getDateTime();
    if (roomLastCheckedMillis + ROOM_CHECK_INTERVAL < millis()) {
        roomLastCheckedMillis = millis();
//        Serial.print("Checking room power (");
//        serialPrintFormattedDateTime(dateTime);
//        Serial.println(")");

        bool pastPowerOnTime = dateTime.hour > roomOnHour || (dateTime.hour == roomOnHour && dateTime.minute >= roomOnMinute);
        bool pastPowerOffTime = dateTime.hour > roomOffHour || (dateTime.hour == roomOffHour && dateTime.minute >= roomOffMinute);

        if (!roomCurrentState && pastPowerOnTime && !pastPowerOffTime) {
            turnOnPower();
        }
        else if (roomCurrentState && pastPowerOffTime) {
            turnOffPower();
        }
    }
}

void turnOnPower() {
    digitalWrite(POWER_RELAY_PIN, LOW);
    roomCurrentState = true;
}

void turnOffPower() {
    digitalWrite(POWER_RELAY_PIN, HIGH);
    roomCurrentState = false;
}

void serialPrintFormattedDateTime(RTCDateTime dateTime) {
    Serial.print(dateTime.year);   Serial.print("-");
    Serial.print(dateTime.month);  Serial.print("-");
    Serial.print(dateTime.day);    Serial.print(" ");
    Serial.print(dateTime.hour);   Serial.print(":");
    Serial.print(dateTime.minute); Serial.print(":");
    Serial.print(dateTime.second); Serial.print("");
}

void setupPower() {
    pinMode(POWER_RELAY_PIN, OUTPUT);
    digitalWrite(POWER_RELAY_PIN, HIGH);

    roomOnHour = 11;
    roomOnMinute = 22;
    roomOffHour = 11;
    roomOffMinute = 23;
}