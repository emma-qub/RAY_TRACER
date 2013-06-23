#include "Vector2.h"
#include <cmath> // sqrt ()

Vector2::Vector2(double x, double y) {
    _coords[0] = x;
    _coords[1] = y;
}

Vector2::Vector2(const Vector2 &v1) {
    *this = v1;
}

Vector2::~Vector2() {
}

double Vector2::get_x() const {
    return _coords[0];
}

double Vector2::get_y() const {
    return _coords[1];
}

void Vector2::set_x(double x) {
    _coords[0] = x;
}

void Vector2::set_y(double y) {
    _coords[1] = y;
}

double Vector2::operator[](int i) const {
    return _coords[i];
}

double& Vector2::operator[](const int &i) {
    return _coords[i];
}

bool operator==(const Vector2 &v1, const Vector2 &v2) {
    return v1[0] == v2[0] && v1[1] == v2[1];
}

bool operator!=(const Vector2 &v1, const Vector2 &v2) {
    return !(v1 == v2);
}

const Vector2& Vector2::operator+() const {
    return *this;
}

Vector2 Vector2::operator-() const {
    return Vector2(-_coords[0], -_coords[1]);
}

Vector2& Vector2::operator=(const Vector2 &v) {
    _coords[0] = v[0];
    _coords[1] = v[1];
    return *this;
}

Vector2 operator*(const Vector2& v, const double k) {
    return Vector2(v[0] * k, v[1] * k);
}

Vector2 operator*(const double k, const Vector2& v) {
    return Vector2(v[0] * k, v[1] * k);
}

Vector2 operator/(const Vector2& v, const double k) {
    return Vector2(v[0] / k, v[1] / k);
}

Vector2 operator+(const Vector2& v1, const Vector2& v2) {
    return Vector2(v1[0] + v2[0], v1[1] + v2[1]);
}

Vector2 operator-(const Vector2& v1, const Vector2& v2) {
    return Vector2(v1[0] - v2[0], v1[1] - v2[1]);
}

Vector2& Vector2::operator*=(const double k) {
    return *this = (*this * k);
}

Vector2& Vector2::operator/=(const double k) {
    return *this = (*this / k);
}

Vector2& Vector2::operator+=(const Vector2& v) {
    return *this = (*this + v);
}

Vector2& Vector2::operator-=(const Vector2& v) {
    return *this = (*this - v);
}

double dot_product(const Vector2& v1, const Vector2& v2) {
    return v1[0] * v2[0] + v1[1] * v2[1];
}

double Vector2::norm() const {
    return sqrt(_coords[0] * _coords[0] + _coords[1] * _coords[1]);
}

double Vector2::squared_norm() const {
    return (_coords[0] * _coords[0] + _coords[1] * _coords[1]);
}

Vector2 Vector2::normalized() {
    Vector2 res;
    double ni = 1.0 / norm();
    res[0] *= ni;
    res[1] *= ni;
    return res;
}

void Vector2::normalize() {
    double ni = 1.0 / norm();
    _coords[0] *= ni;
    _coords[1] *= ni;
}

Vector2 unitVector(const Vector2 &v) {
    return v / v.norm();
}

std::ostream& operator<<(std::ostream &os, const Vector2 &v) {
    return os << "(" << v[0] << "; " << v[1] << ")";
}

std::istream& operator>>(std::istream &is, Vector2 &v) {
    return is >> v._coords[0] >> v._coords[1];
}
