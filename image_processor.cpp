#include "apply_filters.h"
#include "exception.h"
#include "image.h"
#include "iostream"
#include "parse.h"

void Help() {
    std::cout
        << "Crop: -crop int width >= 0; int height >= 0 - crops your image\n"
           "Crystallize: -crystallize int number >= 0 of crystallization centers - makes your image look fragmented\n"
           "Edge Detection: -edge double threshold >= 0 - makes your image look like a system of gray lines\n"
           "Gaussian Blur: -blur double sigma > 0 - blurs your picture\n"
           "Grayscale: -gs - converts your picture to the shades of grey\n"
           "Negative: -neg - reverses every colour\n"
           "Sharpening: -sharp - makes your picture look clearer\n";
}

int main(int argc, char **argv) {
    if (argc == 1) {
        Help();
        return 0;
    }
    try {
        Input parse_results = Parse(argc, argv);
        Image image;
        image.Read(parse_results.input_file);
        ApplyFilters(parse_results.filters, image);
        image.Write(parse_results.output_file);
        return 0;
    } catch (ImageProcessorException &exc) {
        std::cerr << exc.what() << '\n';
        Help();
        return 1;
    } catch (...) {
        std::cerr << "Unknown error\n";
        Help();
        return 2;
    }
}
