#include <algorithm>

#include "Surface.h"
#include "MatrixOpp.h"
#include "Sphere.h"
#include "Cylindre.h"

using namespace std;
using namespace itpp;

/**
  Constructeurs et destructeur
  **/

// Constructeur de Tests Manuels
Surface::Surface(const Color& color, const Material& material, vector<Polynome> polynome, vector<mat> matrix) :
    Shape(color, material),
    _matrix(matrix),
    _polynome(polynome) {
}

// Constructeur pour GUI
Surface::Surface(const Color& color, const Material& material, const QStringList& fourParams) :
    Shape(color, material),
    _equation1(fourParams.at(0)),
    _equation2(fourParams.at(1)),
    _equation3(fourParams.at(2)),
    _equation4(fourParams.at(3)) {

    for (int k = 0; k < fourParams.size(); k++) {
        ParserExpr formatedExpr(fourParams.at(k));
        initPolynome(formatedExpr);
    }
    initMatrix();
}

// Constructeur de copie
Surface::Surface(const Surface& surface) :
    Shape(surface._color, surface._material) {
    _matrix = surface._matrix;
    _polynome = surface._polynome;
}

// Destructeur
Surface::~Surface() {
}

/**
 * Initialisation des matrices de polynomes à partir des QString de l'utilisateur,
 * et création des matrices représentatives M1,M2,M3,M4
 */
void Surface::initPolynome(const ParserExpr& formatedExpr) {
    Polynome polynome(formatedExpr.getDegree());

    QStringList monomesList = formatedExpr.getMonomes();
    for (int k = 0; k < monomesList.size(); k++) {
        QVector<int> currExpo = formatedExpr.getExpoAt(k);
        Trinome trinome(currExpo.at(0), currExpo.at(1), currExpo.at(2), formatedExpr.getConstAt(k));
        polynome.addTrinome(trinome);
    }
    _polynome.push_back(polynome);


}

// Agencement des blocs 0 et identité en fonction de la matrice Mi que l'on souhaite obtenir
mat createT(int i, mat T0, mat Ti) {
    mat T;
    for (int j = 0; j < i; j++) {
        T = concat_vertical(T, T0);
    }
    T = concat_vertical(T, Ti);
    for (int j = i+1; j < 4; j++) {
        T = concat_vertical(T, T0);
    }
    return T;
}

void Surface::initMatrix() {
    int nu = 2*(_polynome.at(0)._degree - 1);
    mat Mat;
    Mat.clear();
    Mat = buildMat(nu);

    // Noyau
    MatrixOpp mo;
    int rk = mo.rank(Mat);

    mat U, K;
    vec s;
    svd(Mat, U, s, K);

    K.del_cols(0,rk-1);

    // Multiplications par Ti
    // TODO: ne récupérer que les blocs de matrix, inutile de multiplier par les Ti
    mat T0, Ti;
    int dim = (nu + 2)*(nu + 1)/2;
    T0.set_size(dim, dim);
    Ti.set_size(dim, dim);
    T0.zeros();
    Ti.clear();
    for (int i = 0; i < dim; i++) {
        Ti(i, i) = 1;
    }
    K = K.transpose();
    for (int i = 0; i < 4; i++) {
        mat T = createT(i, T0, Ti);
        _matrix.push_back((K*T).transpose());
    }

//    for (int k = 0; k < _matrix.size(); k++) {
//        cerr << endl << _matrix.at(k) << endl;
//    }

}

// Création de la matrice représentant l'application de paramétrisation (celle dont on cherche le noyau)
mat Surface::buildMat(int nu) {
    mat M1, M2, M3, M4;
    M1.clear();
    M2.clear();
    M3.clear();
    M4.clear();
    M1=_polynome.at(0).getMatrix(nu);
    M2=_polynome.at(1).getMatrix(nu);
    M3=_polynome.at(2).getMatrix(nu);
    M4=_polynome.at(3).getMatrix(nu);
    mat M = concat_horizontal(M1, M2);
    M = concat_horizontal(M, M3);
    M = concat_horizontal(M, M4);

    return M;
}

