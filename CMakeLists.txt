cmake_minimum_required(VERSION 2.8.4)

# 使用 Arduino 工具链, 打开此文件设置环境和 CPU 型号
set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 17)  # C++ 17 标准

# ================================================
#   自定义设置 | Custom settings
# ================================================
set(FIRMWARE_NAME firmware)  # 生成的固件文件名
set(PROJECT_NAME ArduinoProject)  # CMake 项目名称

# 为 Debug 和 Release 生成模式配置不同的优化等级
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_compile_options(-O0)  # -O0 模式下, gdb 的定位最准确
elseif (CMAKE_BUILD_TYPE STREQUAL Release)
    add_compile_options(-O3)  # -O3 模式下, 程序运行速度最快
endif ()

# 配置 CMake 项目
project(${PROJECT_NAME})

# ================================================
#   配置内部库 | Configure internal libraries
# ================================================
generate_arduino_library(Wire BOARD ${TARGET_BOARD}  # Wire
        SRCS ${ARDUINO_SDK_PATH}/hardware/arduino/avr/libraries/Wire/src/Wire.cpp)

# 配置头文件搜索路径
include_directories(modules)

# ================================================
#   配置外部库 | Configure external libraries
# ================================================
generate_arduino_library(logger BOARD ${TARGET_BOARD}  # logger
        SRCS modules/logger/logger.cpp)
generate_arduino_library(stepper-motor BOARD ${TARGET_BOARD}  # stepper-motor
        SRCS modules/stepper-motor/stepper-motor.cpp)
generate_arduino_library(car-chassis BOARD ${TARGET_BOARD}  # car-chassis
        SRCS modules/car-chassis/car-chassis.cpp)
# ================================================

# ================================================
#   生成固件 | Generate firmware
# ================================================
generate_arduino_firmware(${PROJECT_NAME} BOARD ${TARGET_BOARD}
        LIBS logger car-chassis stepper-motor Wire  # 此处填写链接的库名称, 无先后顺序
        SKETCH main.ino)  # 项目主文件
