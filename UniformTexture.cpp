#include "UniformTexture.h"

UniformTexture::UniformTexture(const Color &color) :
    _color(color) {
}

UniformTexture::~UniformTexture() {
}

Color UniformTexture::value(const Vector2& uv, const Vector3& ptIntersection) const {
    return _color;
}
