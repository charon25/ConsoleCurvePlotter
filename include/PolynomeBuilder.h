#ifndef POLYNOMEBUILDER_H
#define POLYNOMEBUILDER_H

#include <iostream>
#include <iomanip>
#include "PolynomeHybride.h"

//Classe pour créer un polynôme hybride à partir d'un string
class PolynomeBuilder
{
    public:
        PolynomeBuilder();

        static PolynomeHybride createFromString(std::string str);
        static MonomeSimple createMonomeSimpleFromString(std::string str);
    private:
};

#endif // POLYNOMEBUILDER_H
