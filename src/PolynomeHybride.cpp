#include "PolynomeHybride.h"


PolynomeHybride::PolynomeHybride()
{
    std::vector<MonomeHybride> monomes;
}

void PolynomeHybride::addMonomeHybride(MonomeHybride _monomeHybride)
{
    monomes.push_back(_monomeHybride);
}

double PolynomeHybride::calculer(double value) const
{
    double output(0.0);
    for (int i = 0 ; i < monomes.size() ; i++) {
        output += monomes[i].calculer(value);
    }
    return output;
}
