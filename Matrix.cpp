#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Matrix.h"

using namespace std;

template<class T>
Matrix<T>::Matrix(unsigned lines, unsigned columns, bool random, T value) {
    MVector<T> mVector(lines, value);
    for (unsigned k = 0; k < columns; k++) {
        _components.push_back(mVector);
    }
    if (random) {
        for (unsigned k = 0; k < columns; k++) {
            for (unsigned i = 0; i < lines; i++) {
                double randElem = rand()%10;
                (*this)(i, k) = randElem;
            }
        }
    }
}

template<class T>
Matrix<T>::Matrix(unsigned size) {
    MVector<T> mVector(size, 0);
    for (unsigned k = 0; k < size; k++) {
        _components.push_back(mVector);
    }
    for (unsigned k = 0; k < size; k++) {
        setElementK(k, k, 1);
    }
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& matrix) {
    _components = matrix._components;
}

template<class T>
Matrix<T>::Matrix(const MVector<T>& mVector) {
    _components.push_back(mVector);
}

template<class T>
void Matrix<T>::setElementK(unsigned line, unsigned column, T value) {
    if (line <= nbLines() && column <= nbColumns()) {
        _components[column][line] = value;
    } else {
        throw Matrix<T>::OutOfBounds("Taille dépassée (setElementK)");
    }
}

template<class T>
void Matrix<T>::insertBack(const MVector<T>& mVector) {
    if (nbLines() == 0 || nbLines() == mVector.getSize()) {
        _components.push_back(mVector);
    } else {
        throw Matrix<T>::BadDimensions("Le nombre de lignes de la matrice et la taille du vecteur a insérer sont différents (insertBack)");
    }
}

template<class T>
Matrix<T> Matrix<T>::transpose() const {
    if (nbLines() == 0) {
        return *this;
    } else {
        unsigned nbLine = nbLines();
        Matrix<T> result;
        for (unsigned k = 0; k < nbLine; k++) {
            result.insertBack(getLine(k));
        }
        return result;
    }
}

template<class T>
MVector<T> Matrix<T>::getLine(unsigned line) const {
    if (line < nbLines()) {
        unsigned size = nbColumns();
        MVector<T> mvectorColonne(size);
        for (unsigned k = 0; k < size; k++) {
            mvectorColonne[k] = getColumn(k)[line];
        }
        return mvectorColonne;
    } else {
        throw Matrix<T>::OutOfBounds("Taille dépassée (getLine)");
    }
}

template<class T>
MVector<T> Matrix<T>::getColumn(unsigned column) const {
    if (column < _components.size()) {
        return _components[column];
    } else {
        throw Matrix<T>::OutOfBounds("Taille dépassée (getColumn)");
    }
}

template<class T>
unsigned Matrix<T>::nbLines() const {
    try {
        return getColumn(0).getSize();
    } catch (OutOfBounds& e) {
    }
    return 0;
}

template<class T>
unsigned Matrix<T>::nbColumns() const {
    return _components.size();
}
/*
template<class T>
void Matrix<T>::swapLine(unsigned line1, unsigned line2) {
 if (line1 != line2) {
  MVector<T> mline1 = getLine(line1);
  MVector<T> mline2 = getLine(line2);
  for (unsigned k = 0; k < nbColumns(); k++) {
   setElementK(line1, k, mline2[k]);
   setElementK(line2, k, mline1[k]);
  }
 }
}

template<class T>
void Matrix<T>::setLine(unsigned line, const MVector<T>& newLine) {
 unsigned nbNewLines = newLine.getSize();
 if (nbLines() == nbNewLines) {
  for (unsigned k = 0; k < nbNewLines; k++) {
   setElementK(line, k, newLine[k]);
  }
 } else {
  throw BadDimensions("La ligne à remplacer et la nouvelle ligne ne font pas la même taille (setLine)");
 }
}
*/
template<class T>
MVector<T>& Matrix<T>::operator[](unsigned index) {
    if (index < _components.size()) {
        return _components[index];
    }
    throw Matrix<T>::OutOfBounds("Taille dépassée (operator[])");
}

template<class T>
MVector<T> Matrix<T>::operator[](unsigned index) const {
    if (index < _components.size()) {
        return _components[index];
    }
    throw Matrix<T>::OutOfBounds("Taille dépassée (operator[] const)");
}

template<class T>
T& Matrix<T>::operator()(unsigned line, unsigned column) {
    return _components[column][line];
}

