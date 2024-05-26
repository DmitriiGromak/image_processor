#include "crop.h"

Crop::Crop(int32_t new_width, int32_t new_height) : new_width_(new_width), new_height_(new_height) {
}

void Crop::Apply(Image &image) const {
    image.SetHeight(new_height_);
    image.SetWidth(new_width_);
}
