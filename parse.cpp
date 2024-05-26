#include "parse.h"

Input Parse(int argc, char **argv) {
    if (argc < 3) {
        throw ParserException("not enough arguments\n");
    }
    Input data;
    data.input_file = argv[1];
    data.output_file = argv[2];
    for (int32_t i = 3; i < argc; ++i) {
        if (argv[i][0] == '-') {
            data.filters.push_back({});
            data.filters.back().filter_name = argv[i];
        } else {
            data.filters.back().filter_params.push_back(argv[i]);
        }
    }
    return data;
}
