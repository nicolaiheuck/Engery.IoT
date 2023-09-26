#include "power.h"

EnergyMonitor emon;

void setupPower() {
    Serial.begin(9600);
    pinMode(A6, INPUT); //NH_TODO: Does this need to be here
    emon.current(A6, 211.1);

    emon.calcIrms(1480);
    emon.calcIrms(1480);
    emon.calcIrms(1480);
    emon.calcIrms(1480);
    emon.calcIrms(1480);
}

double kilos = 0;
int peakPower = 0;

void debugPower() {
    double current = emon.calcIrms(1480);
    double maxCurrent = 0;
    double minCurrent = 1;

    if (current >= maxCurrent) {
        maxCurrent = current;
    } else if (current <= minCurrent) {
        minCurrent = current;
    }
    if (maxCurrent <= 0.517) {
        maxCurrent = 0.516;
    }

//    double RMSCurrent = ((maxCurrent - 516) * 0.707) / 211.8337;    //Calibration value!
    double RMSCurrent = current;
    int RMSPower = 230 * RMSCurrent;    //Calculates RMS Power Assuming Voltage 230VAC
    if (RMSPower > peakPower) {
        peakPower = RMSPower;
    }
    kilos += (RMSPower * (2.05 / 60 / 60 / 1000));
    Serial.println(
            "A: " + String(RMSCurrent) + " W: " + String(RMSPower) + " kWh: " + String(kilos) + " W: " + peakPower +
            " Current: " + current + "A");
    delay(2000);
    // A : RMSCurrent
    // W : RMSPower
    // kWh : kilos
    // W : preakPower
}

//NH_TODO: Use in usage file
double getUsageInAmps() {
    while (1) { debugPower(); }
    double irms = emon.calcIrms(1480);  // Calculate Irms only
    Serial.println("Power usage: " + String(emon.Irms) + "A");
    return irms;
}