#ifndef UNIFORMTEXTURE_H
#define UNIFORMTEXTURE_H

#include "Texture.h"

class UniformTexture : public Texture {

public:
    Color _color;

    UniformTexture(const Color& color);
    virtual ~UniformTexture();

    virtual Color value(const Vector2 &uv, const Vector3 &ptIntersection) const;

};

#endif // UNIFORMTEXTURE_H
