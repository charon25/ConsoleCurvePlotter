#ifndef MONOMETRIGO_H
#define MONOMETRIGO_H

#include "MonomeSimple.h"
#include "PolynomeSimple.h"
#include "math.h"


//Un monôme trigonométrique est un cosinus ou un sinus appliqué à un polynôme simple
class MonomeTrigo
{
    public:
        MonomeTrigo();
        MonomeTrigo(PolynomeSimple polynome, int type);

        PolynomeSimple Getpolynome() { return polynome; }
        int Gettype() { return type; }

        string toString() const;

        double calculer(double value) const;

    protected:

    private:
        PolynomeSimple polynome;
        int type; //type = 0 si c'est un cosinus, et n'importe quelle autre valeur si c'est un sinus
};

#endif // MONOMETRIGO_H
