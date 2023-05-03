#pragma once

#include "filter.h"

class OilPainting : public Filter {
public:
    OilPainting();
    void SetParams(std::vector<std::string>& filter_params) final;
    void Apply(Image& img) final;

    std::string GetHelp() override;

private:
    int intensity_;
    int filter_range_;
};