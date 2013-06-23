#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>

#include "Shape.h"

class Triangle : public Shape {
public:
    Vector3 _point1, _point2, _point3;

    Triangle(const Color& color, const Material& material, const Vector3 point1 = Vector3(0,0,0), const Vector3 point2 = Vector3(0,0,1), const Vector3 point3 = Vector3(1,0,0));
    virtual ~Triangle();

    virtual Vector3 normal(const Vector3 &ptIntersect) const;
    virtual std::vector<double> ensIntersect(const Ray &rayon) const;
    virtual bool belongsTo(const Vector3 &ptIntersect) const;

    virtual Triangle* clone() const;

    friend std::ostream& operator<<(std::ostream& os, const Triangle& triangle);
};

#endif // TRIANGLE_H
