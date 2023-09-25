#include <Adafruit_GFX.h>
//#include <ArduinoJson.h>
//#include "shared/RGB/rgb.h"
//#include "shared/WiFi/wifi.h"
//#include "shared/MQTT/mqtt.h"
//#include "temp/temp.h"
//#include "shared/DS3231/DS3231.h"
//#include "power/power.h"
//#include "shared/RTC/RTC.h"
//#include "thermostat/thermostat.h"

//extern MQTTClient mqttClient;
//extern DS3231 clock;
//
//void ensureConnectivity();
//void onMessageReceivedAlarm(String &topic, String &payload);
//
//void setup() {
//    Serial.begin(9600);
//    randomSeed(analogRead(0));
//    setupTemp();
//    setupRGB();
//    setupRTC();
//    ensureConnectivity();
//    setupThermostat();
//    setupPower();
//}
//
//void loop() {
//    ensureConnectivity();
//    mqttClient.loop();
//    loopTemp();
//    loopRoomPower();
//    loopThermostat();
//}
//
//void ensureConnectivity() {
//    if (WiFi.status() != WL_CONNECTED) {
//        ledWhite();
//        ensureWiFiSetup();
//    }
//
//    while (!mqttClient.connected()) {
//        ledBlue();
//        setupMQTT("EGON_IoT", onMessageReceivedAlarm);
//        mqttClient.subscribe("EUC/51/244/sp/thermostat");
//    }
//}
//
//void onMessageReceivedAlarm(String &topic, String &payload) {
//    Serial.print("Topic: ");
//    Serial.print(topic);
//    Serial.print(" Payload: ");
//    Serial.println(payload);
//
//    if (topic.endsWith("/sp/thermostat")) {
//        DynamicJsonDocument newSettings(256);
//        deserializeJson(newSettings, payload);
//        Serial.println("setThermostatSettings called");
//        setThermostatSettings(newSettings["newTemperature"], newSettings["newHysteresis"]);
//    }
//}

// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance

void setup() {
    Serial.begin(9600);
    pinMode(A6, INPUT);
    emon1.current(A6, 211.1);             // Current: input pin, calibration. 111,1
}

void loop() {
    int readingA6 = analogRead(A6);
//    Serial.println("A6: " + String(readingA6));

    double Irms = emon1.calcIrms(1480);  // Calculate Irms only
    emon1.calcVI(10,10);
    emon1.serialprint();

//    Serial.print(Irms*230.0);	       // Apparent power
//    Serial.print(" ");
//    Serial.println(Irms);		       // Irms

    delay(500);
}

//int currentPin = 1;              // Transducer pin
//double kilos = 0;
//int peakPower = 0;
//
//void setup()
//{
//}
//
//void loop()
//{
//    int current = 0;
//    int maxCurrent = 0;
//    int minCurrent = 1000;
//    for (int i=0 ; i<=200 ; i++)  //Monitors and logs the current input for 200 cycles to determine max and min current
//    {
//        current = analogRead(currentPin);
//        if(current >= maxCurrent)
//            maxCurrent = current;
//        else if(current <= minCurrent)
//            minCurrent = current;
//    }
//    if (maxCurrent <= 517)
//    {
//        maxCurrent = 516;
//    }
//    double RMSCurrent = ((maxCurrent - 516)*0.707)/11.8337;    //Calibration value!
//    int RMSPower = 230*RMSCurrent;    //Calculates RMS Power Assuming Voltage 230VAC
//    if (RMSPower > peakPower)
//    {
//        peakPower = RMSPower;
//    }
//    kilos = kilos + (RMSPower * (2.05/60/60/1000));
//    delay (2000);
//    // A : RMSCurrent
//    // W : RMSPower
//    // kWh : kilos
//    // W : preakPower
//}
