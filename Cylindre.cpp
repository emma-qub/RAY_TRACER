#include "Cylindre.h"

//Cylindre::Cylindre(const Color& color, const Material& material,
//                   const Vector3& bottomCenter, const Vector3& topCenter, double radius) :

//    Quadrics(color, material,
//        Vector3(topCenter - bottomCenter)[1]*Vector3(topCenter - bottomCenter)[1] + Vector3(topCenter - bottomCenter)[2]*Vector3(topCenter - bottomCenter)[2],
//        Vector3(topCenter - bottomCenter)[0]*Vector3(topCenter - bottomCenter)[0] + Vector3(topCenter - bottomCenter)[2]*Vector3(topCenter - bottomCenter)[2],
//        Vector3(topCenter - bottomCenter)[0]*Vector3(topCenter - bottomCenter)[0] + Vector3(topCenter - bottomCenter)[1]*Vector3(topCenter - bottomCenter)[1],
//        2*Vector3(topCenter - bottomCenter)[0]*Vector3(topCenter - bottomCenter)[1],
//        2*Vector3(topCenter - bottomCenter)[0]*Vector3(topCenter - bottomCenter)[2],
//        2*Vector3(topCenter - bottomCenter)[1]*Vector3(topCenter - bottomCenter)[2],
//        0, 0, 0, -radius*radius),
//    _bottomCenter(bottomCenter),
//    _topCenter(topCenter),
//    _radius(radius) {
//}


Cylindre::Cylindre(const Color& color, const Material& material,
                   const Vector3& bottomCenter, double length, double radius) :
    Shape(color, material),
    _bottomCenter(bottomCenter),
    _length(length),
    _radius(radius) {
}

Cylindre::~Cylindre() {
}

std::vector<double> Cylindre::ensIntersect(const Ray &rayon) const {
    std::vector<double> res;

    double ox = rayon[0][0], oz = rayon[0][2];
    double dx = rayon[1][0], dz = rayon[1][2];

    double a = dx*dx + dz*dz;
    double b = 2*(ox*dx + oz*dz);
    double c = ox*ox + oz*oz - _radius*_radius;


    double delta = b*b - 4.0*a*c;

    if (delta > 0) {
        double t1 = (-b - sqrt(delta)) / (2*a);
        double t2 = (-b + sqrt(delta)) / (2*a);
        double tmin = std::min(t1, t2);
        double tmax = std::max(t1, t2);

        Vector3 pointMin = rayon.getPoint(tmin);
        Vector3 pointMax = rayon.getPoint(tmax);

        if (tmin > 0 && pointMin[1] > _bottomCenter[1] && pointMin[1] < (_bottomCenter[1]+_length))
            res.push_back(tmin);
        if (tmax > 0 && pointMax[1] > _bottomCenter[1] && pointMax[1] < (_bottomCenter[1]+_length))
            res.push_back(tmax);
    } else if (delta == 0) {
        double t = -b / (2*a);
        Vector3 point = rayon.getPoint(t);

        if (t > 0 && point[1] > _bottomCenter[1] && point[1] < _bottomCenter[1]+_length)
            res.push_back(t);
    }

    return res;
}

Vector3 Cylindre::normal(const Vector3 &ptIntersect) const {
    return Vector3(ptIntersect[0]/_radius, 0, ptIntersect[2]/_radius);
}

bool Cylindre::belongsTo(const Vector3 &ptIntersect) const {
    return false;
}

Cylindre* Cylindre::clone() const {
    return new Cylindre(*this);
}

std::ostream& operator<<(std::ostream& os, const Cylindre& cylindre) {

}
