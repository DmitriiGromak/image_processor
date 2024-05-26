#include <memory>

#include "base_filter.h"
#include "crop.h"
#include "crystallize.h"
#include "edge_detection.h"
#include "exception.h"
#include "gaussian_blur.h"
#include "grayscale.h"
#include "image.h"
#include "negative.h"
#include "parse.h"
#include "sharpening.h"

bool ValidateFloat(std::string_view str);

bool ValidateInt(std::string_view str);

std::shared_ptr<BaseFilter> CreateFilter(const Filters &filters);

void ApplyFilters(const std::vector<Filters> &filters, Image &image);
