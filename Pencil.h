#ifndef PENCIL_H
#define PENCIL_H

#include <itpp/itbase.h>
#include <vector>
#include "Vector3.h"

class Pencil {

public:
    Pencil(itpp::mat A, itpp::mat B);
    std::vector<double> getGev() const;

private:
    void reduce();
    void getRegular();

public:
    itpp::mat A;
    itpp::mat B;

};

#endif // PENCIL_H
