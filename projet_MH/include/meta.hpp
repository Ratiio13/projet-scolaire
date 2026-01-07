// meta_init.hpp

#ifndef META_HPP
#define META_HPP

#include <vector>
#include <string>

#include "traitement_instance.hpp"


// ________________________________________________ UTILITAIRES ____________________________________________________________________________________________________________

/*
Tire un entier selon la loi uniforme sur [a, b] (inclus !).

@input: deux int
@output: un int, compris entre les deux donnés (inclus)
*/
int randint(int a, int b);


/*
Tire un double selon la loi uniforme sur [a, b].

@input: deux doubles
@output: un double, compris entre les deux donnés.
*/
double randdouble(double a, double b);


// ________________________________________________ VOISINAGES ____________________________________________________________________________________________________________

/*
Donne le voisin d'une solution dans la boule de Hamming de taille 1 : on change un et un seul booléen.

@input: un vecteur de booléens caractérisant notre solution : un élément est Vrai ssi l'usine indexée est ouverte.
@output: un vecteur de booléens, voisin de la solution donnée dans la boule de Hamming de taille 1.
*/
std::vector<bool> voisin_1_random (std::vector<bool> &solution);


/*
Donne le voisin d'une solution dans la boule de Hamming de taille 2 : on change exactement deux booléens (distincts).

@input: un vecteur de booléens caractérisant notre solution : un élément est Vrai ssi l'usine indexée est ouverte.
@output: un vecteur de booléens, voisin de la solution donnée dans la boule de Hamming de taille 2.
*/
std::vector<bool> voisin_2_random (std::vector<bool> &solution);


/*
Voisinage inclus dans la boule de Hamming de taille 1 : on ouvre une usine de plus.

@input: un vecteur de booléens caractérisant notre solution : un élément est Vrai ssi l'usine indexée est ouverte.
@output: le même vecteur de booléens, mais dont un 0 est devenu un 1.
    NB : si le vecteur était initialement rempli de 1, le vecteur retourné est identique.
*/
std::vector<bool> voisin_ouverture_random (std::vector<bool> &solution);


/*
Voisinage inclus dans la boule de Hamming de taille 1 : on ferme une des usines ouvertes.

@input: un vecteur de booléens caractérisant notre solution : un élément est Vrai ssi l'usine indexée est ouverte.
@output: le même vecteur de booléens, mais dont un 1 est devenu un 0.
    NB : si le vecteur était initialement rempli de 0, le vecteur retourné est identique.
*/
std::vector<bool> voisin_fermeture_random (std::vector<bool> &solution);


/*
Génère un voisin d'une solution donnée, selon le voisinage spécifié.

@input: une solution (vecteur de booléens) dont on veut un voisin, et le voisinage à explorer (son nom en string).
@output: un vecteur de booléens, voisin de la solution initiale dans le voisinage spécifié.
*/
std::vector<bool> voisin_random (std::vector<bool> &solution, const std::string voisinage);



// ________________________________________________ RECUIT SIMULÉ ____________________________________________________________________________________________________________

/*
Recuit simulé, tel quel présenté dans le cours.

@input:
    - une instance du problème (struct Instance),
    - le voisinage à explorer (un string parmi : "boule1", "boule2", "ouverture", "fermeture"),
    - la température initiale,
    - la température seuil : passer en-dessous est la condition d'arrêt,
    - le nombre de voisins à explorer à chaque température,
    - le coefficient par lequel on fait décroître le température : T = mu.T
@output:
    - la (meilleure) valeur de la fonction objectif à minmiser obtenue,
    - et la solution correspondante (vecteurs de booléens caractérisant les usines ouvertes).
*/
std::pair<double, std::vector<bool>> recuit (Instance inst, const std::string voisinage, double temp_init, double temp_seuil, int nb_iter, double decroiss_lin_temp);
 



// ________________________________________________ TABOO SEARCH ____________________________________________________________________________________________________________

/*
Recherche tabou, telle quel présentée dans le cours.

@input:
    - une instance du problème (struct Instance),
    - la condition d'arrêt : au bout de combien d'itérations sans améliorations on arrête la recherche.
@output:
    - la (meilleure) valeur de la fonction objectif à minmiser obtenue,
    - et la solution correspondante (vecteurs de booléens caractérisant les usines ouvertes).
*/
std::pair<double, std::vector<bool>> taboo (Instance &inst, int max_iter_stuck);




#endif // META_HPP
