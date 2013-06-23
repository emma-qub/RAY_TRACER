#ifndef PLANE_H_
#define PLANE_H_

#include <iostream>

#include "Shape.h"

class Plane : public Shape {
public:
    Ray _normAndPoint;
    double _d;

    Plane(const Color &color, const Material &material, const Ray &normAndPoint);
    virtual ~Plane();

    virtual Vector3 normal(const Vector3 &ptIntersect) const;
    virtual std::vector<double> ensIntersect(const Ray &rayon) const;
    virtual bool belongsTo(const Vector3 &ptIntersect) const;

    virtual Plane* clone() const;

    friend std::ostream& operator<<(std::ostream& os, const Plane& plane);
};

#endif /* PLANE_H_ */
