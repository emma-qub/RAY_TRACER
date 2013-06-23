#include "Trinome.h"

Trinome::Trinome(int dx, int dy, int dz, double coeff) :
    _dx(dx),
    _dy(dy),
    _dz(dz),
    _coeff(coeff) {
}

std::ostream& operator<<(std::ostream& os,const Trinome& trinome) {
    return os << trinome._coeff<< ".x^" << trinome._dx
              << "y^" << trinome._dy
              << "z^" << trinome._dz
              << std::endl;
}
