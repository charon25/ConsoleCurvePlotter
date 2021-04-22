#define NUMBER_OF_POINTS_X 200
#define NUMBER_OF_POINTS_Y 50

#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "PolynomeHybride.h"
#include "PolynomeBuilder.h"

#include <regex>

using namespace std;

void afficherMenu();    //Fonction qui affiche le menu
void selection();       //Pour rediriger vers la bonne fonction
void menuTrace();       //Menu pour tracer une fonction
void afficherRegles();  //Affichage des règles d'écriture des fonctions
void traceFunction(string fonction, double xMin, double xMax);  //Pour tracer une fonction entre xMin et xMax
double dichotomie(PolynomeHybride polynome, double a, double b, bool croissante); //Algortihme de dichotomie pour trouver les zéros d'une fonction
void menuTableau();     //Menu pour afficher un tableau de valeur
void afficherTableauValeur(string fonction, double xMin, double xMax, double pasX); //Pour afficher le tableau de valeur
double arrondi(double x, int n); //Fonction pour arrondir un réel x à n chiffres après la virgule

int main() //On affiche le menu
{
    cout << "\t\t########## TRACEUR DE FONCTIONS ##########" << endl << endl;
    cout << "/!\\ Mettre la console en plein écran pour profiter au maximum de l'expérience /!\\" << endl << endl;
    afficherMenu();
    return 0;
}

void afficherMenu() { //On demande à l'utilisateur ce qu'il veut faire
    cout << "Choisissez votre action : " << endl;
    cout << "\tTracer une fonction : 1" << endl;
    cout << "\tObtenir un tableau de valeur : 2" << endl;
    cout << "\tQuitter : q" << endl;
    selection();
}

void selection() { //Selon son choix, on choisit la bonne action
    cout << "\nVotre choix : ";
    string choix;
    cin >> choix;
    if (choix == "1") {menuTrace();}
    else if (choix == "2") {menuTableau();}
    else if (choix == "q") {}
    else {afficherMenu();}
}

void menuTrace() { //On demande la fonction, et les bornes du tracé de la fonction
    afficherRegles();
    string fonction;
    double xMin, xMax;
    cout << endl << endl << "Votre fonction : ";
    cin >> fonction;
    cout << endl << "Borne inférieure du tracé : ";
    cin >> xMin;
    cout << endl << "Borne supérieure du tracé : ";
    cin >> xMax;
    cout << endl << endl;
    traceFunction(fonction, xMin, xMax);
}

void afficherRegles() {
    cout << "Règles d'écriture des fonctions : " << endl;
    cout << "\tElles doivent être une somme de monomes respectant une des formes suivantes : a, ax, ax^n, cos(<polynome>), sin(<polynome>), ax^n*cos(<polynome>), ax^n*sin(<polynome>)." << endl;
    cout << "\tMerci de respecter l'emplacement des symboles (^, *). 'a' peut être omis pour choisir 1. A l'interieur des cosinus et sinus il faut un polynome non trigonométrique." << endl;
    cout << "\tExemples corrects : " << endl;
    cout << "\t\t3x+x^2" << "\n\t\tcos(3x+1)" << "\n\t\t1+cos(3x+x^3)-sin(x+1)" << endl;
    cout << "\tLe nombre de monomes n'est pas limité." << endl;
}

