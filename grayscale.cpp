#include "grayscale.h"

void Grayscale::Apply(Image &image) const {
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            DoubleColour colour = image.GetColour(i, j);
            double new_colour = RedRatio * colour.r + GreenRatio * colour.g + BlueRatio * colour.b;
            image.SetColour(i, j, {new_colour, new_colour, new_colour});
        }
    }
}
