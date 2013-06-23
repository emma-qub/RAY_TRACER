#ifndef POLYNOME_H
#define POLYNOME_H

#include <itpp/itbase.h>
#include "Trinome.h"
#include <QVector>

class Polynome {

public:
    int _degree;
    itpp::mat _matrix;

    Polynome(int degree);
    Polynome(const Polynome& polynome);
    virtual ~Polynome();

    void setMatrix(itpp::mat matrix) { _matrix = matrix; }

    void addTrinome(const Trinome& trinome);
    itpp::mat getMatrix(int nu);
    QVector<double> read() const;
    Polynome deriveeX();
    Polynome deriveeY();
    double evaluate(double x, double y, double z = 1);
    friend Polynome operator*(const Polynome& polynome, const Trinome& trinome);

};

#endif // POLYNOME_H
