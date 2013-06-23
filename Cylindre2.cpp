#include "Cylindre.h"

#include <cmath>

Cylindre::Cylindre(const Color& color, const Material& material,
                   const Vector3& bottomCenter, const Vector3& topCenter, double radius) :
    Shape(color, material),
    _bottomCenter(bottomCenter),
    _topCenter(topCenter),
    _radius(radius) {

    init();
}

Cylindre::~Cylindre() {
}

void Cylindre::init() {
    Vector3 translation(_bottomCenter);
    Vector3 Oy(0, 1, 0);
    double theta = atan2((cross_product(translation, Oy)).norm(), dot_product(translation, Oy));

    _cylindre = Quadrics(_color, _material,
                         1, 0, 1,
                         0, 0, 0,
                         2*(cos(theta)*translation[0] - sin(theta)*translation[2]), 0, 2*(sin(theta)*translation[0] + cos(theta)*translation[2]),
                         - _radius*_radius + translation[0]*translation[0] + translation[2]*translation[2]
                );
}


Vector3 Cylindre::normal(const Vector3& ptIntersect) const {
    return _cylindre.normal(ptIntersect);
}

std::vector<double> Cylindre::ensIntersect(const Ray& rayon) const {
    return _cylindre.ensIntersect(rayon);
}

bool Cylindre::belongsTo(const Vector3& ptIntersect) const {
    return _cylindre.belongsTo(ptIntersect);
}

Cylindre* Cylindre::clone() const {
    return new Cylindre(*this);
}
