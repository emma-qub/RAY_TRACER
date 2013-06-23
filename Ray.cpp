#include "Ray.h"

Ray::Ray(const Vector3& origin, const Vector3& direction) {
    _coords[0] = origin;
    _coords[1] = direction;
}

Ray::Ray(const Ray& ray) {
    _coords[0] = ray[0];
    _coords[1] = ray[1];
}

Ray::~Ray() {
}

Vector3 Ray::getPoint(double t) const {
    return _coords[0] + (t * _coords[1]);
}


Vector3 Ray::operator[](int i) const {
    return _coords[i];
}

Vector3& Ray::operator[](const int& i) {
    return _coords[i];
}


ostream& operator<<(ostream& os, const Ray& ray) {
    return os << ray[0] << " + t*" << ray[1];
}
