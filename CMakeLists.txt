add_executable(
    image_processor
    image_processor.cpp
        parse.h parse.cpp image.h image.cpp apply_filters.h apply_filters.cpp crop.h crop.cpp grayscale.h grayscale.cpp negative.h negative.cpp sharpening.h sharpening.cpp edge_detection.h edge_detection.cpp gaussian_blur.h gaussian_blur.cpp exception.h base_filter.h exception.cpp crystallize.h crystallize.cpp)

add_catch(
        test_image_processor
        unit_tests.cpp
        parse.h parse.cpp image.h image.cpp apply_filters.h apply_filters.cpp crop.h crop.cpp grayscale.h grayscale.cpp negative.h negative.cpp sharpening.h sharpening.cpp edge_detection.h edge_detection.cpp gaussian_blur.h gaussian_blur.cpp exception.h base_filter.h exception.cpp crystallize.h crystallize.cpp)
