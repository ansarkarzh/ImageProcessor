#include "grayscale.h"

void Grayscale::Apply(Image& img) {
    std::vector<Color> new_colors;
    std::pair<int, int> size = img.GetSize();
    new_colors.reserve(size.second * size.first);
    for (int y = 0; y < size.second; ++y) {
        for (int x = 0; x < size.first; ++x) {
            Color old_color = img.GetColor(x, y);
            float new_color = old_color.r * red_coef_ + old_color.g * green_coef_ + old_color.b * blue_coef_;
            new_colors.push_back({new_color, new_color, new_color});
        }
    }
    img.SetNewArray(std::move(new_colors));
}

void Grayscale::SetParams(std::vector<std::string>& filter_params) {
    if (!filter_params.empty()) {
        throw "-gs does not take any parameters";
    }
}

std::string Grayscale::GetHelp() {
    return "Filter Grayscale transforms an image's colors to shades of gray. Enter -gs";
}