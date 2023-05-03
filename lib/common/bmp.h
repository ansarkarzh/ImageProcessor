#pragma once

#include <string>
#include "image.h"

void ExportImage(const std::string& path, Image& image);

Image Import(const std::string& path);
