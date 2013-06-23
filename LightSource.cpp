#include "LightSource.h"

LightSource::LightSource(double intensity, const Vector3 &position, const Color &color) :
    _intensity(intensity), _position(position) {
    if (color != 0){
        _color = color;
    } else {
        _color = Color(1,1,1);
    }
}

LightSource::~LightSource() {
}

LightSource* LightSource::clone() const {
    return new LightSource(*this);
}
