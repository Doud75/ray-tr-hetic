#include "SceneParser.hpp"
#include <fstream>
#include <stdexcept>
#include "Vector.hpp"
#include "Color.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Cube.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"
#include "CheckerBoard.hpp"
#include "SideColorMaterial.hpp"

Color blueSky(const Ray& r);
Color purpleSky(const Ray& r);
Color orangeSky(const Ray& r);
Color greySky(const Ray& r);

SceneParser::SceneParser(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) {
        throw std::runtime_error("SceneParser: Could not open file: " + filename);
    }
    data = json::parse(f);
}

std::unique_ptr<Camera> SceneParser::createCamera() {
    const auto& cam_data = data["camera"];
    int width = cam_data.value("width", 800);
    int height = cam_data.value("height", 600);
    int samples = cam_data.value("samples_per_pixel", 10);
    float fov = cam_data.value("vertical_fov", 90.0f);

    return std::make_unique<Camera>(width, height, samples, fov);
}

std::unique_ptr<Scene> SceneParser::createScene() {
    SkyFunction sky = parseSky();
    auto scene = std::make_unique<Scene>(sky);

    for (const auto& obj_json : data["objects"]) {
        scene->add(parseObject(obj_json));
    }

    return scene;
}

Vector SceneParser::parseVector(const json& j) const {
    return Vector(j[0].get<float>(), j[1].get<float>(), j[2].get<float>());
}

Color SceneParser::parseColor(const json& j) const {
    return Color(j[0].get<float>(), j[1].get<float>(), j[2].get<float>());
}

SkyFunction SceneParser::parseSky() const {
    std::string type = data["sky"].value("type", "blue");
    if (type == "purple") return purpleSky;
    if (type == "orange") return orangeSky;
    if (type == "grey") return greySky;
    return blueSky;
}

std::shared_ptr<Hittable> SceneParser::parseObject(const json& j) const {
    std::string type = j.at("type").get<std::string>();
    auto material = parseMaterial(j.at("material"));
    const auto& props = j.at("properties");

    if (type == "sphere") {
        Vector center = parseVector(props.at("center"));
        float radius = props.at("radius").get<float>();
        return std::make_shared<Sphere>(center, radius, material);
    }
    if (type == "plane") {
        float y_pos = props.at("y_position").get<float>();
        return std::make_shared<Plane>(y_pos, material);
    }
    if (type == "cube") {
        Vector min_c = parseVector(props.at("min_corner"));
        Vector max_c = parseVector(props.at("max_corner"));
        return std::make_shared<Cube>(min_c, max_c, material);
    }

    throw std::runtime_error("Unknown object type: " + type);
}

std::shared_ptr<Material> SceneParser::parseMaterial(const json& j) const {
    std::string type = j.at("type").get<std::string>();
    const auto& props = j.at("properties");

    if (type == "lambertian") {
        return std::make_shared<Lambertian>(parseColor(props.at("albedo")));
    }
    if (type == "metal") {
        return std::make_shared<Metal>(parseColor(props.at("albedo")), props.at("fuzz").get<float>());
    }
    if (type == "checkerboard") {
        return std::make_shared<CheckerMaterial>(
            parseColor(props.at("color1")),
            parseColor(props.at("color2")),
            props.value("scale", 10.0f)
        );
    }
    if (type == "sidecolor") {
        return std::make_shared<SideColorMaterial>(
            parseColor(props.at("front_back_color")),
            parseColor(props.at("other_faces_color"))
        );
    }

    throw std::runtime_error("Unknown material type: " + type);
}