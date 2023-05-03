#include <catch.hpp>

#include "image_processor.h"
#include <fstream>

// Function compares 2 bmp images symbol by symbol
bool CompareTwoImages(const char *path1, const char *path2) {
    std::ifstream f1;
    f1.open(path1, std::ios::in | std::ios::binary);
    std::ifstream f2;
    f2.open(path2, std::ios::in | std::ios::binary);
    if (!f1.is_open()) {
        f1.close();
        throw "The input file can not be opened";
    }
    if (!f2.is_open()) {
        f2.close();
        throw "The output file can not be opened";
    }
    f1.seekg(0, f1.end);
    size_t length1 = f1.tellg();
    f1.seekg(0, f1.beg);
    f2.seekg(0, f2.end);
    size_t length2 = f2.tellg();
    f2.seekg(0, f2.beg);
    if (length1 != length2) {
        f1.close();
        f2.close();
        return false;
    }
    const int header_end = 43;
    for (size_t ind = 0; ind < static_cast<size_t>(length1); ++ind) {
        char a = 0;
        char b = 0;
        f1.get(a);
        f2.get(b);

        if (ind > header_end && a != b) {
            f1.close();
            f2.close();
            return false;
        }
    }
    f1.close();
    f2.close();
    return true;
}

TEST_CASE("CropTest") {
    const char *path[] =
        {"prog_name", "../tasks/image_processor/test_script/data/lenna.bmp", "output_test.bmp", "-crop", "800", "600"};
    const int crop_argc = 6;
    main(crop_argc, const_cast<char **>(path));

    REQUIRE(CompareTwoImages("output_test.bmp", "../tasks/image_processor/test_script/data/lenna_crop.bmp"));
}

TEST_CASE("EdgeDetectionTest") {
    const char *path[] =
        {"prog_name", "../tasks/image_processor/test_script/data/flag.bmp", "output_test.bmp", "-edge", "0.1"};
    const int edge_argc = 5;
    main(edge_argc, const_cast<char **>(path));

    REQUIRE(CompareTwoImages("output_test.bmp", "../tasks/image_processor/test_script/data/flag_edge.bmp"));
}

TEST_CASE("GrayscaleTest") {
    const char *path[] =
        {"prog_name", "../tasks/image_processor/test_script/data/lenna.bmp", "output_test.bmp", "-gs"};
    main(4, const_cast<char **>(path));

    REQUIRE(CompareTwoImages("output_test.bmp", "../tasks/image_processor/test_script/data/lenna_gs.bmp"));
}

TEST_CASE("NegativeTest") {
    const char *path[] =
        {"prog_name", "../tasks/image_processor/test_script/data/lenna.bmp", "output_test.bmp", "-neg"};
    main(4, const_cast<char **>(path));

    REQUIRE(CompareTwoImages("output_test.bmp", "../tasks/image_processor/test_script/data/lenna_neg.bmp"));
}

TEST_CASE("SharpTest") {
    const char *path[] =
        {"prog_name", "../tasks/image_processor/test_script/data/lenna.bmp", "output_test.bmp", "-sharp"};
    main(4, const_cast<char **>(path));

    REQUIRE(CompareTwoImages("output_test.bmp", "../tasks/image_processor/test_script/data/lenna_sharp.bmp"));
}

TEST_CASE("BlurTest") {
    const char *path[] =
        {"prog_name", "../tasks/image_processor/test_script/data/lenna.bmp", "output_test.bmp", "-blur", "7.5"};
    main(4, const_cast<char **>(path));

    REQUIRE(CompareTwoImages("output_test.bmp", "../tasks/image_processor/test_script/data/lenna_blur.bmp"));
}

TEST_CASE("OilTest") {
    const char *path[] =
        {"prog_name", "../tasks/image_processor/test_script/data/lenna.bmp", "output_test.bmp", "-oil", "10", "10"};
    main(6, const_cast<char **>(path));

    REQUIRE(CompareTwoImages("output_test.bmp", "../tasks/image_processor/test_script/data/lenna_oil.bmp"));
}