#include "crystallize.h"

#include <cmath>
#include <vector>

Crystallize::Crystallize(int32_t center_number) : center_number_(center_number) {
}

void Crystallize::Apply(Image &image) const {
    int32_t width = image.GetWidth();
    int32_t height = image.GetHeight();
    std::vector<int32_t> centers_x(center_number_);
    std::vector<int32_t> centers_y(center_number_);
    std::vector<DoubleColour> centers_colour(center_number_);
    for (int32_t i = 0; i < center_number_; ++i) {
        centers_x[i] = rand() % height;
        centers_y[i] = rand() % width;
        centers_colour[i] = image.GetColour(centers_x[i], centers_y[i]);
    }
    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            int32_t min_dist = width * width + height * height + 1;
            DoubleColour nearest_center;
            for (int32_t k = 0; k < center_number_; ++k) {
                int32_t cur_dist = (i - centers_x[k]) * (i - centers_x[k]) + (j - centers_y[k]) * (j - centers_y[k]);
                if (min_dist >= cur_dist) {
                    min_dist = cur_dist;
                    nearest_center = centers_colour[k];
                }
            }
            image.SetColour(i, j, nearest_center);
        }
    }
}