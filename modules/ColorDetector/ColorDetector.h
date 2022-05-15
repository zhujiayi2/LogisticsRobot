#ifndef COLOR_DETECTOR_H_
#define COLOR_DETECTOR_H_

#include "LangFeatures.h"
#include "TCS34725.h"

namespace color_detector {
    constexpr uint8_t kDetectTimes = 8;  ///< Detect times

    enum Colors {
        kNone = 0x0,
        kRed = 0x1,
        kGreen = 0x2,
        kBlue = 0x3,
        SIZE = 0x4
    };

    class ColorDetector : NO_COPY {
    public:
        static ColorDetector &Instance() {
            static ColorDetector _{};
            return _;
        }

        [[maybe_unused]] Colors GetColor();

    private:
        ColorDetector() :
                tcs_34725_(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X),
                color_val_(),
                color_list_() {}

        [[maybe_unused]] void Detect();

        [[maybe_unused]] [[nodiscard]] Colors Recognize() const;

        AdafruitTCS34725 tcs_34725_;
        int color_val_[3];
        Colors color_list_[kDetectTimes];
    };
}

[[maybe_unused]] extern color_detector::ColorDetector &ColorDetector;

#endif  // COLOR_DETECTOR_H_
