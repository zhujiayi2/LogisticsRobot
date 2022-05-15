/**
 * @brief Car chassis header file.
 * @author trantuan-20048607
 * @date 2022.5.15
 * @details Diagram:\n
 *   C: Ultrasonic distance sensor\n
 *   H: Gray sensor\n
 *   B: Stepper motor (X:44,45 Y:32,33 Z:42,43 A:30,31)
 *
 * @code
 *                                     (A0, A1)
 *                        (A3)      (A5)  |  (A12)     (A10)
 *                         |         |    |    |         |
 *                    -----H---------H----C----H---------H----
 *   (dir:32,step:33):B                                      B:(44,45)
 *                    |                                      |
 *                    |                                      |
 *                    |                                      |
 *                    |                                      |
 *                    |                                      |
 *   (dir:30,step:31):B                                      B:(42,43)
 *                    ----------------------------------------
 * @endcode
 */

#ifndef CAR_CHASSIS_H_
#define CAR_CHASSIS_H_

#include "LangFeatures.h"
#include "StepperMotor.h"

namespace car_chassis {
    constexpr int kUltrasonicPin[2] = {A1, A0};
    constexpr int kOutsideSensorPin[2] = {A3, A10};
    constexpr int kMedialSensorPin[2] = {A5, A12};
    [[maybe_unused]] constexpr int kSensorPin[4] = {A3, A5, A12, A10};

    class CarChassis : SINGLETON {
    public:
        CarChassis() = delete;

        [[maybe_unused]] static void ObstacleAvoid(int min_distance);

    private:
        static void SetMode(int mode);

        static inline void Forward() { StepperMotor.Move(0.104, -0.104, 0.104, -0.104); }

        [[maybe_unused]] static inline void Backward() { StepperMotor.Move(-0.5, 0.5, -0.5, 0.5); }

        static inline void Left() { StepperMotor.Move(0.24, 0.24, 0.24, 0.24); }

        static inline void Right() { StepperMotor.Move(-0.23, -0.23, -0.23, -0.23); }

        [[maybe_unused]] static inline void PanLeft(double v) { StepperMotor.Move(v, v, -v, -v); }

        [[maybe_unused]] static inline void PanRight(double v) { StepperMotor.Move(-v, -v, v, v); }

        [[maybe_unused]] static inline void Stop() { StepperMotor.Move(0, 0, 0, 0); }

        static long GetDistance(const int pin[2]);

        static int CrossDetect();
    };
}

using CarChassis [[maybe_unused]] = car_chassis::CarChassis;

#endif  // CAR_CHASSIS_H_
