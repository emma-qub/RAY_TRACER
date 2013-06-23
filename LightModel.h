#ifndef LIGHTMODEL_H_
#define LIGHTMODEL_H_

#include "Ray.h"
#include "LightSource.h"
#include "Material.h"

class LightModel {
public:
    LightModel();
    virtual ~LightModel();

    virtual double getAmbient(Material& material) const;
    virtual double getDiffuse(Ray& normal, LightSource* source, Material& material) const;
    virtual double getSpecular(Ray& refracted, LightSource* source, Material& material) const;
};

#endif /* LIGHTMODEL_H_ */
