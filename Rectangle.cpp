#include "Rectangle.h"
#include <cmath>
#include <iostream>

Rectangle::Rectangle(const Color &color, const Material &material, const Ray &normAndPoint, double height, double width) :
    Plane(color, material, normAndPoint), _height(height), _width(width) {
}

Rectangle::~Rectangle() {
}

std::vector<double> Rectangle::ensIntersect(const Ray &rayon) const {
    std::vector<double> res;

    Vector3 direction = _normAndPoint[1];
    Vector3 origin = _normAndPoint[0];

    double t = (_d - direction[0]*rayon[0][0] - direction[1]*rayon[0][1] - direction[2]*rayon[0][2])
              /(direction[0]*rayon[1][0] + direction[1]*rayon[1][1] + direction[2]*rayon[1][2]);

    Vector3 inter = rayon.getPoint(t);

    // Rectangle with norm like (1, 0, 0)
    if (direction[1] == 0 && direction[2] == 0) {
        if ((fabs(inter[1]-origin[1]) < _width/2.0
          && fabs(inter[2]-origin[2]) < _height/2.0)
          && t > 0) {
            res.push_back(t);
        }
    } // Rectangle with norm like (0, 0, 1)
    else if (direction[0] == 0 && direction[1] == 0) {
        if ((fabs(inter[0]-origin[0]) < _width/2.0
          && fabs(inter[1]-origin[1]) < _height/2.0)
          && t > 0) {
            res.push_back(t);
        }
    } // Otherwise, including with norm like (0, 1, 0)
    else {
        if ((fabs(inter[0]-origin[0]) < _width/2.0
          && fabs(inter[2]-origin[2]) < _height/2.0)
          && t > 0) {
            res.push_back(t);
        }
    }

    return res;
}

bool Rectangle::belongsTo(const Vector3& ptIntersect) const {
    if (Plane::belongsTo(ptIntersect)) {
        Vector3 direction = _normAndPoint[1];
        Vector3 origin = _normAndPoint[0];

        // Rectangle with norm like (1, 0, 0)
        if (direction[1] == 0 && direction[2] == 0) {
            if ((fabs(ptIntersect[1]-origin[1]) < _width/2.0
              && fabs(ptIntersect[2]-origin[2]) < _height/2.0)) {
                return true;
            }
        } // Rectangle with norm like (0, 0, 1)
        else if (direction[0] == 0 && direction[1] == 0) {
            if ((fabs(ptIntersect[0]-origin[0]) < _width/2.0
              && fabs(ptIntersect[1]-origin[1]) < _height/2.0)) {
                return true;
            }
        } // Otherwise, including with norm like (0, 1, 0)
        else {
            if ((fabs(ptIntersect[0]-origin[0]) < _width/2.0
              && fabs(ptIntersect[2]-origin[2]) < _height/2.0)) {
                return true;
            }
        }
    }

    return false;
}

Rectangle* Rectangle::clone() const {
    return new Rectangle(*this);
}

std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle) {
    return os << rectangle._color << std::endl
              << rectangle._material << std::endl
              << rectangle._normAndPoint << std::endl
              << rectangle._height << std::endl
              << rectangle._width;
}
