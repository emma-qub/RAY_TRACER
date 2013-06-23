#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <complex>
#include <cmath>

typedef std::complex<double> cpx;

class Solver {

public:
    static const double pi = 3.14159;
    Solver();
    virtual ~Solver();

    static std::vector<double> solve2degree(double a, double b, double c);
    static std::vector<double> solve3degree(double a, double b, double c, double d);
    static std::vector<double> solve4degree(double a, double b, double c, double d, double e);
    static std::vector<double> getRealSortedSol(std::vector<cpx> res);

    static int SolveQuartic(double c[], double s[]);
    static int SolveCubic(double c[], double s[]);
    static int SolveQuadric(double c[], double s[]);
};

#endif // SOLVER_H
