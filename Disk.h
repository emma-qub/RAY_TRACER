#ifndef DISK_H
#define DISK_H

#include "Plane.h"

class Disk : public Plane {
public:
    double _radius;

    Disk(const Color& color, const Material& material, const Ray& normAndPoint, double radius);
    virtual ~Disk();

    virtual std::vector<double> ensIntersect(const Ray &rayon) const;
    virtual bool belongsTo(const Vector3& ptIntersect) const;
    virtual Disk* clone() const;

    friend std::ostream& operator<<(std::ostream& os, const Disk& disk);
};

#endif // DISK_H