/**
  Calcul des intersections entre la surface et un rayon R
  **/

// Calcul du pinceau de matrice A,B tel que M=A-t.B

Pencil Surface::getPencil(const Ray& ray) const {
    Vector3 origin = ray._coords[0];
    Vector3 direction = ray._coords[1];

    mat A = _matrix.at(3) + origin[0] * _matrix.at(0) + origin[1] * _matrix.at(1) + origin [2] * _matrix.at(2);
    mat B = -(_matrix.at(0) * direction[0] + _matrix.at(1) * direction[1] + _matrix.at(2) * direction[2]);

    return Pencil(A, B);
}

// Calcul des intersections par la méthode des valeurs propres généralisées
vector<double> Surface::ensIntersect(const Ray& rayon) const {

    vector<double> gev;
    Pencil p = getPencil(rayon);

    if (p.A.rows() == 0) {
        return gev;
    } else {
         gev = p.getGev();
         sort(gev.begin(), gev.end());
         return gev;
    }
}

/**
  Calcul de la normal à la surface en point P
  **/

// Evalue les fi(s,t) dans la ligne 0, dfi/dx(s,t) en ligne 1 et dfi/dy(s,t) en ligne 2
mat Surface::derive_table(double s, double t) const {
    mat dve;
    dve.set_size(4,3);
    dve.clear();
    for(int i = 0; i < _polynome.size(); i++) {
        Polynome poly = _polynome.at(i);
        Polynome dx = poly.deriveeX();
        Polynome dy = poly.deriveeY();
        dve(i,0) = poly.evaluate(s, t);
        dve(i,1) = dx.evaluate(s, t);
        dve(i,2) = dy.evaluate(s, t);
    }
    return dve;
}

// Calcul du vecteur gradient de X:(s,t)->(f1/f4,f2/f4,f3/f4)(s,t)
Vector3 Surface::gradient(double s, double t) const {
    Vector3 v1, v2;
    mat table = derive_table(s, t);
    for (int i = 0; i < 3; i++) {
        //dérivées de quotient
        v1[i] = (table(i, 1)*table(3, 0) - table(i, 0)*table(3, 1))/pow(table(3, 0), 2);
        v2[i] = (table(i, 2)*table(3, 0) - table(i, 0)*table(3, 2))/pow(table(3, 0), 2);
    }
    return cross_product(v1, v2);
}

Vector3 normal_sphere(Vector3 ptIntersect) {
    double norm = sqrt(ptIntersect[0]*ptIntersect[0]
                     + ptIntersect[1]*ptIntersect[1]
                     + ptIntersect[2]*ptIntersect[2]
                  );
    if(norm != 0) {
        return ptIntersect/norm;
    } else {
        return Vector3();
    }
}

// Evaluation de la normal en déterminant (s,t) à partir de Ker(M.transposee())
Vector3 Surface::normal(const Vector3& pt) const {
    mat Msurf;
    MatrixOpp mo;
    Msurf.clear();
    Msurf = _matrix.at(3) + pt[0]*_matrix.at(0) + pt[1]*_matrix.at(1) + pt[2]*_matrix.at(2);
    // Noyau de la transposée de M
    Msurf = Msurf.transpose();
    int rk_init = Msurf.cols();
    int rk = mo.rank(Msurf,0.01);
    mat U, V;
    vec S;
    svd(Msurf, U, S, V);
    V.del_cols(0,rk-1);

    if(abs(V(2, 0)) > 10e-20 && (rk < rk_init)) {
        double s = V(0, 0)/V(2, 0);
        double t = V(1, 0)/V(2, 0);
        // Seuillage obligatoire
        s = floor(s*10e6)/10e6;
        t = floor(t*10e6)/10e6;
        Vector3 grad = gradient(s, t);
        return grad;
    } else {
        return Vector3();
    }
}


bool Surface::belongsTo(const Vector3 &ptIntersect) const {
    return false;
}

Surface* Surface::clone() const {
    return new Surface(*this);
}
