#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include "Vector3.h"
#include "Color.h"

class LightSource {
public:
    double _intensity;
    Vector3 _position;
    Color _color;

    LightSource(double intensity, const Vector3& position, const Color& color);
    virtual ~LightSource();

    virtual LightSource* clone() const;
};

#endif /* LIGHTSOURCE_H_ */
