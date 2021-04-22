#include "PolynomeSimple.h"

PolynomeSimple::PolynomeSimple()
{
    std::vector<MonomeSimple> monomes;
}

void PolynomeSimple::addMonomeSimple(MonomeSimple _monomeSimple)
{
    monomes.push_back(_monomeSimple);
}

double PolynomeSimple::calculer(double value) const //On calcule la somme de tous les monômes en value
{
    double output(0.0);
    for (int i = 0 ; i < monomes.size() ; i++) {
        output += monomes[i].calculer(value);
    }
    return output;
}
