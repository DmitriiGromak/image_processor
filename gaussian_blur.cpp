#include "gaussian_blur.h"

#include <cmath>

GaussianBlur::GaussianBlur(double value) : sigma_(value) {
}

void GaussianBlur::Apply(Image &image) const {
    int width = image.GetWidth();
    int height = image.GetHeight();
    std::vector<std::vector<DoubleColour>> data(height, std::vector<DoubleColour>(width));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double x0 = i;
            int min_x = std::max(0, static_cast<int>(x0 - 4 * sigma_));
            int max_x = std::min(height, static_cast<int>(ceil(x0 + 4 * sigma_)));
            double sum = 0;
            for (int k = min_x; k < max_x; ++k) {
                double x = k;
                double indicator = -((x0 - x) * (x0 - x)) / (sigma_ * sigma_ * 2);
                double ratio = (1.0 / sqrt(M_PI * sigma_ * sigma_ * 2) * pow(M_E, indicator));
                data[i][j] += image.GetColour(k, j) * ratio;
                sum += ratio;
            }
            data[i][j] = data[i][j] * (1.0 / sum);
            data[i][j].Standardize();
        }
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            DoubleColour new_colour;
            double y0 = j;
            int min_y = std::max(0, static_cast<int>(y0 - 4 * sigma_));
            int max_y = std::min(width, static_cast<int>(ceil(y0 + 4 * sigma_)));
            double sum = 0;
            for (int l = min_y; l < max_y; ++l) {
                double y = l;
                double indicator = -((y0 - y) * (y0 - y)) / (sigma_ * sigma_ * 2);
                double ratio = (1.0 / sqrt(M_PI * sigma_ * sigma_ * 2) * pow(M_E, indicator));
                new_colour += data[i][l] * ratio;
                sum += ratio;
            }
            new_colour = new_colour * (1.0 / sum);
            new_colour.Standardize();
            image.SetColour(i, j, new_colour);
        }
    }
}
