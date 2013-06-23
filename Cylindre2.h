#ifndef CYLINDRE_H_
#define CYLINDRE_H_

#include "Quadrics.h"

#include <cmath>

class Cylindre : public Shape {

public:
        double _radius;
        Vector3 _bottomCenter;
        Vector3 _topCenter;
        Quadrics _cylindre;

        Cylindre(const Color& color, const Material& material,
                 const Vector3& bottomCenter, const Vector3& topCenter,
                 double radius = 1);
        virtual ~Cylindre();

        void init();

        virtual Vector3 normal(const Vector3& ptIntersect) const;
        virtual std::vector<double> ensIntersect(const Ray& rayon) const;
        virtual bool belongsTo(const Vector3& ptIntersect) const;

        virtual Cylindre* clone() const;
};

#endif /* CYLINDRE_H_ */
