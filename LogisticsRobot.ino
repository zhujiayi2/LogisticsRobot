#include <Arduino.h>
#include "ArduinoLog.h"
#include "CarChassis.h"

constexpr uint32_t kBaudRate = 9600;

void setup() {
    Serial.begin(kBaudRate);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);

    for (auto i = 0; i < 2; i++) {
        pinMode(car_chassis::kOutsideSensorPin[i], INPUT);
        pinMode(car_chassis::kMedialSensorPin[i], INPUT);
    }

    StepperMotor.Initialize();
}

void loop() {
#ifdef DEBUG
    CarChassis::PrintDistance();
    CarChassis::PrintGrayValue();
    Log.infoln("Cross detect: %d.", CarChassis::CrossDetect());
#endif
    CarChassis::ObstacleAvoid(CarChassis::CrossDetect());
}
