#pragma once

#include "filter.h"

class Crop : public Filter {
public:
    Crop();
    void SetParams(std::vector<std::string>& filter_params) final;

    void Apply(Image& img) final;

    std::string GetHelp() override;

private:
    int h_;
    int w_;
};