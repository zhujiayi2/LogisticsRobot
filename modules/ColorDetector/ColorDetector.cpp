#include "ColorDetector.h"
#include "ArduinoLog.h"

[[maybe_unused]] void color_detector::ColorDetector::Detect() {
    if (tcs_34725_.begin()) {
        uint16_t clear, red, green, blue;
        tcs_34725_.getRawDataOneShot(&red, &green, &blue, &clear);
        color_val_[0] = static_cast<int>(red * 256.0 / static_cast<double>(clear));
        color_val_[1] = static_cast<int>(green * 256.0 / static_cast<double>(clear));
        color_val_[2] = static_cast<int>(blue * 256.0 / static_cast<double>(clear));
    } else
        Log.errorln("TCS34725 not found.");
}

[[maybe_unused]] color_detector::Colors color_detector::ColorDetector::Recognize() const {
    int max_color_val = -1, max_color_index = 0;
    for (auto i = 0; i < 3; ++i)
        if (color_val_[i] > max_color_val)
            max_color_index = i + 1;
    return static_cast<Colors>(max_color_index);
}

[[maybe_unused]] color_detector::Colors color_detector::ColorDetector::GetColor() {
    for (auto &c: color_list_) {
        Detect();
        c = Recognize();
    }

    int times[Colors::SIZE] = {0};
    for (const auto &c: color_list_)
        ++times[c];
    Colors mode_color = kNone;
    int max_time = 0;
    for (auto c = 0; c < Colors::SIZE; ++c)
        if (times[c] > max_time)
            mode_color = static_cast<Colors>(c);
    return mode_color;
}

[[maybe_unused]] color_detector::ColorDetector &ColorDetector = color_detector::ColorDetector::Instance();
