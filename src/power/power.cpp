#include "power.h"

EnergyMonitor monitor;
double kiloWattHours = 0;
int peakKiloWatt = 0;
ulong lastPowerReadingMillis = 0;

void setupPower() {
    pinMode(POWER_READING_PIN, INPUT);
    monitor.current(POWER_READING_PIN, POWER_READING_CALIBRATION);
    monitor.calcIrms(7500); // First time calibration to avoid high initial readings
}

void loopPower() {
    // A : RMSCurrent
    // W : RMSPower
    // kWh : kiloWattHours
    // W : peakKiloWatt
    if (lastPowerReadingMillis + POWER_READING_INTERVAL < millis()) {
        lastPowerReadingMillis = millis();

        double RMSCurrent = monitor.calcIrms(1480);
        int RMSPower = 230 * RMSCurrent;    //Calculates RMS Power Assuming Voltage 230VAC
        if (RMSPower > peakKiloWatt) {
            peakKiloWatt = RMSPower;
        }
        kiloWattHours += (RMSPower * (2.05 / 60 / 60 / 1000));
        Serial.println(
                "A: " + String(RMSCurrent) + " W: " + String(RMSPower) + " kWh: " + String(kiloWattHours) + " W: " +
                peakKiloWatt);
    }
}

void resetPowerReadings() {
    kiloWattHours = 0;
    peakKiloWatt = 0;
}