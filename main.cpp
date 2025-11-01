#include "raymath/Color.hpp"
#include "image/Image.hpp"

int main()
{
    const int image_width = 512;
    const int image_height = 512;

    Image image(image_width, image_height);

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            auto r = static_cast<float>(i) / (image_width - 1);
            auto g = static_cast<float>(j) / (image_height - 1);
            auto b = 0.2f;

            image.SetPixel(i, j, Color(r, g, b));
        }
    }

    const char* filename = "output_gradient.png";
    image.WriteFile(filename);

    return 0;
}