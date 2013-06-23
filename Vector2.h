#ifndef VECTEUR2_H_
#define VECTEUR2_H_

#include <iostream>

class Vector2 {
public:
    //the 2 coordinates
    // [0] = x, [1] = y
    double _coords[2];

    Vector2(double x = 0, double y = 0);
    Vector2(const Vector2 &v1);
    virtual ~Vector2();

    double get_x() const;
    double get_y() const;

    void set_x(double x);
    void set_y(double y);

    double operator[](int i) const;
    double& operator[](const int &i);

    friend bool operator==(const Vector2 &v1, const Vector2 &v2);
    friend bool operator!=(const Vector2 &v1, const Vector2 &v2);

    const Vector2& operator+() const;
    Vector2 operator-() const;

    Vector2& operator=(const Vector2 &v);

    friend Vector2 operator+(const Vector2 &v1, const Vector2 &v2);
    friend Vector2 operator-(const Vector2 &v1, const Vector2 &v2);
    friend Vector2 operator*(const Vector2 &v, const double k);
    friend Vector2 operator*(const double k, const Vector2 &v);
    friend Vector2 operator/(const Vector2 &v, const double k);

    Vector2& operator*=(const double k);
    Vector2& operator/=(const double k);
    Vector2& operator+=(const Vector2 &v);
    Vector2& operator-=(const Vector2 &v);

    friend double dot_product(const Vector2& v1, const Vector2& v2);

    double norm() const;
    double squared_norm() const;
    Vector2 normalized();
    void normalize();
    friend Vector2 unitVector(const Vector2 &v);

    friend std::ostream& operator<<(std::ostream &os, const Vector2 &v);
    friend std::istream& operator>>(std::istream &is, Vector2 &v);
};

#endif /* VECTEUR2_H_ */
