#include "Shape.h"

Shape::Shape() {
}

Shape::Shape(const Color &color, const Material &material) :
    _color(color),
    _material(material) {
}

Shape::Shape(const Shape& shape) {
    _color = shape._color;
    _material = shape._material;
}

Shape::~Shape() {
}

Color Shape::getColor(const Vector3 &ptIntersect) {
    return _color;
}
