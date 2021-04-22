#ifndef POLYNOMEHYBRIDE_H
#define POLYNOMEHYBRIDE_H

#include <vector>
#include "MonomeHybride.h"

//Un polynôme hybride est un ensemble de monômes hybrides
class PolynomeHybride
{
    public:
        PolynomeHybride();

        std::vector<MonomeHybride> Getmonomes() { return monomes; }

        string toString() const;

        void addMonomeHybride(MonomeHybride _monomeHybride);
        double calculer(double value) const;

    private:
        std::vector<MonomeHybride> monomes;
};

#endif // POLYNOMEHYBRIDE_H
