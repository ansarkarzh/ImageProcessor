#include "bmp.h"

#include <fstream>

const int BYTES_SIZE2 = 8;
const int BYTES_SIZE4 = 16;
const int BYTES_SIZE6 = 24;

void ExportImage(const std::string &path, Image &image) {
    std::ofstream f;
    f.open(path.data(), std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        throw "The output file can not be opened";
    }

    int w = image.GetSize().first;
    int h = image.GetSize().second;

    unsigned char bmp_pad[3] = {0, 0, 0};
    const int padding_size = ((4 - (w * 3) % 4) % 4);

    const int file_header_size = 14;
    const int information_header_size = 40;
    const int file_size = file_header_size + information_header_size + w * h * 3 + padding_size * h;

    unsigned char file_header[file_header_size];

    // File Type
    file_header[0] = 'B';
    file_header[1] = 'M';
    // File size
    const int file_size_index1 = 2;
    const int file_size_index2 = 3;
    const int file_size_index3 = 4;
    const int file_size_index4 = 5;
    file_header[file_size_index1] = file_size;
    file_header[file_size_index2] = file_size >> BYTES_SIZE2;
    file_header[file_size_index3] = file_size >> BYTES_SIZE4;
    file_header[file_size_index4] = file_size >> BYTES_SIZE6;
    // Reserved (Not used)
    const int reserved_indexes_begin = 6;
    const int reserved_indexes_end = 13;
    for (int i = reserved_indexes_begin; i <= reserved_indexes_end; ++i) {
        file_header[i] = 0;
    }
    // Pixel data offset
    const int file_header_size_index = 10;
    file_header[file_header_size_index] = file_header_size + information_header_size;

    unsigned char information_header[information_header_size];

    // Header size
    information_header[0] = information_header_size;
    const int information_header_begin = 1;
    const int information_header_end = 3;
    for (int i = information_header_begin; i <= information_header_end; ++i) {
        information_header[i] = 0;
    }
    // Image width
    const int width_index1 = 4;
    const int width_index2 = 5;
    const int width_index3 = 6;
    const int width_index4 = 7;
    information_header[width_index1] = w;
    information_header[width_index2] = w >> BYTES_SIZE2;
    information_header[width_index3] = w >> BYTES_SIZE4;
    information_header[width_index4] = w >> BYTES_SIZE6;
    // Image height
    const int height_index1 = 8;
    const int height_index2 = 9;
    const int height_index3 = 10;
    const int height_index4 = 11;
    information_header[height_index1] = h;
    information_header[height_index2] = h >> BYTES_SIZE2;
    information_header[height_index3] = h >> BYTES_SIZE4;
    information_header[height_index4] = h >> BYTES_SIZE6;
    // Unused info
    const int unused_info_begin = 15;
    const int unused_info_end = 39;
    for (int i = unused_info_begin; i <= unused_info_end; ++i) {
        information_header[i] = 0;
    }
    // Plane info
    const int plane_info1 = 12;
    const int plane_info2 = 13;
    information_header[plane_info1] = 1;
    information_header[plane_info2] = 0;
    // Bits per pixel (RGB)
    const int bits_per_pixel = 24;
    const int bits_per_pixel_ind = 14;
    information_header[bits_per_pixel_ind] = bits_per_pixel;

    f.write(reinterpret_cast<char *>(file_header), file_header_size);
    f.write(reinterpret_cast<char *>(information_header), information_header_size);

    const float rgb_float = 255.0f;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            unsigned char r = static_cast<unsigned char>(image.GetColor(x, y).r * rgb_float);
            unsigned char g = static_cast<unsigned char>(image.GetColor(x, y).g * rgb_float);
            unsigned char b = static_cast<unsigned char>(image.GetColor(x, y).b * rgb_float);

            unsigned char color[] = {b, g, r};

            f.write(reinterpret_cast<char *>(color), 3);
        }

        f.write(reinterpret_cast<char *>(bmp_pad), padding_size);
    }

    f.close();
}

Image Import(const std::string &path) {
    const char *arr_path = path.data();
    std::ifstream f;
    f.open(arr_path, std::ios::in | std::ios::binary);

    if (!f.is_open()) {
        throw "The input file can not be opened";
    }

    const int file_header_size = 14;
    const int information_header_size = 40;

    unsigned char file_header[file_header_size];
    f.read(reinterpret_cast<char *>(file_header), file_header_size);

    if (file_header[0] != 'B' || file_header[1] != 'M') {
        f.close();
        throw "Not supported format. Use only .bmp images.";
    }

    unsigned char information_header[information_header_size];
    f.read(reinterpret_cast<char *>(information_header), information_header_size);

    const int width_index1 = 4;
    const int width_index2 = 5;
    const int width_index3 = 6;
    const int width_index4 = 7;
    const int height_index1 = 8;
    const int height_index2 = 9;
    const int height_index3 = 10;
    const int height_index4 = 11;
    int width = information_header[width_index1] + (information_header[width_index2] << BYTES_SIZE2) +
                (information_header[width_index3] << BYTES_SIZE4) + (information_header[width_index4] << BYTES_SIZE6);
    int height = information_header[height_index1] + (information_header[height_index2] << BYTES_SIZE2) +
                 (information_header[height_index3] << BYTES_SIZE4) +
                 (information_header[height_index4] << BYTES_SIZE6);

    Image image(width, height);

    const int padding_size = ((4 - (width * 3) % 4) % 4);

    const float rgb_float = 255.0f;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char color_raw[3];
            f.read(reinterpret_cast<char *>(color_raw), 3);

            Color color = {static_cast<float>(color_raw[2]) / rgb_float, static_cast<float>(color_raw[1]) / rgb_float,
                           static_cast<float>(color_raw[0]) / rgb_float};

            image.SetColor(color, x, y);
        }
        f.ignore(padding_size);
    }

    f.close();
    return image;
}