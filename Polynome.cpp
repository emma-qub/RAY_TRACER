#include "Polynome.h"
#include <math.h>
#include <iostream>

using namespace itpp;
using namespace std;


/**
  Constructeurs et destructeur
  **/

Polynome::Polynome(int degree) :
    _degree(degree) {

    _matrix.set_size(degree + 1, degree + 1);
    _matrix.clear();
}

Polynome::Polynome(const Polynome& polynome) {
    _degree = polynome._degree;
    _matrix = polynome._matrix;
}

Polynome::~Polynome() {
}

/**
  Ajout d'un trinome K*x^dx*y^dy*z^dy
  **/
void Polynome::addTrinome(const Trinome& trinome) {
    _matrix(trinome._dy, trinome._dx) = trinome._coeff;
}

/**
  Lecture de la matrice de représentation pour obtenir le vecteur
  correspondant dans la base Lexicographique
  **/

QVector<double> Polynome::read() const {
    QVector<double> res;

    for (int j =_degree; j >= 0; j--) {
        for (int i = _degree-j; i >= 0; i--) {
            res.push_back(_matrix(i, j));
        }
    }

    return res;
}

/**
  Multiplie le polynome par tous les trinomes de degré nu possibles
  **/

mat Polynome::getMatrix(int nu) {
    mat F;
    int c = 0;
    int n = (nu + 2) * (nu + 1) / 2;
    int m = (nu + _degree + 2) * (nu + _degree + 1) / 2;

    F.set_size(m,n);
    F.clear();

    for(int i = 0; i <= nu; i++) {
        for (int j = 0; j <= i; j++) {
            Trinome trinome(nu-i, i-j, j, 1);
            Polynome mult = (*this);
            mult = mult * trinome;
            QVector<double> vect = mult.read();
            for(int k=0;k<vect.size();k++) {
                F(k,c) = vect.at(k);
            }
            c++;
        }
    }

    return F;
}

/**
  Calcul des dérivées du polynome par rapport à X et Y
  **/

Polynome Polynome::deriveeX() {
    mat D;
    D.set_size(_degree, _degree);
    D.clear();
    Polynome p(_degree-1);
    for(int i = 0; i < _degree; i++) {
        for(int j = 0; j < _degree; j++) {
            D(i, j) = _matrix(i, j+1) * (j+1);
        }
    }
    p.setMatrix(D);
    return p;
}

Polynome Polynome::deriveeY() {
    mat D;
    D.set_size(_degree, _degree);
    D.clear();
    Polynome p(_degree-1);
    for(int i = 0; i < _degree; i++) {
        for(int j = 0; j < _degree; j++) {
            D(i, j) = _matrix(i+1, j) * (i+1);
        }
    }
    p.setMatrix(D);
    return p;
}

/**
  Evaluation de P(x,y,z) à partir de la matrice
  **/

double Polynome::evaluate(double x, double y, double z) {
    double val = 0;
    for(int j = _degree; j >= 0; j--) {
        for(int i = _degree-j; i >= 0; i--) {
            val += _matrix(i, j) * pow(x, j) * pow(y, i) * pow(z, _degree);
        }
    }
    return val;
}

/**
  Multiplication entre un polynome de degré d et un trinome de degré nu
  **/

Polynome operator*(const Polynome& polynome, const Trinome& trinome) {
    int degree = polynome._degree + trinome._dx + trinome._dy + trinome._dz;
    Polynome mult(degree);
    mat Mm;
    Mm.set_size(degree + 1, degree + 1);
    Mm.clear();
    int nbz_up = trinome._dy;
    int nbz_left = trinome._dx;
    for(int i = 0; i < polynome._degree + 1; i++) {
        for(int j = 0; j < polynome._degree + 1; j++) {
            Mm(i + nbz_up, j + nbz_left) = polynome._matrix(i, j);
        }
    }
    mult._matrix = Mm;
    return mult;
}
