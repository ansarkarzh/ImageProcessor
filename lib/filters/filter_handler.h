#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "../common/image.h"
#include "filter.h"

class ImageProcessor {
public:
    ImageProcessor(Image &src_img, std::vector<std::pair<std::string, std::vector<std::string>>> filters_raw);
    void PrintHelp();

private:
    Image src_img_;
    std::unordered_map<std::string, std::shared_ptr<Filter>> name_to_filter_;
};