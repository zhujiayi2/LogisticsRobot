# Arduino code of 2022 logistics robot project

NOTE: This project is designed for CMake to build. It will be very hard to move it to Arduino IDE.

## Source structure

- `LogisticsRobot.ino` is the main source code file including `setup()` and `loop()`.
- `cmake` contains CMake scripts for configuring Arduino SDK and generating makefile.
- `modules` stores all source files of submodules of this project. Each submodule has its own folder.

## Build on Windows

### Requirements

1. Any MinGW 64 toolchain. It's recommended to use [MSYS2](https://www.msys2.org/).
   [CLion](https://www.jetbrains.com/clion/) has bundled an available MinGW.
2. A [CMake](https://cmake.org/) available in PATH. It's recommended to use [scoop](https://scoop.sh/) to install.
   [CLion](https://www.jetbrains.com/clion/) has bundled an available CMake.
3. Official [Arduino](https://www.arduino.cc/en/software/) IDE.

### Build with CMake

Steps:

1. Open `CMakeLists.txt`, modify the names in `Custom settings`.
2. Open `cmake/ArduinoToolchain.cmake`, check or modify the path and target board
   in `Environment settings` to fit your system environment.
3. Create a directory `build` and open a terminal (Powershell is recommended) in it.
4. Run cmake initialization command. Note that:
    - To build a debug binary for performance testing and debugging, use `-DCMAKE_BUILD_TYPE=Debug` flag,
      otherwise use `-DCMAKE_BUILD_TYPE=Release` flag.
    - Use `-G "CodeBlocks - MinGW Makefiles"` to build a MinGW makefile.
    - Use `-DCMAKE_MAKE_PROGRAM="...\mingw32-make.exe"`to specify the making tool.
      In MSYS2, it is in `...\MSYS64\mingw64\bin`.

   Here is an example:
   ```shell
   cmake -G "CodeBlocks - MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM="...\MSYS64\mingw64\bin\mingw32-make.exe" ..
   ```
   Do not miss the last `..`.
5. If no error occurs, run `...\mingw32-make.exe` to build the binary.
   If it works, you will see message like this and will find a `.hex` file:
   ```text
   ...
   Generating EEP image
   Generating HEX image
   Calculating image size
   Firmware Size:  ...
   EEPROM   Size:  ...

   [100%] Built target ...
   ```
