#include "Scene.h"

Scene::Scene(std::vector<Shape*> shapes, std::vector<LightSource*> lightSources) {
    for (unsigned k = 0; k < shapes.size(); k++) {
        _shapes.push_back(shapes[k]->clone());
    }
    for (unsigned k = 0; k < lightSources.size(); k++) {
        _lightSources.push_back(lightSources[k]->clone());
    }
}

Scene::Scene(const Scene& scene) {
    std::vector<Shape*> shapes = scene._shapes;
    for (unsigned k = 0; k < shapes.size(); k++) {
        _shapes.push_back(shapes[k]->clone());
    }
    std::vector<LightSource*> lightSources = scene._lightSources;
    for (unsigned k = 0; k < lightSources.size(); k++) {
        _lightSources.push_back(lightSources[k]->clone());
    }
}

Scene::~Scene() {
    for (unsigned k = 0; k < _shapes.size(); k++) {
        delete _shapes[k];
    }
    for (unsigned k = 0; k < _lightSources.size(); k++) {
        delete _lightSources[k];
    }
}

void Scene::addShape(const Shape& shape) {
    _shapes.push_back(shape.clone());
}

void Scene::addLightSource(const LightSource& lightSource) {
    _lightSources.push_back(lightSource.clone());
}