void traceFunction(string fonction, double xMin, double xMax) {
    PolynomeHybride polynome = PolynomeBuilder().createFromString(fonction); //On crée la fonction à partir du string
    double pasX = (xMax - xMin) / (NUMBER_OF_POINTS_X - 1); //On calcul le pas en fonction du nombre de points (fixé)
    double values[NUMBER_OF_POINTS_X]; //Tableau des valeurs de la fonction
    int k = 0;
    double maximum = polynome.calculer(xMin), minimum = polynome.calculer(xMin);
    vector<double> zerosX;
    vector<double> zeros;
    for (double x = xMin ; x < xMax ; x += pasX) { //On parcours l'intervalle par pas pasX
        values[k] = polynome.calculer(x); //On calcule la valeur
        //On cherche le max et le min
        if (values[k] > maximum) {
            maximum = values[k];
        }
        if (values[k] < minimum) {
            minimum = values[k];
        }
        //Si la fonction change de signe (= on a traversé l'axe des abscisses), on le note
        if (k > 1 && values[k] * values[k - 1] < 0.0) {
            zerosX.push_back(x);
        }
        k++;
    }
    for (int i = 0 ; i < zerosX.size() ; i++) { //Pour tous les zéros, on effectue une dichotomie pour avoir une valeur plus précise
        zeros.push_back(dichotomie(polynome, zerosX[i] - pasX, zerosX[i], true));
    }
    k = 0;
    double pasY = (maximum - minimum) / NUMBER_OF_POINTS_Y; //On calcul le pas vertical
    for (double x = xMin ; x <= xMax ; x += pasX) {
        //On arrondi chaque valeur au multiple entier du pas le plus proche
        if (fmod(values[k], pasY) < pasX / 2.0) {
            values[k] = values[k] - fmod(values[k], pasY);
        } else {
            values[k] = values[k] - fmod(values[k], pasY) + pasY;
        }
        k++;
    }
    cout << "Valeurs de la fonction comprises dans l'intervalle [" << minimum - fmod(minimum, pasY) << " ; " << maximum - fmod(maximum, pasY) + pasY << "]." << endl << endl;
    string lines[NUMBER_OF_POINTS_Y];
    string line;
    string c;
    double y;
    //Création des lignes à afficher
    for (int l = 0 ; l < NUMBER_OF_POINTS_Y ; l++) { //Pour chaque point vertical
        line = "";
        k = 0;
        y = -pasY * l + maximum; //On calcule la valeur actuelle de y
        for (double x = xMin ; x <= xMax ; x += pasX) { //Pour chaque valeur de x entre xMin et xMax
            if (abs(values[k] - y) <= pasY/2) {c = string("·");} //Si on trouve un point aux coordonnées (x, y), on affiche un point
            else {c = string(" ");}                              //Sinon un espace
            if (abs(x - pasX) < pasX/2) {c = "|";}               //Si on est sur l'axe des ordonnées, on affiche |
            if (abs(y - pasY) < pasY/2) {c = "—";}               //Si on est sur l'axe des abscisses, on affiche —
            line += c; //On ajoute le caractère à la ligne
            k++;
        }
        lines[l] = line;
    }
    for (int i = 0 ; i < NUMBER_OF_POINTS_Y ; i++) { //On affiche toutes les lignes
        cout << lines[i] << endl;
    }
    cout << "\nLes zéros de la fonction sur l'intervalle [" << xMin << " ; " << xMax << "] sont (en valeur approchées à 0.0001 près) : " << endl;
    for (int i = 0 ; i < zeros.size() ; i++) { //On affiche tous les zéros
        cout << "\tx = " << arrondi(zeros[i], 4) << endl;
    }
    afficherMenu();
}

double dichotomie(PolynomeHybride polynome, double a, double b, bool croissante) {
    double m;
    for (int k = 0 ; k < 100 ; k++) {
        m = (a + b) / 2;
        if (polynome.calculer(a) * polynome.calculer(m) < 0.0) {
            b = m;
        } else {
            a = m;
        }
    }
    return a;
}

void menuTableau() {
    afficherRegles();
    string fonction;
    double xMin, xMax, pasX;
    cout << endl << endl << "Votre fonction : ";
    cin >> fonction;
    cout << endl << "Borne inférieure : ";
    cin >> xMin;
    cout << endl << "Borne supérieure : ";
    cin >> xMax;
    cout << endl << "Pas : ";
    cin >> pasX;
    cout << endl << endl;
    afficherTableauValeur(fonction, xMin, xMax, pasX);
}

void afficherTableauValeur(string fonction, double xMin, double xMax, double pasX) {
    PolynomeHybride polynome = PolynomeBuilder().createFromString(fonction); //On crée la fonction à partir du string
    for (double x = xMin ; x <= xMax ; x += pasX) { //On affiche toutes les valeurs de x et de f(x) sur l'intervalle avec le pas choisi
        cout << "f(" << arrondi(x, 5) << ") = " << arrondi(polynome.calculer(x), 5) << endl;
    }
    string answer;
    cout << endl << "Voulez-vous l'enregistrer dans un fichier ? (O/N) "; //On demande si l'utilisateur veut l'enregistrer
    cin >> answer;
    if (answer == "O") { //Si oui
        ofstream file("fonction.txt", ios::out | ios::trunc); //On ouvre le flux en écriture
        if (file) {
            for (double x = xMin ; x <= xMax ; x += pasX) {
                file << arrondi(x, 5) << "\t" << arrondi(polynome.calculer(x), 5) << endl; //On écrit x <tabulation> f(x)
            }
            cout << "Ecriture terminée !" << endl << endl;
            file.close(); //On ferme le flux
        } else {
            cout << "Erreur lors de l'écriture !" << endl;
        }
    }
    afficherMenu();
}

double arrondi(double x, int n) {
    return roundf(x * static_cast<double>(pow(10, n))) / static_cast<double>(pow(10, n));
}
