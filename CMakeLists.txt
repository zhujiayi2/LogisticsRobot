cmake_minimum_required(VERSION 2.8.4)

# 使用 Arduino 工具链
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 17)  # C++ 17 标准

# ================================================
#   自定义设置 | Custom settings
# ================================================
set(ARDUINO_SDK_PATH D:/Arduino)  # SDK 路径, 确保内部包含 "hardware" 目录
set(FIRMWARE_NAME firmware)  # 生成的固件文件名
set(TARGET_BOARD mega)  # 目标版型
set(ARDUINO_CPU atmega2560)  # 目标 CPU 型号
set(PROJECT_NAME ArduinoProject)  # CMake 项目名称

# 配置 CMake 项目
project(${PROJECT_NAME})

# ================================================
#   配置内部库 | Configure internal libraries
# ================================================
generate_arduino_library(Wire BOARD ${TARGET_BOARD}  # Wire
        SRCS ${ARDUINO_SDK_PATH}/hardware/arduino/avr/libraries/Wire/src/Wire.cpp)

# ================================================
#   配置外部库 | Configure external libraries
# ================================================
generate_arduino_library(logger BOARD ${TARGET_BOARD}  # logger
        SRCS libs/logger/logger.cpp)

# ================================================
#   生成固件 | Generate firmware
# ================================================
generate_arduino_firmware(${PROJECT_NAME} BOARD ${TARGET_BOARD}
        LIBS logger Wire  # 此处填写链接的库名称, 无先后顺序
        SKETCH arduino-project.ino)  # 项目主文件
