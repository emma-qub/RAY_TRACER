#include "Sphere.h"
#include <cmath>

Sphere::Sphere(const Color& color, const Material& material, const Vector3& center, double radius) :
    Shape(color, material),
    _center(center),
    _radius(radius) {
}

Sphere::~Sphere() {
}

Vector3 Sphere::normal(const Vector3 &ptIntersect) const {
    return (ptIntersect - _center);
}

std::vector<double> Sphere::ensIntersect(const Ray &rayon) const {
    std::vector<double> s;
    Vector3 d_o_x = dot_product(rayon[1], (rayon[0] - _center));
    Vector3 o_c = dot_product(rayon[0], _center);

    double a = rayon[1].norm() * rayon[1].norm();
    double b = 2 * (d_o_x[0] + d_o_x[1] + d_o_x[2]);
    double c = pow(_center.norm(), 2) + pow(rayon[0].norm(), 2) - 2 * (o_c[0] + o_c[1] + o_c[2]) - _radius * _radius;

    //Apply solve function (-b +- sqrt(b^2-4ac))/2a
    double d = b * b - 4 * a * c; //the term in the root

    if (d > 0) { //We have an intersection
        double t1 = (-b - sqrt(d)) / (2 * a);
        double t2 = (-b + sqrt(d)) / (2 * a);
        if (t1 < t2) {
            if (t1 > 0) {
                s.push_back(t1);
                s.push_back(t2);
            }
        } else if (t2 > 0) {
            s.push_back(t2);
        }
    }
    return s;
}

bool Sphere::belongsTo(const Vector3 &ptIntersect) const {
    return fabs(sqrt((ptIntersect[0] - _center[0])*(ptIntersect[0] - _center[0])
                   + (ptIntersect[1] - _center[1])*(ptIntersect[1] - _center[1])
                   + (ptIntersect[2] - _center[2])*(ptIntersect[2] - _center[2])) - _radius
           ) < 0.001;
}

Sphere* Sphere::clone() const {
    return new Sphere(*this);
}

std::ostream& operator<<(std::ostream& os, const Sphere& sphere) {
    return os << sphere._color << std::endl
              << sphere._material << std::endl
              << sphere._center << std::endl
              << sphere._radius;
}
