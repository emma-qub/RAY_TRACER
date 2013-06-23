#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <iostream>
#include <fstream> // ofstream
#include "Vector3.h"
#include "Sphere.h"
#include "Ray.h"
#include "Image.h"
#include "Scene.h"
#include "Camera.h"
#include "LightSource.h"
#include "PhongModel.h"
#include "Color.h"

const double PI = 3.141592;

struct SetPixelFunction {
    virtual void setPixel(unsigned int, unsigned int, const Color&) = 0;
};

class RayTracer {
public:
    enum Resolution {
        low,
        medium,
        high
    };

    Scene _scene;
    PhongModel _lightModel;
    Camera _camera;

    RayTracer(const Scene& scene, const Camera& camera, const PhongModel& lightModel = PhongModel());
    virtual ~RayTracer();
    virtual void raytrace(Image& img);
    virtual void raytrace(SetPixelFunction*);
    virtual void raytrace(Image& img, Resolution resolution);
    virtual void raytrace(SetPixelFunction* putPixel, Resolution resolution);

private:
    int NB_OF_INTERATIONS;

    virtual Color calculateColor(Ray& r, int recursions);
    virtual bool isHidden(LightSource* lightSource, Vector3& point);
};

#endif /* RAYTRACER_H_ */
