#pragma once

#include "../common/image.h"

#include <string>

class Filter {
public:
    virtual ~Filter() = default;
    virtual void Apply(Image&) = 0;
    virtual void SetParams(std::vector<std::string>& filter_params) = 0;
    Color ApplyMatrix(int h, int w, Image& img, const int filter_matrix[][3]);
    int StringToInt(const std::string& s);
    float StringToFloat(const std::string& s);

    virtual std::string GetHelp() = 0;
};