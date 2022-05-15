#include <ArduinoLog.h>
#include "CarChassis.h"
#include "RobotArm.h"

constexpr uint32_t kBaudRate = 9600;
constexpr int kMinDistance = 5;

void setup() {
    Serial.begin(kBaudRate);
    Log.begin(LOG_LEVEL_VERBOSE, &Serial);
    Log.infoln("Current baud rate: %d.", kBaudRate);

    for (auto i = 0; i < 2; i++) {
        pinMode(car_chassis::kOutsideSensorPin[i], INPUT);
        pinMode(car_chassis::kMedialSensorPin[i], INPUT);
    }

    StepperMotor.Initialize();
    RobotArm.Initialize();
}

void loop() {
    CarChassis::ObstacleAvoid(kMinDistance);
}
