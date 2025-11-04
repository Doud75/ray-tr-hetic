#include "image/Image.hpp"
#include "scene/Camera.hpp"
#include "scene/Scene.hpp"
#include "shapes/Sphere.hpp"
#include "shapes/Plane.hpp"
#include "materials/Lambertian.hpp"
#include "materials/Metal.hpp"
#include "utils/RenderMetrics.hpp"
#include "utils/Logger.hpp"
#include <fstream>

int main()
{
    Logger logger(Logger::Level::INFO);
    RenderMetrics metrics;
    logger.Info("Starting raytracer...");

    const int image_width = 1920;
    const int image_height = 1080;

    auto red_matte = std::make_shared<Lambertian>(Color(1.0f, 0.0f, 0.0f));
    auto blue_mirror = std::make_shared<Metal>(Color(0.7f, 0.8f, 1.0f), 0.0f);
    auto green_matte = std::make_shared<Lambertian>(Color(0.2f, 0.8f, 0.3f));
    auto gold_mirror = std::make_shared<Metal>(Color(1.0f, 0.84f, 0.0f), 0.1f);
    auto purple_matte = std::make_shared<Lambertian>(Color(0.7f, 0.2f, 0.8f));
    auto white_material = std::make_shared<Lambertian>(Color(0.9f, 0.9f, 0.9f));
    auto dark_material = std::make_shared<Lambertian>(Color(0.2f, 0.2f, 0.2f));

    Scene scene;
    scene.add(std::make_shared<Sphere>(Vector(-1.0f, -1.0f, -1.0f), 0.5f, red_matte));
    scene.add(std::make_shared<Sphere>(Vector(1.2f, 0.0f, -1.2f), 0.4f, blue_mirror));
    scene.add(std::make_shared<Sphere>(Vector(-1.0f, 0.0f, -0.8f), 0.3f, green_matte));
    scene.add(std::make_shared<Sphere>(Vector(0.5f, 0.5f, -1.5f), 0.35f, gold_mirror));
    scene.add(std::make_shared<Sphere>(Vector(-0.6f, -0.2f, -1.3f), 0.25f, purple_matte));
    scene.add(std::make_shared<Plane>(-0.5f, white_material, dark_material, 0.5f));
    Image image(image_width, image_height);
    Camera cam(image_width, image_height);

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