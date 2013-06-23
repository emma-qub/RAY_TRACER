#ifndef TRINOME_H
#define TRINOME_H

#include <iostream>

class Trinome {

public:
    int _dx;
    int _dy;
    int _dz;
    double _coeff;

    Trinome(int dx, int dy, int dz, double coeff = 1);

    friend std::ostream& operator<<(std::ostream& os, const Trinome& trinome);
};

#endif // TRINOME_H
