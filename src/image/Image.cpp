#include <iostream>
#include "Image.hpp"
#include "lodepng.h"
#include <cmath>

Image::Image(unsigned int w, unsigned int h) : width(w), height(h)
{
    Color black(0.0f, 0.0f, 0.0f);
    buffer.assign(width * height, black);
}

Image::Image(unsigned int w, unsigned int h, Color c) : width(w), height(h)
{
    buffer.assign(width * height, c);
}

Image::~Image()
{
}

void Image::SetPixel(unsigned int x, unsigned int y, const Color& color) {
    unsigned int index = (y * width) + x;

    if (index >= buffer.size()) { throw std::invalid_argument("Image: Invalid index"); }
    buffer[index] = color;
}

Color Image::GetPixel(unsigned int x, unsigned int y) const {
    unsigned int index = (y * width) + x;

    if (index >= buffer.size()) { throw std::invalid_argument("Image: Invalid index"); }
    return buffer[index];
}

void Image::WriteFile(const char * filename) {
    std::vector<unsigned char> image;
    image.resize(width * height * 4);

    auto clamp = [](float x, float min, float max) {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    };

    for(unsigned index = 0; index < buffer.size(); index++) {
        Color pixel = buffer[index];
        int offset = index * 4;

        float r = sqrt(clamp(pixel.R(), 0.0, 1.0));
        float g = sqrt(clamp(pixel.G(), 0.0, 1.0));
        float b = sqrt(clamp(pixel.B(), 0.0, 1.0));

        image[offset] = static_cast<unsigned char>(255.999 * r);
        image[offset + 1] = static_cast<unsigned char>(255.999 * g);
        image[offset + 2] = static_cast<unsigned char>(255.999 * b);
        image[offset + 3] = 255;
    }

    unsigned error = lodepng::encode(filename, image, width, height);

    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}