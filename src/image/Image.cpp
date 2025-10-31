#include <iostream>
#include <cmath>
#include <stdexcept>
#include <tuple>
#include "image/Image.hpp"
#include "lodepng.h"

Image::Image(unsigned int w, unsigned int h) : width(w), height(h)
{
    ColorTuple black = std::make_tuple(0.0f, 0.0f, 0.0f);
    buffer.assign(width * height, black);
}

Image::Image(unsigned int w, unsigned int h, ColorTuple c) : width(w), height(h)
{
    buffer.assign(width * height, c);
}

Image::~Image()
{
}

void Image::SetPixel(unsigned int x, unsigned int y, ColorTuple color) {
    unsigned int index = (y * width) + x;

    if (index >= buffer.size()) { throw std::invalid_argument("Image: Invalid index"); }
    buffer[index] = color;
}

ColorTuple Image::GetPixel(unsigned int x, unsigned int y) {
    unsigned int index = (y * width) + x;

    if (index >= buffer.size()) { throw std::invalid_argument("Image: Invalid index"); }
    return buffer[index];
}

void Image::WriteFile(const char * filename) {
    std::vector<unsigned char> image;
    image.resize(width * height * 4);

    for(unsigned index = 0; index < buffer.size(); index++) {
        ColorTuple pixel = buffer[index];
        int offset = index * 4;

        image[offset]     = static_cast<unsigned char>(floor(std::get<0>(pixel) * 255));
        image[offset + 1] = static_cast<unsigned char>(floor(std::get<1>(pixel) * 255));
        image[offset + 2] = static_cast<unsigned char>(floor(std::get<2>(pixel) * 255));
        image[offset + 3] = 255;
    }

    unsigned error = lodepng::encode(filename, image, width, height);

    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}