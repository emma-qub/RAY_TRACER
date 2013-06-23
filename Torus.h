#ifndef TORUS_H
#define TORUS_H

#include "Shape.h"

#include <cmath>

class Torus : public Shape {
public:
    double _ringRadius;
    double _crossRadius;

    Torus(const Color& color, const Material& material, double ringRadius, double crossRadius);
    virtual ~Torus();


    virtual std::vector<double> ensIntersect(const Ray &rayon) const;
    virtual Vector3 normal(const Vector3 &ptIntersect) const;
    virtual bool belongsTo(const Vector3 &ptIntersect) const;

    virtual Torus* clone() const;

    friend std::ostream& operator<<(std::ostream& os, const Torus& torus);
};

#endif // TORUS_H
