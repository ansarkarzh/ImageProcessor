#include "filter_handler.h"
#include "crop.h"
#include "grayscale.h"
#include "negative.h"
#include "sharpening.h"
#include "edge_detection.h"
#include "gaussian_blur.h"
#include "oil_painting.h"

#include <iostream>

ImageProcessor::ImageProcessor(Image &src_img,
                               std::vector<std::pair<std::string, std::vector<std::string>>> filters_raw)
    : src_img_(src_img) {

    name_to_filter_["crop"] = std::make_shared<Crop>();
    name_to_filter_["gs"] = std::make_shared<Grayscale>();
    name_to_filter_["neg"] = std::make_shared<Negative>();
    name_to_filter_["sharp"] = std::make_shared<Sharpening>();
    name_to_filter_["edge"] = std::make_shared<EdgeDetection>();
    name_to_filter_["blur"] = std::make_shared<GaussianBlur>();
    name_to_filter_["oil"] = std::make_shared<OilPainting>();

    for (auto &[filter_name, filter_params] : filters_raw) {
        if (!name_to_filter_.contains(filter_name)) {
            throw("Unsupported filter");
        }
        auto filter = name_to_filter_[filter_name];
        filter->SetParams(filter_params);
        filter->Apply(src_img);
    }

    if (filters_raw.empty()) {
        PrintHelp();
    } else {
        std::cout << "Filters successfully applied" << std::endl;
    }
}

void ImageProcessor::PrintHelp() {
    std::cout << "This is a program that applies filters to a single image." << std::endl;
    for (auto &[filter_name, filter_type] : this->name_to_filter_) {
        std::cout << filter_type->GetHelp() << std::endl;
    }
}