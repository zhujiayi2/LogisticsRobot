#include <ArduinoLog.h>
#include "CarChassis.h"
#include "RobotArm.h"

[[maybe_unused]] void car_chassis::CarChassis::SetMode(int mode) {
    switch (mode) {
        case 1:
            Right();
            break;
        case 2:
            Left();
            break;
        default:
            Forward();
            break;
    }
}

[[maybe_unused]] long car_chassis::CarChassis::GetDistance(const int *pin) {
    long duration;
    pinMode(pin[1], OUTPUT);
    pinMode(pin[0], INPUT);
    digitalWrite(pin[1], LOW);
    delayMicroseconds(2);
    digitalWrite(pin[1], HIGH);
    delayMicroseconds(20);
    digitalWrite(pin[1], LOW);
    duration = static_cast<long>(pulseIn(pin[0], HIGH, 1500));
    duration /= 59;
    return (duration < 2 || duration > 200) ? 0 : duration;
}

[[maybe_unused]] int car_chassis::CarChassis::CrossDetect() {
    int s = 0;
    for (auto i = 0; i < 2; i++)
        s |= (digitalRead(kOutsideSensorPin[i]) << i);
    return s;
}

[[maybe_unused]] void car_chassis::CarChassis::ObstacleAvoid(int d) {
    if ((GetDistance(kUltrasonicPin) > 2 && GetDistance(kUltrasonicPin) < d)) {
        Forward();
        delay(1000);
        RobotArm.Run();
        delay(50000);
    } else {
#ifdef DEBUG
        CarChassis::PrintDistance();
        CarChassis::PrintGrayValue();
        Log.infoln("Cross detect: %d.", CarChassis::CrossDetect());
#endif
        SetMode(CrossDetect());
    }
}

[[maybe_unused]] void car_chassis::CarChassis::PrintDistance() {
    Log.infoln("Distance: %d cm.", GetDistance(kUltrasonicPin));
}

[[maybe_unused]] void car_chassis::CarChassis::PrintGrayValue() {
    Log.infoln("Gray: %d | %d | %d | %d.",
               !(digitalRead(kOutsideSensorPin[0])),
               !(digitalRead(kMedialSensorPin[0])),
               !(digitalRead(kMedialSensorPin[1])),
               !(digitalRead(kOutsideSensorPin[1])));
}
