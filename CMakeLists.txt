add_executable(
        image_processor
        image_processor.cpp
        lib/filters/filter_handler.cpp lib/filters/filter.cpp lib/common/image.cpp lib/common/bmp.cpp lib/cmd/parser.cpp lib/filters/sharpening.cpp lib/filters/oil_painting.cpp lib/filters/negative.cpp lib/filters/grayscale.cpp lib/filters/gaussian_blur.cpp lib/filters/edge_detection.cpp lib/filters/crop.cpp)
add_catch(test_image_processor lib/tests/test.cpp image_processor.cpp
        lib/filters/filter_handler.cpp lib/filters/filter.cpp lib/common/image.cpp lib/common/bmp.cpp lib/cmd/parser.cpp lib/filters/sharpening.cpp lib/filters/oil_painting.cpp lib/filters/negative.cpp lib/filters/grayscale.cpp lib/filters/gaussian_blur.cpp lib/filters/edge_detection.cpp lib/filters/crop.cpp)