template<class T>
T Matrix<T>::operator()(unsigned line, unsigned column) const {
    return _components[column][line];
}
/*
template<class T>
Matrix<T> operator+(const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
 int nbLines1 = matrix1.nbLines();
 int nbLines2 = matrix2.nbLines();
 int nbColumns1 = matrix1.nbColumns();
 int nbColumns2 = matrix2.nbColumns();
 if ((nbLines1 == nbLines2) && (nbColumns1 == nbColumns2)) {
  Matrix<T> matrixSomme;
  for (int k = 0; k < nbColumns1; k++) {
   matrixSomme.insertBack(matrix1[k] + matrix2[k]);
  }
  return matrixSomme;
 } else {
  throw Matrix<T>::BadDimensions("Les matrices n'ont pas la même taille (operator+ ou operator-)");
 }
}

template<class T>
Matrix<T> Matrix<T>::operator-() const {
 Matrix<T> res;
 for (unsigned k = 0; k < nbColumns(); k++) {
  res.insertBack(- _components[k]);
 }
 return res;
}

template<class T>
Matrix<T> operator-(const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
 return matrix1 + (-matrix2);
}

template<class T>
Matrix<T> operator*(const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
 int nbColumns1 = matrix1.nbColumns();
 int nbColumns2 = matrix2.nbColumns();
 int nbLines1 = matrix1.nbLines();
 int nbLines2 = matrix2.nbLines();
 if (nbColumns1 == nbLines2) {
  Matrix<T> matrixProduit(nbLines1, nbColumns2);
  for (int i = 0; i < nbLines1; i++) {
   for (int j = 0; j < nbColumns2; j++) {
    matrixProduit(i, j) = (matrix1.getLine(i) * matrix2.getColumn(j));
   }
  }
  return matrixProduit;
 }
 throw Matrix<T>::BadDimensions("Les matrices n'ont pas les bonnes dimensions (operator*)");
}

template<class T>
Matrix<T> operator*(double scalar, const Matrix<T>& matrix) {
 Matrix<T> res;
 for (unsigned k = 0; k < matrix.nbColumns(); k++) {
  res.insertBack(scalar * matrix[k]);
 }
 return res;
}

template<class T>
Matrix<T> pow(const Matrix<T>& matrix, int n) {
 if (matrix.nbLines() == matrix.nbColumns()) {
  if (n == 0) {
   return Matrix<T>(matrix.nbLines());
  } else if (n == 1) {
   return matrix;
  } else if (n%2 == 0) {
   return pow(matrix*matrix, n/2);
  } else {
   return matrix * pow(matrix*matrix, (n-1)/2);
  }
 } else {
  throw Matrix<T>::BadDimensions("La matrice n'est pas carrée, donc pas élevable à une puissance entière (pow)");
 }
}

template<class T>
unsigned Matrix<T>::getGreaterPivot(unsigned line, unsigned column) const {
 double pivotMax = getLine(line)[column];
 if (pivotMax < 0) pivotMax *= -1;
 double resLine = line;
 for (unsigned k = line; k < nbLines(); k++) {
  double currentPivot = getLine(k)[column];
  if (currentPivot < 0) currentPivot *= -1;
  if (currentPivot > pivotMax) {
   pivotMax = currentPivot;
   resLine = k;
  }
 }
 return resLine;
}

template<class T>
Matrix<T> Matrix<T>::gaussJordan() const {
 Matrix<T> copyM(*this);
 Matrix<T> inverse(nbLines());
 unsigned size = copyM.nbLines();
 bool isInversible;
 for (unsigned k = 0; k < size; k++) {
  isInversible = false;
  for (unsigned i = k; i < size; i++) {
   if (copyM(i, k) != 0) {
    unsigned bestLine = copyM.getGreaterPivot(i, k);
    copyM.swapLine(bestLine, k);
    inverse.swapLine(bestLine, k);
    isInversible = true;
    break;
   }
  }
  if (!isInversible) {
   throw NotInversible("La Matrice n'est pas inversible (gaussJordan)");
  }
  double akk = copyM(k, k);
  copyM.setLine(k, MVector<T>(1/akk * copyM.getLine(k)));
  inverse.setLine(k, MVector<T>(1/akk * inverse.getLine(k)));
  for (unsigned i = 0; i < size; i++) {
   if (i != k) {
    double aik = copyM(i, k);
    copyM.setLine(i, MVector<T>(copyM.getLine(i) - aik*copyM.getLine(k)));
    inverse.setLine(i, MVector<T>(inverse.getLine(i) - aik*inverse.getLine(k)));
   }
  }
 }

 return inverse;
}

template<class T>
Matrix<T>::operator MVector<T>() const {
 if (_components.size() == 1) {
  return _components[0];
 }
 throw BadDimensions("La matrice a plus d'une colonne (operator MVector<T>)");
}

template<class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& matrix) {
 return *this = (*this + matrix);
}

template<class T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& matrix) {
 return *this = (*this - matrix);
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix) {
 _components = matrix._components;
 return *this;
}
*/

template<class T>
bool operator==(const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
    return matrix1._components == matrix2._components;
}

template<class T>
bool operator!=(const Matrix<T>& matrix1, const Matrix<T>& matrix2) {
    return !(matrix1 == matrix2);
}

template<class T>
ostream& operator<<(ostream &os, const Matrix<T>& matrix) {
    int size = matrix.nbLines();
    Matrix<T> tmatrix = matrix.transpose();
    os << "[" << endl;
    for (int k = 0; k < size; k++) {
        os << "  " << tmatrix[k] << endl;
    }
    return os << "]";
}
