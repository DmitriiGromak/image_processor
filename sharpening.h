#include "base_filter.h"

#include <array>

class Sharpening : public BaseFilter {
public:
    void Apply(Image &image) const override;

private:
    constexpr static int32_t Terms = 5;
    constexpr static std::array<int32_t, 5> Dx = {0, -1, 0, 1, 0};
    constexpr static std::array<int32_t, 5> Dy = {0, 0, -1, 0, 1};
    constexpr static std::array<double, 5> Value = {5.0, -1.0, -1.0, -1.0, -1.0};
};
