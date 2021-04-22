#include "MonomeSimple.h"
#include <regex>

MonomeSimple::MonomeSimple(){}

MonomeSimple::MonomeSimple(double _coefficient, int _degre)
{
    coefficient = _coefficient;
    degre = _degre;
}

double MonomeSimple::calculer(double value) const
{
    return coefficient * pow(value, degre);
}

MonomeSimple MonomeSimple::createFromRegexMatch(smatch match, bool isConstant) //Pour créer un polynome à partir d'un match Regex
{
    if (isConstant) { //Si il est constant, on le crée avec un degré nul
        int sign;
        double coeff;
        if (match.str(1) == "-") {sign = -1;}
        else {sign = 1;}
        coeff = createDoubleFromRegexMatch(match);
        return MonomeSimple(sign * coeff, 0);
    } else { //Sinon, on trouve le coefficient et le degré
        int sign, degre;
        double coeff;
        if (match.str(1) == "-") {sign = -1;}
        else {sign = 1;}
        coeff = createDoubleFromRegexMatch(match);
        if (match.str(4) == "") {degre = 1;}
        else {degre = stoi(match.str(4));}
        return MonomeSimple(sign * coeff, degre);
    }
}

double MonomeSimple::createDoubleFromRegexMatch(smatch match) {
    regex doubleRgx("([0-9]+)(\.[0-9]+)?");
    smatch matches;
    string coeff(match.str(2));
    if (coeff == "") {
        return 1.0;
    } else {
        if (regex_search(coeff, matches, doubleRgx)) {
            return stod(matches.str(1) + matches.str(2));
        }
    }
}

string MonomeSimple::toString() const
{
    if (degre == 0) {
        return to_string(coefficient);
    } else {
        return to_string(coefficient) + "x^" + to_string(degre);
    }
}
