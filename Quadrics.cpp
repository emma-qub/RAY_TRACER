#include "Quadrics.h"
#include "Rectangle.h"

#include <algorithm>

Quadrics::Quadrics(const Color &color, const Material &material,
                   double a, double b, double c,
                   double d, double e, double f,
                   double g, double h, double i, double j) :
    Shape(color, material),
    _a(a), _b(b), _c(c),
    _d(d), _e(e), _f(f),
    _g(g), _h(h), _i(i), _j(j) {
}

Quadrics::~Quadrics() {
}

Vector3 Quadrics::normal(const Vector3& ptIntersect) const {
    double x0 = ptIntersect[0];
    double y0 = ptIntersect[1];
    double z0 = ptIntersect[2];
    return Vector3(2.0*_a*x0 + 2.0*_d*y0 + 2.0*_e*z0 + _g,
                   2.0*_b*y0 + 2.0*_d*x0 + 2.0*_f*z0 + _h,
                   2.0*_c*z0 + 2.0*_e*x0 + 2.0*_f*y0 + _i
           );
}

std::vector<double> Quadrics::ensIntersect(const Ray& rayon) const {

    std::vector<double> res;
/*
    double edge = 20;

    Rectangle r1(Color(), Material(), Ray(Vector3(10, 0, 0), Vector3(1, 0, 0)), edge, edge);
    Rectangle r2(Color(), Material(), Ray(Vector3(-10, 0, 0), Vector3(1, 0, 0)), edge, edge);
    Rectangle r3(Color(), Material(), Ray(Vector3(0, 10, 0), Vector3(0, 1, 0)), edge, edge);
    Rectangle r4(Color(), Material(), Ray(Vector3(0, -10, 0), Vector3(0, 1, 0)), edge, edge);
    Rectangle r5(Color(), Material(), Ray(Vector3(0, 0, 10), Vector3(0, 0, 1)), edge, edge);
    Rectangle r6(Color(), Material(), Ray(Vector3(0, 0, -10), Vector3(0, 0, 1)), edge, edge);

    if (r1.ensIntersect(rayon).size() <= 0
     && r2.ensIntersect(rayon).size() <= 0
     && r3.ensIntersect(rayon).size() <= 0
     && r4.ensIntersect(rayon).size() <= 0
     && r5.ensIntersect(rayon).size() <= 0
     && r6.ensIntersect(rayon).size() <= 0
    ) {
        return res;
    }
*/

    double ox = rayon[0][0];
    double oy = rayon[0][1];
    double oz = rayon[0][2];
    double dx = rayon[1][0];
    double dy = rayon[1][1];
    double dz = rayon[1][2];

    double alpha = _a*dx*dx + _b*dy*dy + _c*dz*dz
                 + 2*_d*dx*dy + 2*_e*dx*dz + 2*_f*dy*dz;
    double beta = 2*_a*ox*dx + 2*_b*oy*dy + 2*_c*oz*dz
                + 2*_d*(ox*dy+oy*dx) + 2*_e*(ox*dz+oz*dx) + 2*_f*(oy*dz+oz*dy)
                + _g*dx + _h*dy + _i*dz;
    double gamma = _a*ox*ox + _b*oy*oy + _c*oz*oz
                + 2*_d*ox*oy + 2*_e*ox*oz + 2*_f*oy*oz
                + _g*ox + _h*oy + _i*oz + _j;
    double delta = beta*beta - 4*alpha*gamma;

    delta = sqrt(delta);
    if (delta == 0 && -beta / (2 * alpha) > 0) {
        res.push_back(-beta / (2 * alpha));
    } else if (delta > 0) {
        double t1 = (-beta - delta) / (2 * alpha);
        double t2 = (-beta + delta) / (2 * alpha);
        if (t1 > 0)
            res.push_back(t1);
        if (t2 > 0)
            res.push_back(t2);
    }

    sort(res.begin(), res.end());
    return res;
}

bool Quadrics::belongsTo(const Vector3& ptIntersect) const {
    double x0 = ptIntersect[0];
    double y0 = ptIntersect[1];
    double z0 = ptIntersect[2];
    return abs(_a * x0 * x0
             + _b * y0 * y0
             + _c * z0 * z0
             + 2 * _d * x0 * y0
             + 2 * _e * x0 * z0
             + 2 * _f * y0 * z0
             + _g * x0
             + _h * y0
             + _i * z0
             + _j
           ) < 0.001;
}

Quadrics* Quadrics::clone() const {
    return new Quadrics(*this);
}
