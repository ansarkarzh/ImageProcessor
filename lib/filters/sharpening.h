#pragma once

#include "filter.h"

class Sharpening : public Filter {
public:
    Sharpening() = default;
    void SetParams(std::vector<std::string>& filter_params) final;
    void Apply(Image& img) final;

    std::string GetHelp() override;

private:
    const int filter_matrix_[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
};