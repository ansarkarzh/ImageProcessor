#include "gaussian_blur.h"

#include <cmath>

GaussianBlur::GaussianBlur() {
    sigma_ = 0;
}

void GaussianBlur::SetParams(std::vector<std::string>& filter_params) {
    if (filter_params.size() != 1) {
        throw "-blur takes 1 parameter";
    }
    sigma_ = GaussianBlur::StringToFloat(filter_params[0]);
}

void GaussianBlur::KernelCalc() {
    kernel_.clear();
    const float coefficient = static_cast<float>(1 / sqrt(2 * pi_ * pow(sigma_, 2)));
    int kernel_size = ceil(sigma_coef_ * sigma_ + 1);
    kernel_size = kernel_size % 2 == 0 ? kernel_size + 1 : kernel_size;
    kernel_.reserve(kernel_size);
    for (int i = 0; i <= kernel_size / 2; ++i) {
        const int x = kernel_size / 2 - i;
        const float div1 = static_cast<float>(pow(x, 2.0));
        const float div2 = static_cast<float>(2 * pow(sigma_, 2));
        const float deg = static_cast<float>(pow(e_, div1 / div2));
        const float val = coefficient * (1 / deg);
        kernel_.push_back(val);
    }
    for (int i = 0; i < kernel_size / 2; ++i) {
        kernel_.push_back(kernel_[kernel_size / 2 - i - 1]);
    }
}

void GaussianBlur::Apply(Image& img) {
    KernelCalc();
    ApplyToAxis(img, true);
    ApplyToAxis(img, false);
}

void GaussianBlur::ApplyToAxis(Image& img, bool axis) {
    std::vector<Color> new_colors;
    std::pair<int, int> size = img.GetSize();
    const int rad = static_cast<int>(kernel_.size() / 2);
    new_colors.reserve(size.second * size.first);
    for (int y = 0; y < size.second; ++y) {
        for (int x = 0; x < size.first; ++x) {
            float sum_r = 0;
            float sum_g = 0;
            float sum_b = 0;
            for (int d = -rad; d <= rad; d++) {
                int h = y;
                int w = x;
                if (axis) {
                    h += d;
                    h = h >= size.second ? size.second - 1 : h;
                    h = h < 0 ? 0 : h;
                } else {
                    w += d;
                    w = w >= size.first ? size.first - 1 : w;
                    w = w < 0 ? 0 : w;
                }
                Color old_color = img.GetColor(w, h);
                sum_r += old_color.r * kernel_[rad + d];
                sum_g += old_color.g * kernel_[rad + d];
                sum_b += old_color.b * kernel_[rad + d];
            }
            sum_r = std::min(static_cast<float>(1), std::max(static_cast<float>(0), sum_r));
            sum_g = std::min(static_cast<float>(1), std::max(static_cast<float>(0), sum_g));
            sum_b = std::min(static_cast<float>(1), std::max(static_cast<float>(0), sum_b));
            new_colors.push_back({sum_r, sum_g, sum_b});
        }
    }
    img.SetNewArray(std::move(new_colors));
}

std::string GaussianBlur::GetHelp() {
    return "Filter Gaussian Blur blurs an image with a certain coefficient. Enter -blur {sigma}";
}