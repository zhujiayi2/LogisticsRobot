#include <ArduinoLog.h>
#include "RobotArm.h"

void robot_arm::RobotArm::ServoStart(int index) {
    if (!servo_[index].attached()) servo_[index].attach(kServoPort[index]);
    pinMode(kServoPort[index], OUTPUT);
}

[[maybe_unused]] void robot_arm::RobotArm::ServoStop(int index) {
    servo_[index].detach();
    digitalWrite(kServoPort[index], LOW);
}

void robot_arm::RobotArm::ServoGo(int index, int dest) {
    ServoStart(index);
    servo_[index].write(dest);
}

void robot_arm::RobotArm::ServoMove(float v1, float v2, float v3, float v4) {
    float value_args[kServoNum] = {v1, v2, v3, v4};
    float value_delta[kServoNum];
    for (auto i = 0; i < kServoNum; ++i)
        value_delta[i] = (value_args[i] - servo_value_[i]) / kDivPartNum;
    for (auto i = 0; i < kDivPartNum; ++i) {
        for (auto k = 0; k < kServoNum; ++k)
            servo_value_[k] = value_delta[k] == 0 ? value_args[k] : servo_value_[k] + value_delta[k];
        for (auto j = 0; j < kServoNum; ++j)
            ServoGo(j, static_cast<int>(servo_value_[j]));
        delay(70);
    }
}

[[maybe_unused]] void robot_arm::RobotArm::Initialize() {
    for (auto i = 0; i < kServoNum; ++i)
        ServoGo(i, static_cast<int>(servo_value_[i]));
}

[[maybe_unused]] void robot_arm::RobotArm::Run() {
    for (auto i = 1; i < Blocks::SIZE; ++i)
        Handle(static_cast<Blocks>(i));
}

void robot_arm::RobotArm::Grab(Blocks block) {
#ifdef DEBUG
    Log.infoln("Grab: %d.", static_cast<int>(block));
#endif

    switch (block) {
        case kBlockA:
            ServoMove(1650, 1850, 860, 1800);
            ServoMove(1650, 1450, 1400, 1800);
            ServoMove(1650, 1450, 1400, 2100);
            ServoMove(1650, 1600, 750, 2100);
            break;
        case kBlockB:
            ServoMove(1500, 1450, 1400, 1800);
            ServoMove(1500, 1450, 1400, 2100);
            ServoMove(1500, 1600, 750, 2100);
            break;
        case kBlockC:
            ServoMove(1320, 1850, 860, 1800);
            ServoMove(1320, 1450, 1400, 1800);
            ServoMove(1320, 1450, 1400, 2100);
            ServoMove(1320, 1600, 750, 2100);
            break;
        default:
            break;
    }
}

void robot_arm::RobotArm::Place(Colors color) {
#ifdef DEBUG
    Log.infoln("Place: %d.", static_cast<int>(color));
#endif

    switch (color) {
        case Colors::kRed:
            ServoMove(1020, 1600, 750, 2100);
            ServoMove(1020, 1380, 1520, 2100);
            ServoMove(1020, 1380, 1520, 1900);
            ServoMove(1020, 1850, 860, 1900);
            ServoMove(1500, 1850, 860, 1800);
            break;
        case Colors::kGreen:
            ServoMove(880, 1600, 750, 2100);
            ServoMove(880, 1700, 1080, 2100);
            ServoMove(880, 1700, 1080, 1900);
            ServoMove(880, 1600, 750, 1900);
            ServoMove(1500, 1850, 860, 1800);
            break;
        case Colors::kBlue:
            ServoMove(730, 1600, 750, 2100);
            ServoMove(730, 1640, 1160, 2100);
            ServoMove(730, 1640, 1160, 1900);
            ServoMove(730, 1600, 750, 1900);
            ServoMove(1500, 1850, 860, 1800);
            break;
        default:
            break;
    }
}

void robot_arm::RobotArm::Handle(Blocks block) {
    Colors color;
    Grab(block);
    do { color = ColorDetector.GetColor(); } while (!color);
    Place(color);
}

[[maybe_unused]] robot_arm::RobotArm &RobotArm = robot_arm::RobotArm::Instance();
