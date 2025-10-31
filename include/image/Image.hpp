#pragma once

#include <vector>
#include <tuple>

using ColorTuple = std::tuple<float, float, float>;

class Image
{
private:
    unsigned int width = 0;
    unsigned int height = 0;
    std::vector<ColorTuple> buffer;

public:
    Image(unsigned int w, unsigned int h);
    Image(unsigned int w, unsigned int h, ColorTuple c);
    ~Image();

    void SetPixel(unsigned int x, unsigned int y, ColorTuple color);
    ColorTuple GetPixel(unsigned int x, unsigned int y);

    void WriteFile(const char* filename);
};