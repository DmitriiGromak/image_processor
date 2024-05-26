#pragma once

#include "base_filter.h"

class Grayscale : public BaseFilter {
public:
    void Apply(Image &image) const override;

private:
    constexpr static double RedRatio = 0.299;
    constexpr static double GreenRatio = 0.587;
    constexpr static double BlueRatio = 0.114;
};
