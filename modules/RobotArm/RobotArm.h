/**
 * @brief Driver of robot arm header file.
 * @author trantuan-20048607
 * @date 2022.5.15
 */

#ifndef ROBOT_ARM_H_
#define ROBOT_ARM_H_

#include <Arduino.h>
#include <ServoTimer2.h>
#include "ColorDetector.h"

namespace robot_arm {
    constexpr uint8_t kServoNum = 4;  ///< Number of servos
    constexpr int kServoPort[kServoNum] = {2, 3, 4, 5};  ///< Ports of servos
    constexpr int kDivPartNum = 40;  ///< Parts to divide when moving

    enum Blocks {
        kNone [[maybe_unused]] = 0x0,
        kBlockA = 0x1,
        kBlockB = 0x2,
        kBlockC = 0x3,
        SIZE = 4
    };

    class RobotArm {
    public:
        static RobotArm &Instance() {
            static RobotArm _{};
            return _;
        }

        [[maybe_unused]] void Initialize();

        [[maybe_unused]] void Run();

    private:
        RobotArm() :
                servo_() {}

        void Handle(Blocks block);

        void Grab(Blocks block);

        void Place(color_detector::Colors color);

        void ServoStart(int index);

        [[maybe_unused]] void ServoStop(int index);

        void ServoGo(int index, int dest);

        void ServoMove(float v1, float v2, float v3, float v4);

        ServoTimer2 servo_[kServoNum];
        float servo_value_[kServoNum]{1500, 1850, 860, 1800};
    };
}

[[maybe_unused]] extern robot_arm::RobotArm &RobotArm;

using Blocks [[maybe_unused]] = robot_arm::Blocks;

#endif  // ROBOT_ARM_H_
