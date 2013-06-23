#ifndef SPHERE_H_
#define SPHERE_H_

#include <iostream>

#include "Shape.h"
#include "Material.h"

class Sphere : public Shape {
public:
    Vector3 _center;
    double _radius;

    Sphere (const Color &color = 0, const Material &material = 0, const Vector3 &center = 0, double radius = 0);
    virtual ~Sphere();

    virtual std::vector<double> ensIntersect(const Ray &rayon) const;
    virtual Vector3 normal(const Vector3 &ptIntersect) const;
    virtual bool belongsTo(const Vector3 &ptIntersect) const;

    virtual Sphere* clone() const;

    friend std::ostream& operator<<(std::ostream& os, const Sphere& sphere);
};

#endif /* SPHERE_H_ */
