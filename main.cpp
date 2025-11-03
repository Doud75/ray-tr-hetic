#include "raymath/Color.hpp"
#include "raymath/Vector.hpp"
#include "raymath/Ray.hpp"
#include "shapes/Sphere.hpp"         // adapte à ton chemin si besoin
#include "image/Image.hpp"
#include "utils/RenderMetrics.hpp"
#include "utils/Logger.hpp"
#include <fstream>
#include <algorithm>

int main()
{
    Logger logger(Logger::Level::INFO);
    RenderMetrics metrics;

    logger.Info("Starting raytracer...");

    const int image_width  = 512;
    const int image_height = 512;

    metrics.StartRender(image_width, image_height);

    Image image(image_width, image_height);
    metrics.RecordImageBufferSize(image_width * image_height * sizeof(Color));

    // --- Scène : une sphère rouge devant la caméra ---
    Sphere sphere(Vector(0.f, 0.f, -1.f), 0.5f, Color(1.f, 0.f, 0.f));

    // --- Caméra pinhole très simple (identique à avant pour l’optique) ---
    Vector origin(0.f, 0.f, 0.f);
    const float viewport_height = 2.0f;
    const float viewport_width  = viewport_height * (float)image_width / (float)image_height;
    const float focal_length    = 1.0f; // plan image à z = -1

    Vector horizontal(viewport_width, 0.f, 0.f);
    Vector vertical(0.f, viewport_height, 0.f);
    Vector lower_left = origin - horizontal * 0.5f - vertical * 0.5f + Vector(0.f, 0.f, -focal_length);

    metrics.StartRenderingLoop();

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            // 1) Couleur de fond EXACTEMENT comme avant (gradient r,g,b)
            float r = static_cast<float>(i) / (image_width  - 1);
            float g = static_cast<float>(j) / (image_height - 1);
            float b = 0.2f;
            Color baseColor(r, g, b);

            // 2) Rayon caméra passant par le pixel (pour tester la sphère)
            float u = (i + 0.5f) / (float)image_width;
            float v = (j + 0.5f) / (float)image_height;
            Vector dir = lower_left + horizontal * u + vertical * v - origin;
            Ray ray(origin, dir);

            // 3) Si intersection -> couleur sphère ; sinon on garde le fond
            HitInfo h;
            Color out = baseColor;
            if (sphere.hit(ray, 0.001f, 1e30f, h)) {
                out = sphere.albedo; // pour l’instant : rouge uni
            }

            image.SetPixel(i, j, out);
        }
    }

    metrics.StopRenderingLoop();

    // garde le même nom que ton fond précédent pour ne rien changer au workflow
    const char* filename = "output_gradient.png";

    metrics.StartFileWrite();
    image.WriteFile(filename);
    metrics.StopFileWrite();

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        size_t fileSize = static_cast<size_t>(file.tellg());
        metrics.RecordFileSize(fileSize);
        file.close();
    }

    metrics.EndRender();

    logger.Info("Render completed.");
    logger.ReportMetrics(metrics.GenerateReport());

    return 0;
}
