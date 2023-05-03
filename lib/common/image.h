#pragma once

#include <vector>

struct Color {
    float r, g, b;

    Color();
    Color(float r, float g, float b);
    ~Color();
};

class Image {
public:
    explicit Image(int width, int height);
    ~Image();

    Color GetColor(int x, int y) const;
    void SetColor(const Color& color, int x, int y);
    std::pair<int, int> GetSize();
    void SetSize(int w, int h);
    void SetNewArray(std::vector<Color>&& colors);

private:
    int width_;
    int height_;
    std::vector<Color> colors_;
};