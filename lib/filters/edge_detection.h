#pragma once

#include "filter.h"

#include <string>

class EdgeDetection : public Filter {
public:
    EdgeDetection() = default;
    void SetParams(std::vector<std::string>& filter_params) final;

    void Apply(Image& img) final;

    std::string GetHelp() override;

private:
    const int filter_matrix_[3][3] = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    float threshold_;
};