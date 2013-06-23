#include "Triangle.h"

Triangle::Triangle(const Color& color, const Material& material, const Vector3 point1, const Vector3 point2, const Vector3 point3) :
    Shape(color, material),
    _point1(point1),
    _point2(point2),
    _point3(point3) {
}

Triangle::~Triangle() {
}

Vector3 Triangle::normal(const Vector3 &ptIntersect) const {
    return cross_product((_point2-_point1), (_point3-_point1));
}

std::vector<double> Triangle::ensIntersect(const Ray &rayon) const {
    std::vector<double> res;

    double a = _point1[0]-_point2[0], b = _point1[0]-_point3[0], c = rayon[1][0], d = _point1[0]-rayon[0][0];
    double e = _point1[1]-_point2[1], f = _point1[1]-_point3[1], g = rayon[1][1], h = _point1[1]-rayon[0][1];
    double i = _point1[2]-_point2[2], j = _point1[2]-_point3[2], k = rayon[1][2], l = _point1[2]-rayon[0][2];

    double m = f*k - g*j, n = h*k - g*l, p = f*l - h*j;
    double q = g*i - e*k, s = e*j - f*i;

    double inv_denom = 1.0/(a*m + b*q + c*s);

    double e1 = d*m - b*n - c*p;
    double beta = e1*inv_denom;

    if (beta < 0.0)
        return res;

    double r = e*l - h*i;
    double e2 = a*n + d*q + c*r;
    double gamma = e2*inv_denom;

    if (gamma < 0.0)
        return res;

    if (beta + gamma > 1.0)
        return res;

    double e3 = a*p - b*r + d*s;
    double t = e3*inv_denom;

    if (t > 0)
        res.push_back(t);

    return res;
}

bool Triangle::belongsTo(const Vector3 &ptIntersect) const {
    return false;
}

Triangle* Triangle::clone() const {
    return new Triangle(*this);
}

std::ostream& operator<<(std::ostream& os, const Triangle& triangle) {
    return os << triangle._point1 << std::endl
              << triangle._point2 << std::endl
              << triangle._point3 << std::endl;
}
