#pragma once

#include <string>
#include <memory>
#include <vector>
#include "json.hpp"
#include "../scene/Scene.hpp"
#include "../scene/Camera.hpp"

using json = nlohmann::json;

class SceneParser {
public:
    SceneParser(const std::string& filename);

    std::unique_ptr<Camera> createCamera();
    std::unique_ptr<Scene> createScene();

private:
    json data;

    Vector parseVector(const json& j) const;
    Color parseColor(const json& j) const;
    std::shared_ptr<Material> parseMaterial(const json& j) const;
    std::shared_ptr<Hittable> parseObject(const json& j) const;
    SkyFunction parseSky() const;
};