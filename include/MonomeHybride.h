#ifndef MONOMEHYBRIDE_H
#define MONOMEHYBRIDE_H

#include "MonomeSimple.h"
#include "MonomeTrigo.h"

//Un monôme hybride est le produit d'un monôme simple et d'un monôme trigonométrique
class MonomeHybride
{
    public:
        MonomeHybride();
        MonomeHybride(MonomeSimple _monomeSimple);
        MonomeHybride(MonomeSimple _monomeSimple, MonomeTrigo _monomeTrigo);

        MonomeSimple GetmonomeSimple() { return monomeSimple; }
        MonomeTrigo GetmonomeTrigo() { return monomeTrigo; }

        string toString() const;

        double calculer(double value) const;

    private:
        MonomeSimple monomeSimple;
        MonomeTrigo monomeTrigo;
        bool isHybride; //si isHybride = false, alors le monôme n'est qu'un monôme simple
};

#endif // MONOMEHYBRIDE_H
