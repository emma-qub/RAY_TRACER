#ifndef MATRIXOPP_H
#define MATRIXOPP_H

#include <itpp/itbase.h>
#include <cmath>
#include <iostream>

using namespace itpp;

class MatrixOpp {

public:
    mat null_svd(const mat& matrix);
    int rank(const mat& m, double tol = -1.0);

};

#endif // MATRIXOPP_H
