#include "edge_detection.h"
#include "grayscale.h"

void EdgeDetection::Apply(Image& img) {
    Grayscale grayscale;
    grayscale.Apply(img);
    std::vector<Color> new_colors;
    std::pair<int, int> size = img.GetSize();
    new_colors.reserve(size.second * size.first);
    for (int y = 0; y < size.second; ++y) {
        for (int x = 0; x < size.first; ++x) {
            Color color = ApplyMatrix(y, x, img, filter_matrix_);
            color.r = color.r > threshold_ ? 1.0 : 0.0;
            color.g = color.g > threshold_ ? 1.0 : 0.0;
            color.b = color.b > threshold_ ? 1.0 : 0.0;
            new_colors.push_back(color);
        }
    }
    img.SetNewArray(std::move(new_colors));
}

void EdgeDetection::SetParams(std::vector<std::string>& filter_params) {
    if (filter_params.size() != 1) {
        throw "-edge takes 1 parameter";
    }
    threshold_ = EdgeDetection::StringToFloat(filter_params[0]);
}

std::string EdgeDetection::GetHelp() {
    return "Filter EdgeDetection outlines edges in the image. Enter -edge {threshold}.";
}