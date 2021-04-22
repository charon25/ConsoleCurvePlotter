#include "PolynomeBuilder.h"

PolynomeBuilder::PolynomeBuilder()
{
    //ctor
}

PolynomeHybride PolynomeBuilder::createFromString(std::string str)
{
    regex polynomeRgx("([+-]?[^-+]+)"); //Permet de découper le string selon les symboles + et -
    smatch matchPoly;
    int type;
    MonomeSimple monomeSimple;
    PolynomeSimple polynomeSimple;
    int trigoState(0); //Variable qui permet de savoir si le monôme en train d'être analysé est dans un cos ou un sin
    if ((str.find("cos") != string::npos) || (str.find("sin") != string::npos)) { //Si le string contient au moins un cos ou un sin
        PolynomeHybride polynome;
        while (str.length() > 0) { //Tant que le string contient des caractères
            if (regex_search(str, matchPoly, polynomeRgx)) { //On récupère le premier monôme
                string s(matchPoly[0].str());
                if ((s.find("cos") != string::npos) || (str.find("sin") != string::npos)) { //Si il contient cos ou sin
                    if (s.find("cos") != string::npos) { //On associe le type en fonction de si c'est un cos ou un sin
                        type = 0;
                    } else {
                        type = 1;
                    }
                    trigoState = 1;
                    polynomeSimple = PolynomeSimple();
                    if (s.find("*") != string::npos) { //Si le monôme contient un * (donc de la forme <monome>*cos(<polynome>))
                        string s2(s.substr(0, s.find("*")));
                        monomeSimple = createMonomeSimpleFromString(s2); //On crée un monome à partir de ce qui est avant la fonction trigo
                    } else { //Sinon, selon le signe, on crée un monôme de la forme 1 ou -1
                        if (s.substr(0, 1) == "-") {
                            monomeSimple = MonomeSimple(-1, 0);
                        } else {
                            monomeSimple = MonomeSimple(1, 0);
                        }
                    }
                    string s3(s.substr(s.find("(") + 1, s.find(")")));
                    polynomeSimple.addMonomeSimple(createMonomeSimpleFromString(s3)); //On crée le premier monôme contenu dans le cos ou le sin
                    if (s3.find(")") != string::npos) {
                        polynome.addMonomeHybride(MonomeHybride(monomeSimple, MonomeTrigo(polynomeSimple, type)));
                    }
                } else {
                    //Si le monôme ne contient pas cos ou sin, alors c'est un monôme simple et on le crée, et on l'ajoute à la bonne liste en fonction de si on se trouve dans un cos ou un sin ou pas
                    if (s.find(")") != string::npos) {
                        trigoState = 2;
                        s.pop_back();
                    }
                    MonomeSimple monome = createMonomeSimpleFromString(s);
                    if (trigoState == 0) {
                        polynome.addMonomeHybride(MonomeHybride(monome));
                    } else if (trigoState == 1) {
                        polynomeSimple.addMonomeSimple(monome);
                    } else {
                        polynomeSimple.addMonomeSimple(monome);
                        polynome.addMonomeHybride(MonomeHybride(monomeSimple, MonomeTrigo(polynomeSimple, type)));
                        trigoState = 0;
                    }
                }
                str.erase(0, matchPoly[0].length());
            }
        }
        return polynome;
    } else { //Si la fonction ne contient ni cos ni sin, on crée juste tous les monômes un par un
        PolynomeHybride polynome;
        while (str.length() > 0) {
            if(regex_search(str, matchPoly, polynomeRgx)) {
                string s(matchPoly[0].str());
                polynome.addMonomeHybride(MonomeHybride(createMonomeSimpleFromString(s)));
                str.erase(0, matchPoly[0].length());
            }
        }
        return polynome;
    }
}


MonomeSimple PolynomeBuilder::createMonomeSimpleFromString(std::string s) //Permet de créer un monôme simple à partir d'un string
{
    regex monomeRgx("(\\+|-|)?([0-9.]*)x(\\^([0-9]+))?");
    regex constRgx("([+-]?)([0-9.]+)");
    smatch matchMono;
    if (regex_search(s, matchMono, monomeRgx)) {
        return MonomeSimple().createFromRegexMatch(matchMono, false);
    }else if (regex_search(s, matchMono, constRgx)) {
        return MonomeSimple().createFromRegexMatch(matchMono, true);
    }
    return MonomeSimple(0, 1);
}
