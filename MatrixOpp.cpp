#include "MatrixOpp.h"

#define THRESHOLD 10e-6

using namespace itpp;
/*
mat MatrixOpp::null_svd(const mat& matrix) {

    int nbRows = matrix.rows();
    int nbCols = matrix.cols();

    itpp::mat u(nbRows, nbRows), v(nbCols, nbCols);
    int nbSingular = std::min(nbRows, nbCols);
    itpp::vec s(nbSingular);

    svd(matrix, u, s, v);

    int k = rank(matrix);

    //return itpp::mat(v.get_cols(nbCols-k-1, nbCols-1));

    //return v.get_cols(0,k-1);

}
*/
int MatrixOpp::rank(const mat &m, double tol) {
  int rows = m.rows();
  int cols = m.cols();
  if ((rows == 0) || (cols == 0))
    return 0;

  vec sing_val = svd(m);
  //std::cerr << "rank sing" << sing_val << std::endl;

  if (tol < 0.0) { // Calculate default tolerance
    tol = eps * sing_val(0) * (rows > cols ? rows : cols);
    std::cerr << "eps=" << eps << std::endl;
  }

  // Count number of nonzero singular values
  int r = 0;
  while ((r < sing_val.length()) && (sing_val(r) > tol)) {
    r++;
  }

  return r;
}
