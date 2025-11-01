#pragma once

#include <vector>
#include "../raymath/Color.hpp"

class Image
{
private:
    unsigned int width = 0;
    unsigned int height = 0;
    std::vector<Color> buffer;

public:
    Image(unsigned int w, unsigned int h);
    Image(unsigned int w, unsigned int h, Color c);
    ~Image();

    void SetPixel(unsigned int x, unsigned int y, const Color& color); //Color& est une réference de l'objet Color (plus opti)
    Color GetPixel(unsigned int x, unsigned int y) const;

    void WriteFile(const char* filename);
};