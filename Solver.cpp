#include "Solver.h"

#include <algorithm>
#include <iostream>

using namespace std;

Solver::Solver() {
}

Solver::~Solver() {
}

vector<double> Solver::solve2degree(double a, double b, double c) {
    vector<double> res;

    double delta = b*b - 4.0*a*c;

    if (delta > 0) {
        res.push_back((-b - sqrt(delta)) / (2*a));
        res.push_back((-b + sqrt(delta)) / (2*a));
    } else if (delta == 0) {
        res.push_back(-b / (2*a));
        //res.push_back(-b / (2*a));
    } else {
        //res.push_back(cpx(-b / (2*a), -sqrt(delta) / (2*a)));
        //res.push_back(cpx(-b / (2*a), sqrt(delta) / (2*a)));
    }

    sort(res.begin(), res.end());

    return res;
}

vector<double> Solver::solve3degree(double a, double b, double c, double d) {
    vector<double> res;

    //cpx j(-1/2, sqrt(3)/2);
    //cpx j2(-1/2, -sqrt(3)/2);

    if (d == 0.0) {
        res = solve2degree(a, b, c);
        res.push_back(0.0);
    } else {
        double p = (-b*b)/(3*a*a) + c/a;
        double q = (b/(27*a))*((2*b*b)/(a*a) - (9*c)/(a)) + d/a;

        double delta = pow(q, 2) + (4*pow(p, 3))/27;
        if (abs(delta) < 10e-6)
            delta = 0;

        if (delta > 0) {
            double u = pow(((-q - sqrt(delta))/2), (1/3));
            double v = pow(((-q + sqrt(delta))/2), (1/3));
            res.push_back(u + v - b/(3*a));
            //res.push_back(j*u + conj(j)*v);
            //res.push_back(j2*u + conj(j2)*v);
        } else if (delta == 0) {
            if (p == 0 && q == 0) {
                res.push_back(-b/(3*a));
            } else {
                res.push_back((3*q)/p - b/(3*a));
                res.push_back((-3*q)/(2*p) - b/(3*a));
                //res.push_back((-3*q)/(2*p) - b/(3*a));
            }
        } else if (delta < 0) {
            for (int k = 0; k < 3; k++) {
                res.push_back(2*sqrt(-p/3)*cos(acos((-q/2)*sqrt(27/(-p*p*p)))/3 + (2*k*M_PI)/3) - b/(3*a));
            }
        }
    }

    sort(res.begin(), res.end());

    return res;
}

vector<double> Solver::solve4degree(double a, double b, double c, double d, double e) {

    vector<double> res;

    e /= a;
    d /= a;
    c /= a;
    b /= a;
    a = 1.0;

    if (e == 0) {
        res = solve3degree(a, b, c, d);
        res.push_back(0.0);
    } else {
        double delta = 0.0, delta2 = 0.0, delta3 = 0.0, z0 = 0.0;

        double b2 = (3.0*b*b/8.0 - c)/2.0;
        double b1 = 3.0*b*b*b*b/256.0 - b*b*c/16.0 + b*d/4.0 - e;
        double b0 = b2*b1 - pow((b*b*b/16.0 - b*c/4.0 + d/2.0), 2);

        vector<double> resInter = solve3degree(1, b2, b1, b0);

        if (resInter.size() == 0) {
            return res;
        } else {
            z0 = resInter.at(0);
            delta = 2.0*(z0 + b2);
            if (delta < 0) {
                return res;
            } else if (delta == 0.0) {
                delta2 = z0*z0 + b1;
                if (delta2 < 0.0) {
                    return res;
                } else {
                    delta3 = sqrt(z0*z0 + b1);
                }
            } else {
                delta3 = sqrt((b2*b1 - b0)/delta);
            }
        }
        double alpha = delta - 4.0*(z0 - delta3);
        if (alpha == 0.0) {
            res.push_back(-sqrt(delta)/2.0 + b/4.0);
        } else if (alpha > 0) {
            res.push_back(-(sqrt(delta) + sqrt(alpha))/2.0 - b/4.0);
            res.push_back(-(sqrt(delta) - sqrt(alpha))/2.0 - b/4.0);
        }

        double beta = delta - 4.0*(z0 + delta3);
        if (beta == 0.0) {
            res.push_back(sqrt(delta)/2.0 + b/4.0);
        } else if (beta > 0.0) {
            res.push_back((sqrt(delta) + sqrt(beta))/2.0 - b/4.0);
            res.push_back((sqrt(delta) - sqrt(beta))/2.0 - b/4.0);
        }
    }

    sort(res.begin(), res.end());

    return res;
}

vector<double> Solver::getRealSortedSol(std::vector<cpx> res) {
    vector<double> resReal;

    for (int k = 0; k < res.size(); k++) {
        cpx currSol = res.at(k);
        if (currSol.imag() == 0) {
            resReal.push_back(currSol.real());
        }
    }

    if (resReal.size() > 0)
        sort(resReal.begin(), resReal.end());

    return resReal;
}

