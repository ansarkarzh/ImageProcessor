#include "negative.h"

void Negative::Apply(Image& img) {
    std::vector<Color> new_colors;
    std::pair<int, int> size = img.GetSize();
    new_colors.reserve(size.second * size.first);
    for (int y = 0; y < size.second; ++y) {
        for (int x = 0; x < size.first; ++x) {
            Color color = img.GetColor(x, y);
            color.r = 1 - color.r;
            color.g = 1 - color.g;
            color.b = 1 - color.b;
            new_colors.push_back(color);
        }
    }
    img.SetNewArray(std::move(new_colors));
}

void Negative::SetParams(std::vector<std::string>& filter_params) {
    if (!filter_params.empty()) {
        throw "-neg does not take any parameters";
    }
}

std::string Negative::GetHelp() {
    return "Filter Negative turns an image to its negative. Enter -neg";
}