#ifndef CYLINDRE_H_
#define CYLINDRE_H_

#include "Quadrics.h"

#include <cmath>

class Cylindre : public Shape {
public:
    double _radius;
    Vector3 _bottomCenter;
    //Vector3 _topCenter;
    double _length;

    Cylindre(const Color& color, const Material& material,
             const Vector3& bottomCenter = Vector3(0,0,0),
             double length = 3.0, double radius = 1.0);
    virtual ~Cylindre();

    virtual std::vector<double> ensIntersect(const Ray &rayon) const;
    virtual Vector3 normal(const Vector3 &ptIntersect) const;
    virtual bool belongsTo(const Vector3 &ptIntersect) const;

    virtual Cylindre* clone() const;

    friend std::ostream& operator<<(std::ostream& os, const Cylindre& cylindre);
};

#endif /* CYLINDRE_H_ */
