#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <iostream>

#include "Plane.h"

class Rectangle : public Plane {
public:
    double _height;
    double _width;

    Rectangle(const Color &color, const Material &material, const Ray &normAndPoint, double height, double width);
    virtual ~Rectangle();

    virtual std::vector<double> ensIntersect(const Ray &rayon) const;
    virtual bool belongsTo(const Vector3& ptIntersect) const;
    virtual Rectangle* clone() const;

    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle);
};

#endif /* RECTANGLE_H_ */
