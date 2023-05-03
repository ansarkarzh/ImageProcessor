#pragma once

#include <string>
#include "filter.h"

class Grayscale : public Filter {
public:
    Grayscale() = default;
    void SetParams(std::vector<std::string>& filter_params) final;
    void Apply(Image& img) final;

    std::string GetHelp() override;

private:
    const float red_coef_ = 0.299;
    const float green_coef_ = 0.587;
    const float blue_coef_ = 0.114;
};