#include "sharpening.h"

void Sharpening::Apply(Image &image) const {
    auto data = image.GetData();
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            DoubleColour new_colour;
            for (int32_t k = 0; k < Terms; ++k) {
                int32_t i1 = std::max(0, std::min(i + Dx[k], height - 1));
                int32_t j1 = std::max(0, std::min(j + Dy[k], width - 1));
                new_colour += data[i1][j1] * Value[k];
            }
            new_colour.Standardize();
            image.SetColour(i, j, new_colour);
        }
    }
}
