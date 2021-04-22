#ifndef POLYNOMESIMPLE_H
#define POLYNOMESIMPLE_H

#include <vector>
#include "MonomeSimple.h"

//Un polynôme simple est un ensemble de monôme simple
class PolynomeSimple
{
    public:
        PolynomeSimple();

        std::vector<MonomeSimple> Getmonomes() { return monomes; }

        string toString() const;

        void addMonomeSimple(MonomeSimple _monomeSimple);
        double calculer(double value) const;
    protected:

    private:
        std::vector<MonomeSimple> monomes;
};

#endif // POLYNOMESIMPLE_H
