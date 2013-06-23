#ifndef TEXTURE_H
#define TEXTURE_H

#include "Vector2.h"
#include "Vector3.h"
#include "Color.h"

class Texture {
public:
    Texture();
    virtual ~Texture();

    virtual Color value(const Vector2& uv, const Vector3& ptIntersection) const = 0;
};

#endif // TEXTURE_H
