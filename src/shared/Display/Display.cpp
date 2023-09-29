//
// Created by Jan Andreasen on 27/09/2023.
//

#include "Display.h"

extern DS3231 clock;
extern MQTTClient mqttClient;
unsigned char image[10240];
Paint paint(image, 0, 0);
Epd epd;
int lastCheckedDay = -1;

/**
 *  @brief: Sets up the display
 *          and inits it with default text
 */
void setupDisplay() {
    epd.Init();
    epd.ClearFrameMemory(0xFF);
    String header[] = { "HEADER TEXT " };
    String body[] = {"CLASS DESCRIPTION", "LINE DESCRIPTION", "START DATE", "END DATE"};
    DisplayText(5,5, header, &Font24, true);
    DisplayText(5, 2, body, &Font20);
    epd.DisplayFrame();
}

/**
 *  @brief: Write text to the screen.
 *          If header = true it requires 1 item in the array
 *          If header = false it requires 4 items in the array.
 *          This won't update the display!
 */
void DisplayText(int x, int y, String text[], sFONT* font, bool header) {
    paint.SetRotate(ROTATE_270);
    paint.SetWidth(128);
    paint.SetHeight(296);
    if (header)
    {
        paint.SetWidth(50);
        paint.Clear(COLORED);
        paint.DrawStringAt(x, y, text[0].c_str(), font, UNCOLORED);
        epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());
    }
    else
    {
        paint.SetWidth(98);
        paint.Clear(UNCOLORED);
        paint.DrawStringAt(x, y, text[0].c_str(), font, COLORED);
        paint.DrawStringAt(x, y + 20, text[1].c_str(), font, COLORED);
        paint.DrawStringAt(0, y + 71, "Start:", &Font8, COLORED);
        paint.DrawStringAt(140, y + 71, "Slut:", &Font8, COLORED);
        paint.DrawStringAt(x, y + 81, text[2].c_str(), &Font16, COLORED);
        paint.DrawStringAt(x + 140, y + 81, text[3].c_str(), &Font16, COLORED);

        epd.SetFrameMemory(paint.GetImage(), 32, 0, paint.GetWidth(), paint.GetHeight());
    }
    delay(100);
}

/**
 *  @brief: Clears display
 *          either black or white
 */
void DisplayClear(int color) {
    paint.Clear(color);
    delay(200);
}

/**
 *  @brief: Updates the display
 *          with whatever is in
 *          the frame buffer :)
 */
void DisplayDisplay() {
    epd.DisplayFrame();
}

/**
 *  @brief: Receives an MQTT payload
 *          and deserializes it for
 *          updating the display
 */
void DisplayDeserializeMQTTPayload(String payload){
    DynamicJsonDocument locationData(1024);
    deserializeJson(locationData, payload);

    // Deserialize and save in local String-type variables (for string operations)
    String _location = locationData["Location"];
    String _locationDescription = locationData["LocationDescription"];
    String _startDate = locationData["ClassStartdate"];
    String _endDate = locationData["ClassEnddate"];

    // Create the two arrays - for header and body
    String _locationDisplayText[] = {
            _location + " - " + _locationDescription
    };

    String data[] = {
            locationData["Description"],
            locationData["Education"],
            _startDate.substring(0, 10),
            _endDate.substring(0, 10)
    };

    // Send the text to the display handler and display the display
    DisplayText(5,5, _locationDisplayText, &Font24, true);
    DisplayText(0, 2, data, &Font20);
    DisplayDisplay();
}

void requestLocation() {
    mqttClient.publish(MQTT_REQUEST_LOCATION_TOPIC, "42");
    Serial.println("New location info requested");
}

void loopDisplay() {
    RTCDateTime dateTime = clock.getDateTime();
    if (dateTime.hour == 0 && dateTime.minute == 0 && dateTime.day != lastCheckedDay) {
        lastCheckedDay = dateTime.day;
        requestLocation();
    }
}