#ifndef QUADRICS_H_
#define QUADRICS_H_

#include "Shape.h"
#include <cmath>

class Quadrics: public Shape {

public:
    double _a, _b, _c, _d, _e, _f, _g, _h, _i, _j;

    Quadrics(const Color& color = Color(), const Material& material = Material(),
             double a = 0.0, double b = 0.0, double c = 0.0,
             double d = 0.0, double e = 0.0, double f = 0.0,
             double g = 0.0, double h = 0.0, double i = 0.0, double j = 0.0);
    virtual ~Quadrics();

    virtual Vector3 normal(const Vector3& ptIntersect) const;
    virtual std::vector<double> ensIntersect(const Ray& rayon) const;
    virtual bool belongsTo(const Vector3& ptIntersect) const;

    virtual Quadrics* clone() const;
};

#endif /* QUADRICS_H_ */
