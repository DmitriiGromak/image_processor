#include "apply_filters.h"

#include <iostream>

bool ValidateFloat(std::string_view str) {
    bool dot_flag = false;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '.') {
            if (dot_flag || i == 0) {
                return false;
            }
            dot_flag = true;
            continue;
        }
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool ValidateInt(std::string_view str) {
    for (size_t i = 0; i < str.size(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

std::shared_ptr<BaseFilter> CreateFilter(const Filters &filter) {
    if (filter.filter_name == "-crop") {
        if (filter.filter_params.size() != 2) {
            throw FilterException("wrong number of crop params\n");
        }
        if (!ValidateInt(filter.filter_params[0]) || !ValidateInt(filter.filter_params[1])) {
            throw FilterException("invalid crop params\n");
        }
        return std::make_shared<Crop>(std::stoi(filter.filter_params[0]), std::stoi(filter.filter_params[1]));
    } else if (filter.filter_name == "-gs") {
        if (!filter.filter_params.empty()) {
            throw FilterException("wrong number of gs params\n");
        }
        return std::make_shared<Grayscale>();
    } else if (filter.filter_name == "-neg") {
        if (!filter.filter_params.empty()) {
            throw FilterException("wrong number of neg params\n");
        }
        return std::make_shared<Negative>();
    } else if (filter.filter_name == "-sharp") {
        if (!filter.filter_params.empty()) {
            throw FilterException("wrong number of sharp params\n");
        }
        return std::make_shared<Sharpening>();
    } else if (filter.filter_name == "-edge") {
        if (filter.filter_params.size() != 1) {
            throw FilterException("wrong number of edge params");
        }
        if (!ValidateFloat(filter.filter_params[0])) {
            throw FilterException("invalid edge params\n");
        }
        return std::make_shared<EdgeDetection>(std::atof(filter.filter_params[0]));
    } else if (filter.filter_name == "-blur") {
        if (filter.filter_params.size() != 1) {
            throw FilterException("wrong number blur params\n");
        }
        if (!ValidateFloat(filter.filter_params[0]) || std::atof(filter.filter_params[0]) == 0) {
            throw FilterException("invalid blur params\n");
        }
        std::cout << std::atof(filter.filter_params[0]);
        return std::make_shared<GaussianBlur>(std::atof(filter.filter_params[0]));
    } else if (filter.filter_name == "-crystallize") {
        if (filter.filter_params.size() != 1) {
            throw FilterException("wrong number of crystallize params\n");
        }
        if (!ValidateInt(filter.filter_params[0])) {
            throw FilterException("invalid crystallize params\n");
        }
        return std::make_shared<Crystallize>(std::atof(filter.filter_params[0]));
    } else {
        throw FilterException("unknown filter\n");
    }
}

void ApplyFilters(const std::vector<Filters> &filters, Image &image) {
    for (const auto &filter : filters) {
        CreateFilter(filter)->Apply(image);
    }
}
