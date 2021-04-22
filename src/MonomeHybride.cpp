#include "MonomeHybride.h"

MonomeHybride::MonomeHybride(){}

MonomeHybride::MonomeHybride(MonomeSimple _monomeSimple, MonomeTrigo _monomeTrigo)
{
    monomeSimple = _monomeSimple;
    monomeTrigo = _monomeTrigo;
    isHybride = true;
}

MonomeHybride::MonomeHybride(MonomeSimple _monomeSimple)
{
    monomeSimple = _monomeSimple;
    isHybride = false;
}

double MonomeHybride::calculer(double value) const //Selon isHybride, on calcule la valeur du monôme hybride
{
    if (isHybride) {
        return monomeSimple.calculer(value) * monomeTrigo.calculer(value);
    } else {
        return monomeSimple.calculer(value);
    }
}
