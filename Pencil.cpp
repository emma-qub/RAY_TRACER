#include "Pencil.h"
#include "MatrixOpp.h"

using namespace itpp;
using namespace std;


extern "C" {
    void dggev_(const char* JOBVL, const char* JOBVR, const int* N,
                const double* A, const int* LDA, const double* B, const int* LDB,
                double* ALPHAR, double* ALPHAI, double* BETA,
                double* VL, const int* LDVL, double* VR, const int* LDVR,
                double* WORK, const int* LWORK, int* INFO
         );
}


/**
  Constructeur
  **/

Pencil::Pencil(itpp::mat A, itpp::mat B) :
    A(A),
    B(B) {

    getRegular();
}

/**
  Transformation du pinceau en matrices carrées (partie régulière)
  **/

// Forme échelon par colonne
mat echelonCols(mat B) {
    mat U, V;
    vec s;
    svd(B, U, s, V);
    return V;
}

// Forme échelon par lignes
mat echelonRows(mat A) {
    mat U, V;
    vec s;
    //cerr << "######## ECHELON PAR LIGNE ########" << endl;
    //cerr << "A=" << A << endl;
    svd(A, U, s, V);
    //cerr << "A=" << A << endl;
    //cerr << "######## /ECHELON PAR LIGNE ########" << endl;
    mat E2 = U.transpose();
    return E2;
}


// Réduction du pinceau de matrice (A,B) en (A',B')
void Pencil::reduce() {

    //cerr << "##########" << endl << A << endl << "##########" << endl << B << endl << "##########" << endl;


    int n = B.cols();
    MatrixOpp mo;

    // Forme échelon sur les colonnes de B
    int r = mo.rank(B);
    mat C2 = echelonCols(B);

    // Application à A
    mat A2 = A*C2;
    A2.del_cols(0,r-1);
    //cerr << A2.rows() << " " << A2.cols() << endl;

    // Forme échelon sur les lignes de A2
    int rA2 = mo.rank(A2, pow(10, -10));
    //cerr << "rkA2=" << rA2 << endl;
    vec sA2; mat uA2, vA2; svd(A2, uA2, sA2, vA2);
    //cerr << "sA2=" << sA2 << endl;
    mat E2 = echelonRows(A2);

    // Obtention d'un pinceau réduit
    mat EBC = E2*B*C2;
    mat EAC = E2*A*C2;
    EBC.del_cols(r,n-1);
    EAC.del_cols(r,n-1);
    if (rA2 > 0) {
        EBC.del_rows(0, rA2-1);
        EAC.del_rows(0, rA2-1);
    }
    A = EAC;
    B = EBC;
}

// Obtention d'un pinceau carré
void Pencil::getRegular() {
    int nbCols = B.cols();
    MatrixOpp mo;
    int rk = mo.rank(B);


//    std::cerr << "################Hors du while#################" << std::endl;
//    std::cerr << "A=" << this->A << std::endl;
//    std::cerr << "B=" << this->B << std::endl;
//    std::cerr << "rk=" << rk << std::endl;
//    std::cerr << "nbCols=" << nbCols << std::endl;
//    std::cerr << "rkAB=" << mo.rank(A-B) << std::endl;
//    std::cerr << "rkA3B=" << mo.rank(A-3*B) << std::endl;
//    std::cerr << "################/Hors du while#################" << std::endl;


    while(rk < nbCols) {
        reduce();
        nbCols = B.cols();
        rk = mo.rank(B);


//        std::cerr << "################Dans le while#################" << std::endl;
//        std::cerr << "A=" << this->A << std::endl;
//        std::cerr << "B=" << this->B << std::endl;
//        std::cerr << "rk=" << rk << std::endl;
//        std::cerr << "nbCols=" << nbCols << std::endl;
//        std::cerr << "rkAB=" << mo.rank(A-B) << std::endl;
//        std::cerr << "rkA3B=" << mo.rank(A-3*B) << std::endl;
//        std::cerr << "################/Dans le while#################" << std::endl;


    }
    if(B.cols() != B.rows()) {
        cout << "transposition" << endl;
        A = A.transpose();
        B = B.transpose();
        getRegular();
    }
}

/**
  Calcul des valeurs propres généralisées d'un pinceau REDUIT
  **/
vector<double> Pencil::getGev() const {
    //TODO encapsuler ds le MatrixOpp
    char jobvl = 'N';
    char jobvr = 'V';
    int n;
    int lda;
    int ldb;
    int ldvl;
    int ldvr;
    int lwork;
    int info;

//    cerr << endl << A << endl;
//    cerr << endl << B << endl;

    n = lda = A.rows();
    ldb = B.rows();
    ldvl = 1;
    ldvr = n;

    //lwork = std::max(1,  n*n+64); // This may be choosen better! ???
    lwork = 8*A.rows();

    vec work(lwork);
    vec alphar(n);
    vec alphai(n);
    vec beta(n);
    mat vl(1, n);
    mat vr(n, n);

    dggev_(&jobvl, &jobvr, &n,
           A._data(), &lda, B._data(), &ldb,
           alphar._data(), alphai._data(), beta._data(),
           vl._data(), &ldvl, vr._data(), &ldvr,
           work._data(), &lwork, &info);

//    cerr << endl << A << endl;
//    cerr << endl << B << endl;

    vector<double> gev;
    for(int i=0; i < n; i++){
//        cerr << "beta(i)=" << beta(i) << endl;
//        cerr << "alphai(i)=" << alphai(i) << endl;
//        cerr << "alphar(i)=" << alphar(i) << endl;
        if (abs(beta(i)) > 0.0001 && alphai(i) == 0) {
            double vp = alphar(i)/beta(i);
            if (vp > 0) {
                //cerr << vp << endl;
                gev.push_back(vp);
            }
        }
    }
    return gev;
}
