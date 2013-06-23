#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "MVector.h"

using namespace std;

template<class T>
MVector<T>::MVector(unsigned int size, T valeur) :
    _coords(size, valeur) {
}

template<class T>
MVector<T>::MVector(const MVector<T>& mVector) {
    _coords = mVector._coords;
}

template<class T>
unsigned MVector<T>::getSize() const {
    return _coords.size();
}

template<class T>
void MVector<T>::insertBack(T value) {
    _coords.push_back(value);
}

template<class T>
void MVector<T>::setAt(unsigned index, T value) {
    _coords[index] = value;
}
/*
template<class T>
double MVector<T>::dotProduct() const {
 return (*this) * (*this);
}

template<class T>
double MVector<T>::norm() const {
 return sqrt(dotProduct());
}
*/
template<class T>
T& MVector<T>::operator[](unsigned index) {
    if (index < _coords.size()) {
        return _coords[index];
    }
    throw MVector<T>::OutOfBounds("Taille dépassée");
}

template<class T>
T MVector<T>::operator[](unsigned index) const {
    if (index < _coords.size()) {
        return _coords[index];
    }
    throw MVector<T>::OutOfBounds("Taille dépassée");
}
/*
template<class T>
MVector<T> operator+(const MVector<T>& mVector1, const MVector<T>& mVector2) {
 int length1 = mVector1.getSize();
 int length2 = mVector2.getSize();
 if (length1 == length2) {
  MVector<T> mvect_somme(length1);
  for (int k = 0; k < length1; k++) {
   mvect_somme[k] = mVector1[k] + mVector2[k];
  }
  return mvect_somme;
 }
 throw MVector<T>::BadDimensions("Les deux vecteurs n'ont pas la même dimension");
}

template<class T>
MVector<T> MVector::operator-() const {
 MVector<T> res;
 for (unsigned k = 0; k < getSize(); k++) {
  res.insertBack(- _coords[k]);
 }
 return res;
}

template<class T>
MVector<T> operator-(const MVector<T>& mVector1, const MVector<T>& mVector2) {
 return mVector1 + (-mVector2);
}

template<class T>
double operator*(const MVector<T>& mVector1, const MVector<T>& mVector2) {
 int length1 = mVector1.getSize();
 int length2 = mVector2.getSize();
 double result = 0;
 if (length1 == length2) {
  for (int k = 0; k < length1; k++) {
   result += mVector1[k] * mVector2[k];
  }
  return result;
 }
 throw MVector<T>::BadDimensions("Les deux vecteurs n'ont pas la même dimension");
}

template<class T>
MVector<T> operator*(T scalar, const MVector<T>& mVector) {
 MVector<T> res;
 for (unsigned k = 0; k < mVector.getSize(); k++) {
  res.insertBack(mVector[k]*scalar);
 }
 return res;
}

template<class T>
MVector<T>& MVector<T>::operator+=(const MVector<T>& mVector) {
 return *this = (*this + mVector);
}

template<class T>
MVector<T>& MVector<T>::operator-=(const MVector<T>& mVector) {
 return *this = (*this - mVector);
}

template<class T>
MVector<T>& MVector<T>::operator*=(T scalar) {
 return *this = scalar * (*this);
}

*/
template<class T>
MVector<T>& MVector<T>::operator=(const MVector<T>& mVector) {
    _coords = mVector._coords;
    return *this;
}

template<class T>
bool operator==(const MVector<T>& mVector1, const MVector<T>& mVector2) {
    return mVector1._coords == mVector2._coords;
}

template<class T>
bool operator!=(const MVector<T>& mVector1, const MVector<T>& mVector2) {
    return !(mVector1 == mVector2);
}

template<class T>
ostream& operator<<(ostream &os, const MVector<T>& mvector) {
    int size = mvector.getSize();
    os << "[ ";
    for (int k = 0; k < size; k++) {
        os << mvector[k] << " ";
    }
    return os << "]";
}
