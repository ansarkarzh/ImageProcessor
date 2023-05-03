#include "sharpening.h"

void Sharpening::Apply(Image& img) {
    std::vector<Color> new_colors;
    std::pair<int, int> size = img.GetSize();
    new_colors.reserve(size.second * size.first);
    for (int y = 0; y < size.second; ++y) {
        for (int x = 0; x < size.first; ++x) {
            Color color = ApplyMatrix(y, x, img, filter_matrix_);
            new_colors.push_back(color);
        }
    }
    img.SetNewArray(std::move(new_colors));
}

void Sharpening::SetParams(std::vector<std::string>& filter_params) {
    if (!filter_params.empty()) {
        throw "-sharp does not take any parameters";
    }
}

std::string Sharpening::GetHelp() {
    return "Filter Sharpening sharpens an image. Enter -sharp";
}