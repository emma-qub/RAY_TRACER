#include "Box.h"

#include <cmath>
#include <algorithm>

Box::Box(const Color& color, const Material& material, const Vector3& bottomLeftFrontCorner, const Vector3& topRightBackCorner) :
    Shape(color, material),
    _bottomLeftFrontCorner(bottomLeftFrontCorner),
    _topRightBackCorner(topRightBackCorner) {

    double minX = min(bottomLeftFrontCorner[0], topRightBackCorner[0]);
    double maxX = max(bottomLeftFrontCorner[0], topRightBackCorner[0]);
    double minY = min(bottomLeftFrontCorner[1], topRightBackCorner[1]);
    double maxY = max(bottomLeftFrontCorner[1], topRightBackCorner[1]);
    double minZ = min(bottomLeftFrontCorner[2], topRightBackCorner[2]);
    double maxZ = max(bottomLeftFrontCorner[2], topRightBackCorner[2]);

    double meanX = (maxX + minX) / 2;
    double meanY = (maxY + minY) / 2;
    double meanZ = (maxZ + minZ) / 2;

    double width = maxX - minX;
    double height = maxY - minY;
    double length = maxZ - minZ;

    if (width != 0 && height != 0 && length != 0) {
        _faces.push_back(Rectangle(color, material, Ray(Vector3(maxX, meanY, meanZ), Vector3(1, 0, 0)), length, height));
        _faces.push_back(Rectangle(color, material, Ray(Vector3(minX, meanY, meanZ), Vector3(-1, 0, 0)), length, height));
        _faces.push_back(Rectangle(color, material, Ray(Vector3(meanX, maxY, meanZ), Vector3(0, 1, 0)), length, width));
        _faces.push_back(Rectangle(color, material, Ray(Vector3(meanX, minY, meanZ), Vector3(0, -1, 0)), length, width));
        _faces.push_back(Rectangle(color, material, Ray(Vector3(meanX, meanY, maxZ), Vector3(0, 0, 1)), height, width));
        _faces.push_back(Rectangle(color, material, Ray(Vector3(meanX, meanY, minZ), Vector3(0, 0, -1)), height, width));
    }
}

Box::Box(const Box& box) :
    Shape(box._color, box._material) {
    _faces = box._faces;
}

Box::~Box() {
}

Vector3 Box::normal(const Vector3& ptIntersect) const {
    for (unsigned int i = 0; i < _faces.size(); i++) {
        Rectangle currFace = _faces.at(i);
        if (currFace.belongsTo(ptIntersect)) {
            return currFace.normal(ptIntersect);
        }
    }
}

std::vector<double> Box::ensIntersect(const Ray& rayon) const {
    vector<double> res;

    for (unsigned int i = 0; i < _faces.size(); i++) {
        vector<double> currInter = _faces.at(i).ensIntersect(rayon);
        if (currInter.size() == 1) {
            res.push_back(currInter.at(0));
        }
    }

    sort(res.begin(), res.end());
    return res;
}

bool Box::belongsTo(const Vector3& ptIntersect) const {
    return false;
}

Shape* Box::clone() const {
    return new Box(*this);
}
