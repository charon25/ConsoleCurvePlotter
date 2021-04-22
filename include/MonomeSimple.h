#ifndef MONOMESIMPLE_H
#define MONOMESIMPLE_H

#include "math.h"
#include <iostream>
#include <string>
#include <regex>
using namespace std;

//Un monôme simple est un monome de la forme coefficient*x^degre
class MonomeSimple
{
    public:
        MonomeSimple();
        MonomeSimple(double coefficient, int degre);

        double Getcoefficient() { return coefficient; }
        int Getdegre() { return degre; }
        double calculer(double value) const;

        string toString() const;

        static MonomeSimple createFromRegexMatch(smatch match, bool isConstant);
        static double createDoubleFromRegexMatch(smatch match);

    private:
        double coefficient;
        int degre;
};

#endif // MONOMESIMPLE_H
