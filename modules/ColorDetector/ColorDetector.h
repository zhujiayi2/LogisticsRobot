/**
 * @brief Driver of color detector header file.
 * @author trantuan-20048607
 * @date 2022.5.15
 */

#ifndef COLOR_DETECTOR_H_
#define COLOR_DETECTOR_H_

#include <Adafruit_TCS34725.h>
#include "LangFeatures.h"

namespace color_detector {
    constexpr uint8_t kDetectionTimes = 8;  ///< Detection times per round

    enum Colors {
        kNone = 0x0, kRed = 0x1, kGreen = 0x2, kBlue = 0x3, SIZE = 0x4
    };

    class ColorDetector : SINGLETON {
    public:
        inline static ColorDetector &Instance() {
            static auto *_ = new ColorDetector();
            return *_;
        }

        [[maybe_unused]] Colors GetColor();

    private:
        ColorDetector() :
                adafruit_tcs_34725_(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X),
                color_list_() {}

        Adafruit_TCS34725 adafruit_tcs_34725_;
        Colors color_list_[kDetectionTimes];
    };
}

[[maybe_unused]] extern color_detector::ColorDetector &ColorDetector;

using Colors [[maybe_unused]] = color_detector::Colors;

#endif  // COLOR_DETECTOR_H_
