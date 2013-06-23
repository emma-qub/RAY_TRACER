#ifndef SHAPE_H_
#define SHAPE_H_

#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include "Material.h"
#include <vector>

class Shape {
public:
    Color _color;
    Material _material;

    Shape();
    Shape(const Color& color, const Material& material);
    Shape(const Shape& shape);
    virtual ~Shape();

    virtual Vector3 normal(const Vector3& ptIntersect) const = 0;
    virtual std::vector<double> ensIntersect(const Ray& rayon) const = 0;
    virtual Color getColor(const Vector3& ptIntersect);
    virtual bool belongsTo(const Vector3& ptIntersect) const = 0;

    virtual Shape* clone() const = 0;
};

#endif /* SHAPE_H_ */
