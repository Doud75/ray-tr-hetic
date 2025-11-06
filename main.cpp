#include "image/Image.hpp"
#include "scene/Camera.hpp"
#include "scene/Scene.hpp"
#include "shapes/Sphere.hpp"
#include "shapes/Plane.hpp"
#include "shapes/Cube.hpp"
#include "utils/RenderMetrics.hpp"
#include "utils/Logger.hpp"
#include "materials/Lambertian.hpp"
#include "materials/CheckerBoard.hpp"
#include "materials/SideColorMaterial.hpp"
#include "materials/Metal.hpp"
#include <fstream>
#include <functional>

Color blueSky(const Ray& r) {
    Vector unit_direction = r.Direction();
    float a = 0.5f * (unit_direction.Y() + 1.0f);
    Color start_color = Color(1.0f, 1.0f, 1.0f);
    Color end_color = Color(0.5f, 0.7f, 1.0f);

    return start_color * (1.0f - a) + end_color * a;
}

Color purpleSky(const Ray& r) {
    Vector unit_direction = r.Direction();
    float a = 0.5f * (unit_direction.Y() + 1.0f);
    Color start_color = Color(0.9f, 0.5f, 0.3f);
    Color end_color = Color(0.2f, 0.1f, 0.4f);

    return start_color * (1.0f - a) + end_color * a;
}

Color orangeSky(const Ray& r) {
    Vector unit_direction = r.Direction();
    float a = 0.5f * (unit_direction.Y() + 1.0f);
    a = a * a;
    Color start_color = Color(1.0f, 0.5f, 0.0f);
    Color end_color = Color(0.6f, 0.1f, 0.3f);

    return start_color * (1.0f - a) + end_color * a;
}

Color greySky(const Ray& r) {
    return Color(0.7f, 0.7f, 0.7f);
}

int main()
{
    Logger logger(Logger::Level::INFO);
    RenderMetrics metrics;
    logger.Info("Starting raytracer...");

    const int image_width = 1920;
    const int image_height = 1080;
    const int samples_per_pixel = 10;

    auto material_ground = std::make_shared<CheckerMaterial>(
        Color(0.1, 0.3, 0.1),
        Color(0.9, 0.9, 0.9),
        2.0f
    );
    auto material_center = std::make_shared<Lambertian>(Color(0.94, 0.53, 0.26));
    auto material_left = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.8));
    auto material_right = std::make_shared<Lambertian>(Color(0.8, 0.6, 0.2));
    auto material_cube = std::make_shared<SideColorMaterial>(
        Color(0.9, 0.2, 0.2),
        Color(0.2, 0.2, 0.9)
    );
    auto shiny = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0f);
    auto rough = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.5f);

    Scene scene(orangeSky);
    scene.add(std::make_shared<Plane>(-0.5f, material_ground));

    scene.add(std::make_shared<Sphere>(Vector(0.0f, 0.0f, -9.0f), 0.5f, shiny));
    scene.add(std::make_shared<Sphere>(Vector(-2.0f, 0.0f, -6.0f), 0.5f, rough));
    scene.add(std::make_shared<Sphere>(Vector(1.0f, 0.0f, -5.0f), 0.5f, material_right));
    scene.add(std::make_shared<Cube>(
        Vector(-3.90f - 0.35f, -0.5f, -7.0f - 0.35f),
        Vector(-3.90f + 0.35f,  0.2f, -7.0f + 0.35f),
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