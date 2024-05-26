#include "negative.h"

void Negative::Apply(Image &image) const {
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            DoubleColour colour = image.GetColour(i, j);
            image.SetColour(i, j, {1 - colour.r, 1 - colour.g, 1 - colour.b});
        }
    }
}
