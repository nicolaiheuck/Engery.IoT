#include "roomPower.h"

extern DS3231 clock;

int roomOnHour = 0;
int roomOnMinute = 0;
int roomOffHour = 0;
int roomOffMinute = 0;
bool roomCurrentState = false;
ulong roomLastCheckedMillis = 0;

void loopRoomPower() {
    RTCDateTime dateTime = clock.getDateTime();
    if (roomLastCheckedMillis + ROOM_POWER_CHECK_INTERVAL < millis()) {
        roomLastCheckedMillis = millis();
        Serial.print("Checking room power (");
        serialPrintFormattedDateTime(dateTime);
        Serial.println(")");

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
    digitalWrite(ROOM_POWER_RELAY_PIN, LOW);
    roomCurrentState = true;
}

void turnOffPower() {
    digitalWrite(ROOM_POWER_RELAY_PIN, HIGH);
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

void setupRoomPower() {
    pinMode(ROOM_POWER_RELAY_PIN, OUTPUT);
    digitalWrite(ROOM_POWER_RELAY_PIN, HIGH);
}

void setRoomSettings(String &payload) {
    DynamicJsonDocument locationData(1024);
    deserializeJson(locationData, payload);

    String startDate = locationData["ClassStartdate"];
    String endDate = locationData["ClassEnddate"];
    getHourAndMinuteFromDateTimeString(startDate, &roomOnHour, &roomOnMinute);

    getHourAndMinuteFromDateTimeString(endDate, &roomOffHour, &roomOffMinute);
}

void getHourAndMinuteFromDateTimeString(String &dateTime, int *hour, int *minute) {
    int timeSplitterIndex = dateTime.indexOf("T");
    int firstColonIndex = dateTime.indexOf(":");
    int secondColonIndex = firstColonIndex + 3;

    String parsedHour = dateTime.substring(timeSplitterIndex + 1, firstColonIndex);
    String parsedMinute = dateTime.substring(firstColonIndex + 1, secondColonIndex);

    *hour = parsedHour.toInt();
    *minute = parsedMinute.toInt();
}