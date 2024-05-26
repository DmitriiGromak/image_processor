#include "base_filter.h"

class Crop : public BaseFilter {
public:
    void Apply(Image &image) const override;

    Crop(int32_t new_width, int32_t new_height);

private:
    int32_t new_width_;
    int32_t new_height_;
};
