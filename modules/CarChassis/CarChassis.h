#ifndef CAR_CHASSIS_H_
#define CAR_CHASSIS_H_

#include "LangFeatures.h"
#include "StepperMotor/StepperMotor.h"

namespace car_chassis {
    class CarChassis : NO_COPY, NO_MOVE {
    public:
        [[maybe_unused]] inline static CarChassis &Instance() {
            static CarChassis _{};
            return _;
        }

    private:
        CarChassis() = default;

        [[maybe_unused]] inline void Forward() { StepperMotor.Move(0.105, -0.104, 0.104, -0.1); }

        [[maybe_unused]] inline void Backward() { StepperMotor.Move(-0.5, 0.5, -0.5, 0.5); }

        [[maybe_unused]] inline void Left() { StepperMotor.Move(0.24, 0.24, 0.24, 0.24); }

        [[maybe_unused]] inline void Right() { StepperMotor.Move(-0.23, -0.23, -0.23, -0.23); }

        [[maybe_unused]] inline void PanLeft(double v) { StepperMotor.Move(v, v, -v, -v); }

        [[maybe_unused]] inline void PanRight(double v) { StepperMotor.Move(-v, -v, v, v); }

        [[maybe_unused]] inline void Stop() { StepperMotor.Move(0, 0, 0, 0); }
    };
}

#endif  // CAR_CHASSIS_H_
