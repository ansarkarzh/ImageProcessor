/* This effect is achieved by examining the nearest pixels for all pixels.
   For every pixel, it finds the maximum repeated color and that color will be considered as the output.
   In effect, we will get a blocky image with less information, and it will be similar to
   the painting effect of the image. */

#include "oil_painting.h"

#include <cmath>

OilPainting::OilPainting() {
    intensity_ = 0;
    filter_range_ = 0;
}

void OilPainting::SetParams(std::vector<std::string>& filter_params) {
    if (filter_params.size() != 2) {
        throw "-oil takes 2 parameters";
    }
    intensity_ = StringToInt(filter_params[0]);
    filter_range_ = StringToInt(filter_params[1]);
}

void OilPainting::Apply(Image& img) {
    std::vector<Color> new_colors;
    std::pair<int, int> size = img.GetSize();
    if (filter_range_ > std::max(size.first, size.second)) {
        filter_range_ = std::max(size.first, size.second);
    }
    new_colors.reserve(size.second * size.first);
    for (int y = 0; y < size.second; ++y) {
        for (int x = 0; x < size.first; ++x) {
            int current_intensity = 0;
            int max_intensity = 0;
            int max_index = 0;
            std::vector<int> intensity_bin(intensity_ + 1, 0);
            std::vector<float> red_intensity(intensity_ + 1, 0);
            std::vector<float> green_intensity(intensity_ + 1, 0);
            std::vector<float> blue_intensity(intensity_ + 1, 0);
            for (int dy = -filter_range_; dy <= filter_range_; ++dy) {
                for (int dx = -filter_range_; dx <= filter_range_; ++dx) {
                    int h = y + dy;
                    int w = x + dx;
                    h = h >= size.second ? size.second - 1 : h;
                    h = h < 0 ? 0 : h;
                    w = w >= size.first ? size.first - 1 : w;
                    w = w < 0 ? 0 : w;

                    Color clr = img.GetColor(w, h);

                    float clr_sum = (clr.r + clr.g + clr.b);
                    current_intensity = static_cast<int>(std::lround((clr_sum / 3) * static_cast<float>(intensity_)));

                    ++intensity_bin[current_intensity];
                    red_intensity[current_intensity] += clr.r;
                    green_intensity[current_intensity] += clr.g;
                    blue_intensity[current_intensity] += clr.b;

                    if (intensity_bin[current_intensity] > max_intensity) {
                        max_intensity = intensity_bin[current_intensity];
                        max_index = current_intensity;
                    }
                }
            }

            Color new_color;
            new_color.r = red_intensity[max_index] / static_cast<float>(max_intensity);
            new_color.g = green_intensity[max_index] / static_cast<float>(max_intensity);
            new_color.b = blue_intensity[max_index] / static_cast<float>(max_intensity);
            new_colors.push_back(new_color);
        }
    }
    img.SetNewArray(std::move(new_colors));
}

std::string OilPainting::GetHelp() {
    return "Filter OilPainting creates an illusion of an image drawn by hand. Enter -oil {intensity} {filter_range}\n"
           "intensity coefficient changes a range of colors intensities. Recommended value range: 5-50.\n"
           "filter_range is a number of neighbouring pixels used in calculating each pixel value. "
           "Recommended value range: 1-15.";
}