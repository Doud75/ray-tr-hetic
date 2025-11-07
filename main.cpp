#include "image/Image.hpp"
#include "scene/Camera.hpp"
#include "scene/Scene.hpp"
#include "utils/RenderMetrics.hpp"
#include "utils/Logger.hpp"
#include "utils/SceneParser.hpp"
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <filesystem>
#include <limits>

Color blueSky(const Ray& r) {
    Vector unit_direction = r.Direction();
    float a = 0.5f * (unit_direction.Y() + 1.0f);
    return Color(1.0f, 1.0f, 1.0f) * (1.0f - a) + Color(0.5f, 0.7f, 1.0f) * a;
}

Color purpleSky(const Ray& r) {
    Vector unit_direction = r.Direction();
    float a = 0.5f * (unit_direction.Y() + 1.0f);
    return Color(0.9f, 0.5f, 0.3f) * (1.0f - a) + Color(0.2f, 0.1f, 0.4f) * a;
}

Color orangeSky(const Ray& r) {
    Vector unit_direction = r.Direction();
    float a = 0.5f * (unit_direction.Y() + 1.0f);
    a = a * a;
    return Color(1.0f, 0.5f, 0.0f) * (1.0f - a) + Color(0.6f, 0.1f, 0.3f) * a;
}

Color greySky(const Ray& r) {
    return Color(0.7f, 0.7f, 0.7f);
}


std::string selectSceneInteractively() {
    std::string scenes_dir = "scene_json";
    std::vector<std::string> scene_files;

    std::cout << "Available scenes:" << std::endl;
    int i = 0;
    for (const auto & entry : std::filesystem::directory_iterator(scenes_dir)) {
        if (entry.path().extension() == ".json") {
            std::cout << "  " << i + 1 << ". " << entry.path().filename().string() << std::endl;
            scene_files.push_back(entry.path().string());
            i++;
        }
    }

    if (scene_files.empty()) {
        std::cerr << "No scenes found in 'scenes/' directory." << std::endl;
        return "";
    }

    int choice = -1;
    while (true) {
        std::cout << "Enter your choice (1-" << scene_files.size() << "): ";
        std::cin >> choice;
        if (std::cin.good() && choice >= 1 && choice <= scene_files.size()) {
            return scene_files[choice - 1];
        }
        std::cout << "Invalid input. Please try again." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


int main(int argc, char* argv[])
{
    Logger logger(Logger::Level::INFO);
    RenderMetrics metrics;

    std::string scene_file;

    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "--interactive") {
            scene_file = selectSceneInteractively();
            if (scene_file.empty()) return 1;
        } else {
            scene_file = arg;
        }
    } else {
        scene_file = "scene_json/default.json";
        logger.Info("No scene file specified. Loading default scene: " + scene_file);
    }

    logger.Info("Loading scene from: " + scene_file);

    try {
        SceneParser parser(scene_file);

        auto cam = parser.createCamera();
        auto scene = parser.createScene();

        const int image_width = cam->image_width;
        const int image_height = cam->image_height;

        Image image(image_width, image_height);

        logger.Info("Starting raytracer...");
        metrics.StartRender(image_width, image_height);

        size_t bufferSize = image_width * image_height * sizeof(Color);
        metrics.RecordImageBufferSize(bufferSize);

        metrics.StartRenderingLoop();
        cam->render(*scene, image);
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

    } catch (const std::exception& e) {
        logger.Error("An error occurred: " + std::string(e.what()));
        return 1;
    }

    return 0;
}