int Solver::SolveQuartic(double c[], double s[]) {
    // From Graphics Gems I by Jochen Schwartz

    double  coeffs[ 4 ];
    double  z, u, v, sub;
    double  A, B, C, D;
    double  sq_A, p, q, r;
    int     i, num;

    // Normal form: x^4 + Ax^3 + Bx^2 + Cx + D = 0

    A = c[ 3 ] / c[ 4 ];
    B = c[ 2 ] / c[ 4 ];
    C = c[ 1 ] / c[ 4 ];
    D = c[ 0 ] / c[ 4 ];

    //  substitute x = y - A/4 to eliminate cubic term:
    // x^4 + px^2 + qx + r = 0

    sq_A = A * A;
    p    = - 3.0/8 * sq_A + B;
    q    = 1.0/8 * sq_A * A - 1.0/2 * A * B + C;
    r    = - 3.0/256*sq_A*sq_A + 1.0/16*sq_A*B - 1.0/4*A*C + D;

    if (std::fabs(r) <= 0.00001) {
        // no absolute term: y(y^3 + py + q) = 0

        coeffs[ 0 ] = q;
        coeffs[ 1 ] = p;
        coeffs[ 2 ] = 0;
        coeffs[ 3 ] = 1;

        num = SolveCubic(coeffs, s);

        s[ num++ ] = 0;
    } else {
        // solve the resolvent cubic ...
        coeffs[ 0 ] = 1.0/2 * r * p - 1.0/8 * q * q;
        coeffs[ 1 ] = - r;
        coeffs[ 2 ] = - 1.0/2 * p;
        coeffs[ 3 ] = 1;

        (void) SolveCubic(coeffs, s);

        // ... and take the one real solution ...
        z = s[ 0 ];

        // ... to Build two quadric equations
        u = z * z - r;
        v = 2 * z - p;

        if (std::fabs(u) <= 0.00001)
            u = 0;
        else if (u > 0)
            u = std::sqrt(u);
        else
            return 0;

        if (std::fabs(v) <= 0.00001)
            v = 0;
        else if (v > 0)
            v = std::sqrt(v);
        else
            return 0;

        coeffs[ 0 ] = z - u;
        coeffs[ 1 ] = q < 0 ? -v : v;
        coeffs[ 2 ] = 1;

        num = SolveQuadric(coeffs, s);

        coeffs[ 0 ]= z + u;
        coeffs[ 1 ] = q < 0 ? v : -v;
        coeffs[ 2 ] = 1;

        num += SolveQuadric(coeffs, s + num);
    }

    // resubstitute

    sub = 1.0/4 * A;

    for (i = 0; i < num; ++i)
        s[ i ] -= sub;

    return num;
}

int Solver::SolveCubic(double c[], double s[]) {
    // From Graphics Gems I bu Jochen Schwartz
    int     i, num;
    double  sub;
    double  A, B, C;
    double  sq_A, p, q;
    double  cb_p, D;

    // Normal form: x^3 + Ax^2 + Bx + C = 0
    A = c[ 2 ] / c[ 3 ];
    B = c[ 1 ] / c[ 3 ];
    C = c[ 0 ] / c[ 3 ];

    //  substitute x = y - A/3 to eliminate quadric term:
    //    x^3 +px + q = 0
    sq_A = A * A;
    p = 1.0/3 * (- 1.0/3 * sq_A + B);
    q = 1.0/2 * (2.0/27 * A * sq_A - 1.0/3 * A * B + C);

    // use Cardano's formula
    cb_p = p * p * p;
    D = q * q + cb_p;

    if (std::fabs(D) <= 0.00001) {
        if (std::fabs(q) <= 0.00001) { // one triple solution
            s[ 0 ] = 0;
            num = 1;
        } else { // one single and one G4double solution
            double u = std::pow(-q,1./3.);
            s[ 0 ] = 2 * u;
            s[ 1 ] = - u;
            num = 2;
        }
    } else if (D < 0) { // Casus irreducibilis: three real solutions
        double phi = 1.0/3 * std::acos(-q / std::sqrt(-cb_p));
        double t = 2 * std::sqrt(-p);

        s[ 0 ] =   t * std::cos(phi);
        s[ 1 ] = - t * std::cos(phi + pi / 3);
        s[ 2 ] = - t * std::cos(phi - pi / 3);
        num = 3;
    } else { // one real solution
        double sqrt_D = std::sqrt(D);
        double u = std::pow(sqrt_D - q,1./3.);
        double v = - std::pow(sqrt_D + q,1./3.);

        s[ 0 ] = u + v;
        num = 1;
    }

    // resubstitute
    sub = 1.0/3 * A;

    for (i = 0; i < num; ++i)
        s[ i ] -= sub;

    return num;
}


int Solver::SolveQuadric(double c[], double s[]) {
    // From Graphics Gems I by Jochen Schwartz
    double p, q, D;

    // Normal form: x^2 + px + q = 0
    p = c[ 1 ] / (2 * c[ 2 ]);
    q = c[ 0 ] / c[ 2 ];

    D = p * p - q;

    if (std::fabs(D) <= 0.00001) {
        s[ 0 ] = - p;
        return 1;
    } else if (D < 0) {
        return 0;
    } else if (D > 0) {
        double sqrt_D = std::sqrt(D);

        s[ 0 ] =   sqrt_D - p;
        s[ 1 ] = - sqrt_D - p;
        return 2;
    }

    return 0;
}
