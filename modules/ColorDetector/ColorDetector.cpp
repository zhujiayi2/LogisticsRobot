#include <map>
#include <ArduinoLog.h>
#include "ColorDetector.h"

[[maybe_unused]] color_detector::Colors color_detector::ColorDetector::GetColor() {
    for (auto &c: color_list_) {
        if (adafruit_tcs_34725_.begin()) {
            uint16_t clear, red, green, blue;
            adafruit_tcs_34725_.getRawDataOneShot(&red, &green, &blue, &clear);
            int color_val[3] = {
                    static_cast<int>(red * 256.0 / static_cast<double>(clear)),
                    static_cast<int>(green * 256.0 / static_cast<double>(clear)),
                    static_cast<int>(blue * 256.0 / static_cast<double>(clear))
            };

            int max_color_val = -1, max_color_val_index = 0;
            for (auto i = 0; i < 3; ++i)
                if (color_val[i] > max_color_val)
                    max_color_val_index = i + 1;
            c = static_cast<Colors>(max_color_val_index);
        } else {
            Log.errorln("Failed to connect to TCS34725.");
            c = kNone;
        }
    }

    std::map<Colors, uint8_t> times;
    for (const auto &c: color_list_)
        if (times.find(c) == times.end())
            times[c] = 0;
        else
            ++times[c];
    Colors mode_color = kNone;
    int mode_time = 0;
    for (const auto &it: times)
        if (it.second > mode_time)
            mode_color = it.first;
    return mode_color;
}

[[maybe_unused]] color_detector::ColorDetector &ColorDetector = color_detector::ColorDetector::Instance();
