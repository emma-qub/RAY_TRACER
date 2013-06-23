#ifndef BOX_H
#define BOX_H

#include "Rectangle.h"
#include <vector>

class Box: public Shape {

public:
    std::vector<Rectangle> _faces;
    Vector3 _bottomLeftFrontCorner;
    Vector3 _topRightBackCorner;

    class NotABox: public std::exception {
    public:
        const char* what() const throw() {
            return "Syntax error";
        }
    };

    Box(const Color& color, const Material& material, const Vector3& bottomLeftFrontCorner, const Vector3& topRightBackCorner);
    Box(const Box& box);
    virtual ~Box();

    virtual Vector3 normal(const Vector3& ptIntersect) const;
    virtual std::vector<double> ensIntersect(const Ray& rayon) const;
    virtual bool belongsTo(const Vector3& ptIntersect) const;

    virtual Shape* clone() const;
};

#endif // BOX_H
