#pragma once

#include "filter.h"

class GaussianBlur : public Filter {
public:
    GaussianBlur();
    void SetParams(std::vector<std::string>& filter_params) final;
    void Apply(Image& img) final;

    void KernelCalc();
    void ApplyToAxis(Image& img, bool axis);

    std::string GetHelp() override;

private:
    const float pi_ = 3.14159;
    float sigma_;
    const float sigma_coef_ = 6;
    const float e_ = 2.71828;

    std::vector<float> kernel_;
};