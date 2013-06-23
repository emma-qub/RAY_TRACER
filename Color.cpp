#include "Color.h"
//#include <stdint.h>

Color::Color(double r/*= 0.0*/, double g/*= 0.0*/, double b/*= 0.0*/) {
    _val[0] = r;
    _val[1] = g;
    _val[2] = b;
}

Color::Color(const Color &color) {
    *this = color;
}

Color::~Color() {
}

double& Color::operator[](unsigned i) {
    return _val[i];
}

double Color::operator[](unsigned i) const {
    return _val[i];
}

bool operator==(const Color &color1, const Color &color2) {
    return color1[0] == color2[0] && color1[1] == color2[1] && color1[2] == color2[2];
}

bool operator!=(const Color &color1, const Color &color2) {
    return !(color1 == color2);
}

const Color& Color::operator+() const {
    return *this;
}

Color Color::operator-() const {
    return Color(-_val[0], -_val[1], -_val[2]);
}

Color& Color::operator=(const Color &color) {
    _val[0] = color[0];
    _val[1] = color[1];
    _val[2] = color[2];
    return *this;
}

Color operator+(const Color &color1, const Color &color2) {
    return Color(color1[0] + color2[0], color1[1] + color2[1], color1[2] + color2[2]);
}

Color operator*(const Color &color1, const Color &color2) {
    return Color(color1[0] * color2[0], color1[1] * color2[1], color1[2] * color2[2]);
}

Color operator/(const Color &color1, const Color &color2) {
    return Color(color1[0] / color2[0], color1[1] / color2[1], color1[2] / color2[2]);
}

Color operator*(const double k, const Color &color) {
    return Color(color[0] * k, color[1] * k, color[2] * k);
}

Color operator*(const Color &color, const double k) {
    return Color(color[0] * k, color[1] * k, color[2] * k);
}

Color operator/(const Color &color, const double k) {
    return Color(color[0] / k, color[1] / k, color[2] / k);
}

Color& Color::operator+=(const Color &color) {
    return *this = *this + color;
}

Color& Color::operator*=(const Color &color) {
    return *this = *this * color;
}

Color& Color::operator/=(const Color &color) {
    return *this = *this / color;
}

Color& Color::operator*=(const double k) {
    return *this = *this * k;
}

Color& Color::operator/=(const double k) {
    return *this = *this / k;
}

void Color::clamp() {
    if (_val[0] < 0)
        _val[0] = 0;
    if (_val[1] < 0)
        _val[1] = 0;
    if (_val[2] < 0)
        _val[2] = 0;

    if (_val[0] > 1)
        _val[0] = 1;
    if (_val[1] > 1)
        _val[1] = 1;
    if (_val[2] > 1)
        _val[2] = 1;
}

std::ostream& operator<<(std::ostream &os, const Color &color) {
    return os << "rgb(" << color[0] << ", " << color[1] << ", " << color[2] << ")";
}

/*
 Improvement:

 uint32_t Color::getRGB () const
 {
 uint32_t res = 0;
 res |= (int(_val[0]*255) & 0xff) << 16;
 res |= (int(_val[1]*255) & 0xff) << 8;
 res |= (int(_val[2]*255) & 0xff);
 return res;
 }
 */
