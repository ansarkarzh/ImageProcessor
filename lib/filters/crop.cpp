#include "crop.h"

Crop::Crop() {
    w_ = 0;
    h_ = 0;
}

void Crop::SetParams(std::vector<std::string>& filter_params) {
    if (filter_params.size() != 2) {
        throw "-crop takes 2 parameters";
    }
    w_ = Crop::StringToInt(filter_params[0]);
    h_ = Crop::StringToInt(filter_params[1]);
}

void Crop::Apply(Image& img) {
    std::pair<int, int> old_size = img.GetSize();
    if (w_ > old_size.first) {
        w_ = old_size.first;
    }
    if (h_ > old_size.second) {
        h_ = old_size.second;
    }
    std::vector<Color> new_colors;
    new_colors.reserve(old_size.second * old_size.first);
    for (int y = h_; y > 0; --y) {
        for (int x = 0; x < w_; ++x) {
            new_colors.push_back(img.GetColor(x, old_size.second - y));
        }
    }
    img.SetSize(w_, h_);
    img.SetNewArray(std::move(new_colors));
}

std::string Crop::GetHelp() {
    return "Filter Crop resizes an image to a certain size. Enter -crop {width} {height}.";
}