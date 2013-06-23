#include "Torus.h"
#include "Solver.h"

#include <algorithm>

Torus::Torus(const Color& color, const Material& material, double ringRadius, double crossRadius) :
    Shape(color, material),
    _ringRadius(ringRadius),
    _crossRadius(crossRadius) {
}

Torus::~Torus() {
}


std::vector<double> Torus::ensIntersect(const Ray &rayon) const {
    std::vector<double> res;
    std::vector<double> resFake;

    Ray rayonTest(Vector3(-11, 0, -11), Vector3(1, 0, 1));

    double a = _ringRadius;
    double b = _crossRadius;

    double ox = rayonTest[0][0], oy = rayon[0][1], oz = rayon[0][2];
    double dx = rayonTest[1][0], dy = rayon[1][1], dz = rayon[1][2];

    double sumDSqrd  = dx*dx+dy*dy+dz*dz;
    double sumOSqrd  = ox*ox+oy*oy+oz*oz;
    double e         = sumOSqrd - a*a - b*b;
    double f         = ox*dx+oy*dy+oz*dz;
    double fourASqrd = 4.0*a*a;

    double coeffs[5];
    double roots[4];

    coeffs[0] = e*e - fourASqrd*(b*b - oy*oy);
    coeffs[1] = 4.0*f*e + 2.0*fourASqrd*oy*dy;
    coeffs[2] = 2.0*sumDSqrd*e + 4.0*f*f + fourASqrd*dy*dy;
    coeffs[3] = 4.0*sumDSqrd*f;
    coeffs[4] = sumDSqrd*sumDSqrd;

    int nbSol = Solver::SolveQuartic(coeffs, roots);

    for (int k = 0; k < nbSol; k++) {
        double t = roots[k];
        if (t > 0)
            res.push_back(t);
    }

    sort(res.begin(), res.end());

    std::cerr << "a=" << a << std::endl;
    std::cerr << "b=" << b << std::endl;
    std::cerr << coeffs[0] << std::endl;
    std::cerr << coeffs[1] << std::endl;
    std::cerr << coeffs[2] << std::endl;
    std::cerr << coeffs[3] << std::endl;
    std::cerr << coeffs[4] << std::endl;
    std::cerr << nbSol << std::endl;
        for (int k = 0; k < nbSol; k++)
            std::cerr << res.at(k) << std::endl;

    return resFake;
}

Vector3 Torus::normal(const Vector3 &ptIntersect) const {
    double x = ptIntersect[0], y = ptIntersect[1], z = ptIntersect[2];
    double a = _ringRadius, b = _crossRadius;
    double c = x*x+y*y+z*z - (a*a+b*b);

    Vector3 normal(4*x*c, 4*y*(c+2*a*a), 4*z*c);
    normal = normal.normalized();

    return normal;
}

bool Torus::belongsTo(const Vector3 &ptIntersect) const {
    return false;
}

Torus* Torus::clone() const {
    return new Torus(*this);
}

std::ostream& operator<<(std::ostream& os, const Torus& torus);
