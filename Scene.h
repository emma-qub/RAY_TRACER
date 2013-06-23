#ifndef SCENE_H_
#define SCENE_H_

#include "LightSource.h"
#include "Shape.h"
#include "Color.h"
#include <vector>

class Scene {
public:
    std::vector<LightSource*> _lightSources;
    std::vector<Shape*> _shapes;
    Color L_a;

    Scene(std::vector<Shape*> shapes = std::vector<Shape*>(0),
          std::vector<LightSource*> lightSources = std::vector<LightSource*>(0));
    Scene(const Scene& scene);
    virtual ~Scene();

    void addShape(const Shape& shape);
    void addLightSource(const LightSource& lightSource);

};

#endif /* SCENE_H_ */
