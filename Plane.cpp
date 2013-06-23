#include "Plane.h"
#include <cmath>

Plane::Plane(const Color& color, const Material& material, const Ray& normAndPoint) :
    Shape(color, material),
    _normAndPoint(normAndPoint) {

    //Calculate the d constant in the plane equation P:ax+by+cz=d
    _d = _normAndPoint[0][0] * _normAndPoint[1][0]
            + _normAndPoint[0][1] * _normAndPoint[1][1]
            + _normAndPoint[0][2] * _normAndPoint[1][2];
}

Plane::~Plane() {
}

std::vector<double> Plane::ensIntersect(const Ray& rayon) const {
    std::vector<double> res;
    double t = (_d - _normAndPoint[1][0]*rayon[0][0] - _normAndPoint[1][1]*rayon[0][1] - _normAndPoint[1][2]*rayon[0][2])
              /(_normAndPoint[1][0]*rayon[1][0] + _normAndPoint[1][1]*rayon[1][1] + _normAndPoint[1][2]*rayon[1][2]);

    if (t > 0) {
        res.push_back(t);
    }

    return res;
}

Vector3 Plane::normal(const Vector3& ptIntersect) const {
    return _normAndPoint[1];
}

bool Plane::belongsTo(const Vector3& ptIntersect) const {
    return abs(_d + ptIntersect[0] * _normAndPoint[1][0]
                  + ptIntersect[1] * _normAndPoint[1][1]
                  + ptIntersect[2] * _normAndPoint[1][2]
           ) < 10e-9;
}

Plane* Plane::clone() const {
    return new Plane(*this);
}

std::ostream& operator<<(std::ostream& os, const Plane& plane) {
    return os << plane._color << std::endl
              << plane._material << std::endl
              << plane._normAndPoint;
}
