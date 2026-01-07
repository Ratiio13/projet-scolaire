// hard_init.hpp

#ifndef HARD_HPP
#define HARD_HPP

#include <vector>

#include "traitement_instance.hpp"
//#include "heuristique_init.hpp"






// ________________________________________________ PROBLÈME (plus) COMPLEXE ________________________________________________________________________________________________



/*
On dédie un Struct à nos solutions, pour porter en une seule variable les informations sur :
- la matrice d'affectation qui caractérise la solution,
- les capacités restantes des usines une fois prises en compte les demandes des clients qu'elles accueillent.
*/
struct Solution_hard {

    // Variables
    std::vector<int> capacites; 
    std::vector<std::vector<bool>> affectations;
    int viol = 0;

    // Constructeur 
    Solution_hard(int clients, int usines, std::vector<int> capac):
        capacites(capac),
        affectations(clients, std::vector<bool>(usines, false))
    {}

};


/*
Une heuristique initiale ayant pour but de minimiser le coût total, quitte à largement violer les contraintes de capacités.
Principe : comme pour la version du problème sans capacités, on place chaque client là où c'est le moins cher.

@input: une instance du problème (avec capacités),
@output: une solution (affectations des clients aux usines) et son coût_total associé.
*/
std::pair<double, Solution_hard> glouton_hard (Instance_hard &inst);


/*
Fonction d'évaluation du coût total d'une solution : somme des coûts d'ouverture des usines utilisées 
et d'affectations des clients placés.

@input:
    - une instance du problème (version avec capacités),
    - une solution (affectations des clients aux usines).
@output:
    - un double : le coût total de la solution.
*/
double evaluation_hard (Instance_hard inst, Solution_hard solution);


/*
Retourne le voisinage d'une solution donnée selon l'idée intuitive : "on déplace 1 client".
@input:
    - une instance du problème (version avec capacités),
    - une solution (affectations des clients aux usines).
@output:
    - une sorte de liste d'adjacence : 
      une liste regroupant, pour chaque client, la liste des usines pouvant accueillir sa demande.
*/
std::vector<std::vector<int>> voisinage_hard (Instance_hard &inst, Solution_hard solution);


/*
Choisit un voisin dans le voisinage ci-dessus, équitablement sur les clients.
- on tire au sort un client (équiprobabilité),
- puis on tire au sort une usine parmi celles pouvant l'accueillir.

@input:
    - une instance du problème (version avec capacités),
    - une solution (affectations des clients aux usines).
@output:
    - une solution voisine.
*/
Solution_hard voisin_hard_client_random (Instance_hard &inst, Solution_hard &solution);


/*
Choisit un voisin dans le voisinage ci-dessus, équitablement sur les voisins possibles.
On liste tous les choix possibles, et on en tire un (équiprobabilité).
Par exemple, si on n'a que deux clients et 5 usines et que :
- le client 1 peut être accueilli dans les usines {1, 3, 4, 5},
- et le client 2 seulement dans {3},
on a 5 voisins possibles : C1->U1, C1->U3, C1->U4, C1->U5 ou C2->U3,
et on en choisit un aléatoirement (une chance sur 5 chacun).

@input:
    - une instance du problème (version avec capacités),
    - une solution (affectations des clients aux usines).
@output:
    - une solution voisine.
*/
Solution_hard voisin_hard_full_random (Instance_hard &inst, Solution_hard &solution);


/*
Recuit simulé, tel quel présenté dans le cours.

@input:
    - une instance du problème (struct Instance_hard),
    - la température initiale,
    - la température seuil : passer en-dessous est la condition d'arrêt,
    - le nombre de voisins à explorer à chaque température,
    - le coefficient par lequel on fait décroître le température : T = mu.T
@output:
    - la (meilleure) valeur de la fonction objectif à minmiser obtenue,
    - et la solution correspondante.
*/
std::pair<double, Solution_hard> recuit_hard (Instance_hard inst, double temp_init, double temp_seuil, int nb_iter, double decroiss_lin_temp);





#endif // hard_HPP