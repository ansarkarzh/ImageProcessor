#pragma once

#include "filter.h"

class Negative : public Filter {
public:
    void SetParams(std::vector<std::string>& filter_params) final;
    void Apply(Image& img) final;

    std::string GetHelp() override;
};