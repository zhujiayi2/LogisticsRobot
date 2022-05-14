cmake_minimum_required(VERSION 2.8.4)

# Configure Arduino toolchain. Open this file to set up your environment.
set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)
set(CMAKE_CXX_STANDARD 17)  # Use C++17 standard

# ================================================
#   Custom Settings
# ================================================
set(PROJECT_NAME LogisticsRobot)  # CMake project name
set(FIRMWARE_NAME firmware)  # Firmware (.hex) name

# Configure optimizations, depending on -DCMAKE_BUILD_TYPE flag.
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_compile_options(-O0)  # No optimization
elseif (CMAKE_BUILD_TYPE STREQUAL Release)
    add_compile_options(-O3)  # Full optimization
endif ()

# Configure CMake project.
project(${PROJECT_NAME})

# ================================================
#   Configure dependency libraries
# ================================================
generate_arduino_library(Wire BOARD ${TARGET_BOARD}  # Wire
        SRCS ${ARDUINO_SDK_PATH}/hardware/arduino/avr/libraries/Wire/src/Wire.cpp)

# Configure global header searching path.
include_directories(modules)

# ================================================
#   Configure project library
# ================================================
file(GLOB PROJECT_SRCS modules/*/*.c*)
generate_arduino_library(${PROJECT_NAME} BOARD ${TARGET_BOARD} SRCS ${PROJECT_SRCS})

# ================================================
#   Generate firmware
# ================================================
generate_arduino_firmware(${FIRMWARE_NAME}
        BOARD ${TARGET_BOARD}
        LIBS ${PROJECT_NAME} Wire  # Add more libraries here.
        SKETCH LogisticsRobot.ino)
