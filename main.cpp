#include "image/Image.hpp"
#include "scene/Camera.hpp"
#include "scene/Scene.hpp"
#include "shapes/Sphere.hpp"
#include "shapes/Plane.hpp"
#include "shapes/Cube.hpp"
#include "utils/RenderMetrics.hpp"
#include "utils/Logger.hpp"
#include "materials/Lambertian.hpp"
#include <fstream>

int main()
{
    Logger logger(Logger::Level::INFO);
    RenderMetrics metrics;
    logger.Info("Starting raytracer...");

    const int image_width = 1920;
    const int image_height = 1080;
    const int samples_per_pixel = 4;

    auto material_ground = std::make_shared<Lambertian>(Color(0.94, 0.53, 0.26));
    auto material_center = std::make_shared<Lambertian>(Color(0.94, 0.53, 0.26));
    auto material_left = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.8));
    auto material_right = std::make_shared<Lambertian>(Color(0.8, 0.6, 0.2));
    auto material_cube = std::make_shared<Lambertian>(Color(0.2, 0.8, 0.3));

    Scene scene;
    scene.add(std::make_shared<Plane>(-0.5f, material_ground));

    scene.add(std::make_shared<Sphere>(Vector(0.0f, 0.0f, -9.0f), 0.5f, material_center));
    scene.add(std::make_shared<Sphere>(Vector(-2.0f, 0.0f, -6.0f), 0.5f, material_left));
    scene.add(std::make_shared<Sphere>(Vector(1.0f, 0.0f, -5.0f), 0.5f, material_right));
    scene.add(std::make_shared<Cube>(
        Vector(-0.90f - 0.35f, -0.5f, -7.0f - 0.35f),
        Vector(-0.90f + 0.35f,  0.2f, -7.0f + 0.35f),
        material_cube
    ));

    
    Image image(image_width, image_height);
    Camera cam(image_width, image_height, samples_per_pixel, 45.0f);

    metrics.StartRender(image_width, image_height);

    size_t bufferSize = image_width * image_height * sizeof(Color);
    metrics.RecordImageBufferSize(bufferSize);

    metrics.StartRenderingLoop();

    cam.render(scene, image);

    metrics.StopRenderingLoop();

    const char* filename = "output.png";

    metrics.StartFileWrite();
    image.WriteFile(filename);
    metrics.StopFileWrite();

    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (file.is_open())
    {
        size_t fileSize = static_cast<size_t>(file.tellg());
        metrics.RecordFileSize(fileSize);
        file.close();
    }

    metrics.EndRender();

    logger.Info("Render completed.");
    logger.ReportMetrics(metrics.GenerateReport());

    return 0;
}