#include <iostream>
#include <cmath>
#include "../image/Image.hpp"
#include "lodepng.h"

Image:: Image(unsigned int w, unsigned int h) : width(w), height(h)
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

    for(unsigned index = 0; index < buffer.size(); index++) {
        Color pixel = buffer[index];
        int offset = index * 4;

        image[offset] = (unsigned int)floor(pixel.R() * 255); 
        image[offset + 1] = (unsigned int)floor(pixel.G() * 255); 
        image[offset + 2] = (unsigned int)floor(pixel.B() * 255); 
        image[offset + 2] = static_cast<unsigned char>(std::floor(pixel.B() * 255));
        image[offset + 3] = 255;      // Alpha
    }

    unsigned error = lodepng::encode(filename, image, width, height);

    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}