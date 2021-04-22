#include "MonomeTrigo.h"

//type = 0 ==> cosinus
//type <> 0 ==> sinus

MonomeTrigo::MonomeTrigo(){}

MonomeTrigo::MonomeTrigo(PolynomeSimple _polynome, int _type)
{
    polynome = _polynome;
    type = _type;
}

double MonomeTrigo::calculer(double value) const
{
    if (type == 0) {
        return cos(polynome.calculer(value));
    } else {
        return sin(polynome.calculer(value));
    }
}
