#include "base_filter.h"
#include "grayscale.h"

#include <array>

class EdgeDetection : public BaseFilter {
public:
    explicit EdgeDetection(double value);

    void Apply(Image &image) const override;

private:
    constexpr static int32_t Terms = 5;
    constexpr static std::array<int32_t, 5> Dx = {0, -1, 0, 1, 0};
    constexpr static std::array<int32_t, 5> Dy = {0, 0, -1, 0, 1};
    constexpr static std::array<double, 5> Value = {4.0, -1.0, -1.0, -1.0, -1.0};
    double threshold_;
};
