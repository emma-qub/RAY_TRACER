#ifndef RAYON_H_
#define RAYON_H_

#include "Vector3.h"
#include <iostream>

using namespace std;

class Ray {
public:
    // coords[0] is the origin point of the vector
    // coords[1] is the vector's direction from its origin
    Vector3 _coords[2];

    Ray(const Vector3& origin = Vector3(), const Vector3& direction = Vector3());
    Ray(const Ray& ray);
    virtual ~Ray();

    /**
      * \fn Vector3 getPoint(double t) const
      * \brief Value in a point
      *
      * Calculates the point of the ray at parameter t
      *
      * \param t: the parameter
      * \return the point of the ray at parameter t
      */
    Vector3 getPoint(double t) const;

    Vector3 operator[](int i) const;
    Vector3& operator[](const int& i);

    friend ostream& operator<<(ostream& os, const Ray& ray);
};

#endif /* RAYON_H_ */
