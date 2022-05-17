#include <ArduinoLog.h>
#include "StepperMotor.h"

stepper_motor::StepperMotor::StepperMotor() :
        stepper_x_(1, 45, 44),
        stepper_y_(1, 33, 32),
        stepper_z_(1, 43, 42),
        stepper_a_(1, 31, 30) {}

[[maybe_unused]] void stepper_motor::StepperMotor::Initialize() {
    pinMode(kEnablePin, OUTPUT);
    digitalWrite(kEnablePin, LOW);
    steppers_.addStepper(stepper_x_);
    steppers_.addStepper(stepper_y_);
    steppers_.addStepper(stepper_z_);
    steppers_.addStepper(stepper_a_);
    SetMaxSpeed(static_cast<double>(kMaxSpeed));
}

[[maybe_unused]] void stepper_motor::StepperMotor::SetMaxSpeed(double v) {
    stepper_x_.setMaxSpeed(static_cast<float>(v));
    stepper_y_.setMaxSpeed(static_cast<float>(v));
    stepper_z_.setMaxSpeed(static_cast<float>(v));
    stepper_a_.setMaxSpeed(static_cast<float>(v));
}

[[maybe_unused]] void stepper_motor::StepperMotor::Move(double x, double y, double z, double a) {
    long positions[4] = {static_cast<long>(-x * kTotalStep),
                         static_cast<long>(-y * kTotalStep),
                         static_cast<long>(-z * kTotalStep),
                         static_cast<long>(-a * kTotalStep)};
#ifdef DEBUG
    Log.infoln("Move to: X %F Y %F Z %F A %F.", positions[0], positions[1], positions[2], positions[3]);
#endif
    steppers_.moveTo(positions);
    steppers_.runSpeedToPosition();
    stepper_x_.setCurrentPosition(0);
    stepper_y_.setCurrentPosition(0);
    stepper_z_.setCurrentPosition(0);
    stepper_a_.setCurrentPosition(0);
}

[[maybe_unused]] stepper_motor::StepperMotor &StepperMotor = stepper_motor::StepperMotor::Instance();
