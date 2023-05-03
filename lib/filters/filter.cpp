#include "filter.h"

#include <iostream>

Color Filter::ApplyMatrix(int h, int w, Image& img, const int (*filter_matrix)[3]) {
    int img_h = img.GetSize().second;
    int img_w = img.GetSize().first;
    float sum_r = 0;
    float sum_g = 0;
    float sum_b = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int coord_h = h + dy;
            int coord_w = w + dx;
            if (coord_h >= img_h) {
                coord_h -= 1;
            } else if (coord_h < 0) {
                coord_h += 1;
            }
            if (coord_w >= img_w) {
                coord_w -= 1;
            } else if (coord_w < 0) {
                coord_w += 1;
            }
            sum_r += static_cast<float>(filter_matrix[1 + dy][1 + dx]) * img.GetColor(coord_w, coord_h).r;
            sum_g += static_cast<float>(filter_matrix[1 + dy][1 + dx]) * img.GetColor(coord_w, coord_h).g;
            sum_b += static_cast<float>(filter_matrix[1 + dy][1 + dx]) * img.GetColor(coord_w, coord_h).b;
        }
    }
    sum_r = std::min(static_cast<float>(1), std::max(static_cast<float>(0), sum_r));
    sum_g = std::min(static_cast<float>(1), std::max(static_cast<float>(0), sum_g));
    sum_b = std::min(static_cast<float>(1), std::max(static_cast<float>(0), sum_b));
    return {sum_r, sum_b, sum_g};
}

int Filter::StringToInt(const std::string& s) {
    try {
        int num = std::stoi(s);
        if (num < 0) {
            throw "negative number";
        }
        return num;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    return 0;
}

float Filter::StringToFloat(const std::string& s) {
    try {
        float num = std::stof(s);
        if (num < 0) {
            throw "negative number";
        }
        return num;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << std::endl;
    }
    return 0;
}