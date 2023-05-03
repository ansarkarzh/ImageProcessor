#include "image.h"

Color::Color() : r(0), g(0), b(0) {
}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {
}

Color::~Color() {
}

Image::Image(int width, int height) : width_(width), height_(height), colors_(std::vector<Color>(width * height)) {
}

Image::~Image() {
}

Color Image::GetColor(int x, int y) const {
    if (static_cast<size_t>(y * width_ + x) < colors_.size()) {
        return colors_[y * width_ + x];
    }
    throw "out of boundaries";
}

void Image::SetColor(const Color& color, int x, int y) {
    if (color.r < 0 || color.r > 1 || color.g < 0 || color.g > 1 || color.b < 0 || color.b > 1) {
        throw "Invalid input";
    }
    colors_[y * width_ + x].r = color.r;
    colors_[y * width_ + x].g = color.g;
    colors_[y * width_ + x].b = color.b;
}

std::pair<int, int> Image::GetSize() {
    return {this->width_, this->height_};
}

void Image::SetSize(int w, int h) {
    if (w < 0 || h < 0) {
        throw "Invalid input";
    }
    this->width_ = w;
    this->height_ = h;
}

void Image::SetNewArray(std::vector<Color>&& colors) {
    this->colors_ = std::move(colors);
}