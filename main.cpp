#include "image/Image.hpp"
#include "scene/Camera.hpp"
#include "scene/Scene.hpp"
#include "shapes/Sphere.hpp"
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

    Scene scene;
    scene.add(std::make_shared<Sphere>(Vector(0.0f, 0.0f, -1.0f), 0.5f));
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