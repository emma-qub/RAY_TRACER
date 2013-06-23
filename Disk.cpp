#include "Disk.h"

Disk::Disk(const Color &color, const Material &material, const Ray &normAndPoint, double radius) :
    Plane(color, material, normAndPoint),
    _radius(radius) {
}

Disk::~Disk() {
}

std::vector<double> Disk::ensIntersect(const Ray &rayon) const {
    std::vector<double> res;

    Vector3 direction = _normAndPoint[1];
    Vector3 origin = _normAndPoint[0];

    double t = (_d - direction[0]*rayon[0][0] - direction[1]*rayon[0][1] - direction[2]*rayon[0][2])
              /(direction[0]*rayon[1][0] + direction[1]*rayon[1][1] + direction[2]*rayon[1][2]);

    Vector3 inter = rayon.getPoint(t);

    if (t > 0 &&  ((inter[0]-origin[0])*(inter[0]-origin[0])+(inter[1]-origin[1])*(inter[1]-origin[1])+(inter[2]-origin[2])*(inter[2]-origin[2])) < _radius*_radius)
        res.push_back(t);

    return res;
}

bool Disk::belongsTo(const Vector3& ptIntersect) const {
    Vector3 direction = _normAndPoint[1];
    Vector3 origin = _normAndPoint[0];

    if (((ptIntersect[0]-origin[0])*(ptIntersect[0]-origin[0])+(ptIntersect[1]-origin[1])*(ptIntersect[1]-origin[1])+(ptIntersect[2]-origin[2])*(ptIntersect[2]-origin[2])) < _radius*_radius)
        return true;

    return false;
}

Disk* Disk::clone() const {
    return new Disk(*this);
}

std::ostream& operator<<(std::ostream& os, const Disk& disk) {
    return os << disk._color << std::endl
              << disk._material << std::endl
              << disk._normAndPoint << std::endl
              << disk._radius;
}
