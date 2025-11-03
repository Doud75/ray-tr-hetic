#include "raymath/Color.hpp"
#include "image/Image.hpp"
#include "utils/RenderMetrics.hpp"
#include "utils/Logger.hpp"
#include <fstream>

int main()
{
    Logger logger(Logger::Level::INFO);
    RenderMetrics metrics;
    
    logger.Info("Starting raytracer...");

    const int image_width = 512;
    const int image_height = 512;

    metrics.StartRender(image_width, image_height);

    Image image(image_width, image_height);
    
    size_t bufferSize = image_width * image_height * sizeof(Color);
    metrics.RecordImageBufferSize(bufferSize);

    metrics.StartRenderingLoop();

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            metrics.StartPixelComputation();
            
            auto r = static_cast<float>(i) / (image_width - 1);
            auto g = static_cast<float>(j) / (image_height - 1);
            auto b = 0.2f;

            image.SetPixel(i, j, Color(r, g, b));
            
            metrics.StopPixelComputation();
        }
    }

    metrics.StopRenderingLoop();

    const char* filename = "output_gradient.png";
    
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