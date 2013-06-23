#include "Vector3.h"
#include <cmath> // sqrt ()

Vector3::Vector3(double x, double y, double z) {
    _coords[0] = x;
    _coords[1] = y;
    _coords[2] = z;
}

Vector3::Vector3(const Vector3& vector) {
    *this = vector;
}

Vector3::~Vector3() {
}

double Vector3::operator[](int i) const {
    return _coords[i];
}

double& Vector3::operator[](const int &i) {
    return _coords[i];
}

bool operator==(const Vector3& vector1, const Vector3& vector2) {
    return vector1[0] == vector2[0] && vector1[1] == vector2[1] && vector1[2] == vector2[2];
}

bool operator!=(const Vector3& vector1, const Vector3& vector2) {
    return !(vector1 == vector2);
}

const Vector3& Vector3::operator+() const {
    return *this;
}

Vector3 Vector3::operator-() const {
    return Vector3(-_coords[0], -_coords[1], -_coords[2]);
}

Vector3& Vector3::operator=(const Vector3& vector) {
    _coords[0] = vector[0];
    _coords[1] = vector[1];
    _coords[2] = vector[2];
    return *this;
}

Vector3 operator*(const Vector3& vector, const double k) {
    return Vector3(vector[0] * k, vector[1] * k, vector[2] * k);
}

Vector3 operator*(const double k, const Vector3& vector) {
    return Vector3(vector[0] * k, vector[1] * k, vector[2] * k);
}

Vector3 operator/(const Vector3& vector, const double k) {
    return Vector3(vector[0] / k, vector[1] / k, vector[2] / k);
}

Vector3 operator+(const Vector3& vector1, const Vector3& vector2) {
    return Vector3(vector1[0] + vector2[0], vector1[1] + vector2[1], vector1[2] + vector2[2]);
}

Vector3 operator-(const Vector3& vector1, const Vector3& vector2) {
    return Vector3(vector1[0] - vector2[0], vector1[1] - vector2[1], vector1[2] - vector2[2]);
}

Vector3& Vector3::operator*=(const double k) {
    return *this = (*this * k);
}

Vector3& Vector3::operator/=(const double k) {
    return *this = (*this / k);
}

Vector3& Vector3::operator+=(const Vector3& vector) {
    return *this = (*this + vector);
}

Vector3& Vector3::operator-=(const Vector3& vector) {
    return *this = (*this - vector);
}

double dot_product(const Vector3& vector1, const Vector3& vector2) {
    return vector1[0] * vector2[0] + vector1[1] * vector2[1] + vector1[2] * vector2[2];
}

Vector3 cross_product(const Vector3& vector1, const Vector3& vector2) {
    return Vector3(
		vector1[1] * vector2[2] - vector1[2] * vector2[1],
		vector1[2] * vector2[0] - vector1[0] * vector2[2],
		vector1[0] * vector2[1] - vector1[1] * vector2[0]
                );
}

double triple_product(const Vector3& vector1, const Vector3& vector2, const Vector3& vector3) {
    return dot_product(cross_product(vector1, vector2), vector3);
}

double Vector3::norm() const {
    return sqrt(
		_coords[0] * _coords[0]
                + _coords[1] * _coords[1]
                + _coords[2] * _coords[2]
                );
}

double Vector3::squared_norm() const {
    return (
		_coords[0] * _coords[0]
                + _coords[1] * _coords[1]
                + _coords[2] * _coords[2]
                );
}

Vector3& Vector3::normalize() {
    return (*this = *this / (*this).norm());
}

Vector3 Vector3::normalized() const {
    return *this / (*this).norm();
}

double Vector3::min_coord() const {
    double tmp = _coords[0];
    if (tmp > _coords[1])
        tmp = _coords[1];
    if (tmp > _coords[2])
        tmp = _coords[2];
    return tmp;
}

double Vector3::max_coord() const {
    double tmp = _coords[0];
    if (tmp < _coords[1])
        tmp = _coords[1];
    if (tmp < _coords[2])
        tmp = _coords[2];
    return tmp;
}

double Vector3::min_abs_coord() const {
    double tmp = fabs(_coords[0]);
    if (tmp > fabs(_coords[1]))
        tmp = fabs(_coords[1]);
    if (tmp > fabs(_coords[2]))
        tmp = fabs(_coords[2]);
    return tmp;
}

double Vector3::max_abs_coord() const {
    double tmp = fabs(_coords[0]);
    if (tmp < fabs(_coords[1]))
        tmp = fabs(_coords[1]);
    if (tmp < fabs(_coords[2]))
        tmp = fabs(_coords[2]);
    return tmp;
}

int Vector3::index_min_coord() const {
    int index = 0;
    double tmp = _coords[0];
    if (tmp > _coords[1]) {
        tmp = _coords[1];
        index = 1;
    }
    if (tmp > _coords[2])
        index = 2;
    return index;
}

int Vector3::index_max_coord() const {
    int index = 0;
    double tmp = _coords[0];
    if (tmp < _coords[1]) {
        tmp = _coords[1];
        index = 1;
    }
    if (tmp < _coords[2])
        index = 2;
    return index;
}

int Vector3::index_min_abs_coord() const {
    int index = 0;
    double tmp = fabs(_coords[0]);
    if (tmp > fabs(_coords[1])) {
        tmp = fabs(_coords[1]);
        index = 1;
    }
    if (tmp > fabs(_coords[2]))
        index = 2;
    return index;
}

int Vector3::index_max_abs_coord() const {
    int index = 0;
    double tmp = fabs(_coords[0]);
    if (tmp < fabs(_coords[1])) {
        tmp = fabs(_coords[1]);
        index = 1;
    }
    if (tmp < fabs(_coords[2]))
        index = 2;
    return index;
}

Vector3 minVect(const Vector3& vector1, const Vector3& vector2) {
    Vector3 vector(vector1);
    if (vector2[0] < vector1[0])
        vector[0] = vector2[0];
    if (vector2[1] < vector1[1])
        vector[1] = vector2[1];
    if (vector2[2] < vector1[2])
        vector[3] = vector2[2];
    return vector;
}

Vector3 maxVect(const Vector3& vector1, const Vector3& vector2) {
    Vector3 vector(vector1);
    if (vector2[0] > vector1[0])
        vector[0] = vector2[0];
    if (vector2[1] > vector1[1])
        vector = vector2[1];
    if (vector2[2] > vector1[2])
        vector = vector2[2];
    return vector;
}

std::ostream& operator<<(std::ostream &os, const Vector3& vector) {
    return os << "(" << vector[0] << "; " << vector[1] << "; " << vector[2] << ")";
}

std::istream& operator>>(std::istream &is, Vector3& vector) {
    return is >> vector._coords[0] >> vector._coords[1] >> vector._coords[2];
}
