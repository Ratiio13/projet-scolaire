// penalite.hpp

#ifndef PENALITE_HPP
#define PENALITE_HPP

//#include <vector>

#include "traitement_instance.hpp"
#include "hard.hpp"




/*
Fonction d'évaluation du viol total d'une solution, ie la somme des dépacements des capacités des usines.
Exemple : si une usine a pour capacité 10 mais qu'elle accueille deux clients avec pour demandes respectives 5 et 15,
son viol est de 5+15-10 = 10.

@input:
    - une instance du problème (version avec capacités),
    - une solution (affectations des clients aux usines).
@output:
    - un int : le viol total de la solution.
*/
int calcul_viol (Instance_hard &inst, Solution_hard &solution);


/*
Fonction d'évaluation du coût total d'une solution : somme des coûts d'ouverture des usines utilisées 
et d'affectations des clients placés.

@input:
    - une instance du problème (version avec capacités),
    - une solution (affectations des clients aux usines).
@output:
    - un double : le coût total de la solution.
*/
double calcul_cout (Instance_hard &inst, Solution_hard &solution);


/*
Une heuristique initiale ayant pour but de minimiser le viol total de la solution.
Principe : on place les clients par ordre décroissant de leur demande (le plus "gros" en premier),
    et on les place dans l'usine à la plus grande capacité.

@input: une instance du problème (avec capacités),
@output: une solution (affectations des clients aux usines).
*/
Solution_hard glouton_prudent (Instance_hard &inst);


/*
Une heuristique initiale ayant pour but de minimiser le coût total, quitte à largement violer les contraintes de capacités.
Principe : comme pour la version du problème sans capacités, on place chaque client là où c'est le moins cher.

@input: une instance du problème (avec capacités),
@output: une solution (affectations des clients aux usines).
*/
Solution_hard ouverture_viol(Instance_hard &inst);







#endif // PENALITE_HPP