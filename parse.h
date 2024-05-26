#pragma once

#include <vector>
#include <string>

#include "exception.h"

struct Filters {
    std::string filter_name;
    std::vector<const char *> filter_params;
};

struct Input {
    const char *input_file;
    const char *output_file;
    std::vector<Filters> filters;
};

Input Parse(int argc, char **argv);
