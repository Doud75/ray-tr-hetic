#include <iostream>
#include "raymath/Color.hpp"
#include "image/Image.hpp"

int main()
{
    const int image_width = 512;
    const int image_height = 512;

    Image image(image_width, image_height);

    // Dégradé horizontal du rouge (à gauche) vers le bleu (à droite)
    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            float t = float(i) / (image_width - 1); // 0 à 1

            float r = 1.0f * (1.0f - t); 
            float g = 0.0f;              
            float b = 1.0f * t;          

            Color pixel_color(r, g, b);
            image.SetPixel(i, j, pixel_color);
        }
    }

    const char* filename = "output_gradient.png";
    image.WriteFile(filename);

    return 0;
}