#ifndef VECTEUR3_H_
#define VECTEUR3_H_

#include <iostream>


class Vector3 {
public:
    //the 3 coordinates
    // [0] = x, [1] = y, [2]=z
    double _coords[3];

    Vector3(double x = 0, double y = 0, double z = 0);
    Vector3(const Vector3& vector);
    virtual ~Vector3();

    double operator[](int i) const;
    double& operator[](const int& i);

    friend bool operator==(const Vector3& vector1, const Vector3& vector2);
    friend bool operator!=(const Vector3& vector1, const Vector3& vector2);

    const Vector3& operator+() const;
    Vector3 operator-() const;

    Vector3& operator=(const Vector3& vector);

    friend Vector3 operator+(const Vector3& vector1, const Vector3& vector2);
    friend Vector3 operator-(const Vector3& vector1, const Vector3& vector2);
    friend Vector3 operator*(const Vector3& vector, const double k);
    friend Vector3 operator*(const double k, const Vector3& vector);
    friend Vector3 operator/(const Vector3& vector, const double k);

    Vector3& operator*=(const double k);
    Vector3& operator/=(const double k);
    Vector3& operator+=(const Vector3& vector);
    Vector3& operator-=(const Vector3& vector);

    friend double dot_product(const Vector3& vector1, const Vector3& vector2);
    friend Vector3 cross_product(const Vector3& vector1, const Vector3& vector2);
    friend double triple_product(const Vector3& vector1, const Vector3& vector2, const Vector3& vector3);

    double norm() const;
    double squared_norm() const;
    Vector3& normalize();
    Vector3 normalized() const;
    //friend Vector3 unitVector(const Vector3& vector); OBSOLETE

    double min_coord() const;
    double max_coord() const;
    double min_abs_coord() const;
    double max_abs_coord() const;
    int index_min_coord() const;
    int index_max_coord() const;
    int index_min_abs_coord() const;
    int index_max_abs_coord() const;

    friend Vector3 minVect(const Vector3& vector1, const Vector3& vector2);
    friend Vector3 maxVect(const Vector3& vector1, const Vector3& vector2);

    friend std::ostream& operator<<(std::ostream& os, const Vector3& vector);
    friend std::istream& operator>>(std::istream& is, Vector3& vector);
};

#endif /* VECTEUR3_H_ */
