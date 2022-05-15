/**
 * @brief Driver of stepper motor header file.
 * @author trantuan-20048607
 * @date 2022.5.15
 */

#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_

#include <Arduino.h>
#include "LangFeatures.h"
#include "AccelStepper/AccelStepper.h"
#include "AccelStepper/MultiStepper.h"

namespace stepper_motor {
    constexpr uint8_t kEnablePin = 34;  ///< Enable pin of driver board (A4988)
    constexpr uint16_t kMainStep = 200;  ///< Main steps per round
    constexpr uint16_t kMicroStep = 16;  ///< Subdivided steps per one main step
    constexpr uint16_t kTotalStep = kMainStep * kMicroStep;  ///< Total steps

    /**
     * @brief Main class of stepper motor, SINGLETON.
     * @warning All use of StepperMotor are redirected to stepper_motor::StepperMotor::Instance().
     */
    class StepperMotor : NO_COPY, NO_MOVE {
    public:
        [[maybe_unused]] inline static StepperMotor &Instance() {
            static StepperMotor _{};
            return _;
        }

        [[maybe_unused]] void Initialize();

        [[maybe_unused]] void SetMaxSpeed(double v);

        [[maybe_unused]] void Move(double x, double y, double z, double a);

    private:
        StepperMotor();

        /// AccelStepper parameters on each axis
        AccelStepper stepper_x_, stepper_y_, stepper_z_, stepper_a_;
        MultiStepper steppers_;  ///< Stepper group
    };
}

[[maybe_unused]] extern stepper_motor::StepperMotor &StepperMotor;

#endif  // STEPPER_MOTOR_H_
