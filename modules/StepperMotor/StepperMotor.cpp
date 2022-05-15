#include "StepperMotor.h"

stepper_motor::StepperMotor::StepperMotor() :
        stepper_x_(1, 45, 44),
        stepper_y_(1, 33, 32),
        stepper_z_(1, 43, 42),
        stepper_a_(1, 31, 30) {}

[[maybe_unused]] void stepper_motor::StepperMotor::Initialize() {
    pinMode(kEnablePin, OUTPUT);  // Set enable pin to OUTPUT mode.
    digitalWrite(kEnablePin, LOW);
    // Add steppers to the stepper group.
    steppers_.addStepper(stepper_x_);
    steppers_.addStepper(stepper_y_);
    steppers_.addStepper(stepper_z_);
    steppers_.addStepper(stepper_a_);
    // TODO stepperSet(V_MAX);  // Configure the initial MAX speed.
}

[[maybe_unused]] void stepper_motor::StepperMotor::SetMaxSpeed(double v) {
    stepper_x_.setMaxSpeed(static_cast<float>(v));
    stepper_y_.setMaxSpeed(static_cast<float>(v));
    stepper_z_.setMaxSpeed(static_cast<float>(v));
    stepper_a_.setMaxSpeed(static_cast<float>(v));
}

[[maybe_unused]] void stepper_motor::StepperMotor::Move(double x, double y, double z, double a) {
    double step_x = -x * kTotalStep, step_y = -y * kTotalStep,
            step_z = -z * kTotalStep, step_a = -a * kTotalStep;
    long positions[4] = {static_cast<long>(step_x),
                         static_cast<long>(step_y),
                         static_cast<long>(step_z),
                         static_cast<long>(step_a)};
    steppers_.moveTo(positions);  // Set destination.
    steppers_.runSpeedToPosition();  // Start moving to given round number.
    // Set the new departure point.
    stepper_x_.setCurrentPosition(0);
    stepper_y_.setCurrentPosition(0);
    stepper_z_.setCurrentPosition(0);
    stepper_a_.setCurrentPosition(0);
}

[[maybe_unused]] stepper_motor::StepperMotor &StepperMotor = stepper_motor::StepperMotor::Instance();
