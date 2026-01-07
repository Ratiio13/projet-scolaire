//#include <iostream>
#include <vector>
//#include <string>
#include <limits> // pour +infty
//#include <numeric> // pour std::inner_product
//#include <random>
//#include <cmath>
#include <algorithm>

#include "traitement_instance.hpp"
#include "penalite.hpp"
//#include "hard.hpp"
//#include "meta.hpp"

using namespace std;



/*
Fonction d'évaluation du viol total d'une solution, ie la somme des dépacements des capacités des usines.
Exemple : si une usine a pour capacité 10 mais qu'elle accueille deux clients avec pour demandes respectives 5 et 15,
son viol est de 5+15-10 = 10.

@input:
    - une instance du problème (version avec capacités),
    - une solution
@output:
    - un int : le viol total de la solution.
*/
int calcul_viol (Instance_hard &inst, Solution_hard &solution){
    int viol_total = 0;
    // On somme les viols de chaque usine, ie : (son occupation - sa capacité).
    for (int j = 0; j < inst.nb_usines; j++){
        int occupation_j = 0;
        for (int i = 0; i < inst.nb_clients; i++){
            if (solution.affectations[i][j]){
                occupation_j += inst.demandes[i];
            }
        }
        if (occupation_j > inst.capacites[j]){
            viol_total += occupation_j - inst.capacites[j];
        }
    }
    return viol_total;
}


/*
Fonction d'évaluation du coût total d'une solution : somme des coûts d'ouverture des usines utilisées 
et d'affectations des clients placés.

@input:
    - une instance du problème (version avec capacités),
    - une solution
@output:
    - un double : le coût total de la solution.
*/
double calcul_cout (Instance_hard inst, Solution_hard solution){
    vector<bool> usines_ouvertes(inst.nb_usines, false);
    double cout_total = 0.0;
    // On parcourt la matrice d'affectation de la solution, et on somme les coûts.
    for (int i = 0; i < inst.nb_clients; i++){
        for (int j = 0; j < inst.nb_usines; j++){
            if (solution.affectations[i][j]){
                cout_total += inst.prix_affectation[i][j];
                // On note également quelles usines sont ouvertes, pour ajouter leur coût d'ouverture.
                usines_ouvertes[j] = true;
            }
        }
    }
    // En sortie de boucle, 'c'out_total' contient la somme des coût d'affectation, 
    // et il ne reste qu'à ajouter les coûts d'ouverture des usines utilisées.
    for (int j = 0; j < inst.nb_usines; j++){
        if (usines_ouvertes[j]){
            cout_total += inst.prix_ouverture[j];
        }
    }
    return cout_total;
}


/*
Une heuristique initiale ayant pour but de minimiser le viol total de la solution.
Principe : on place les clients par ordre décroissant de leur demande (le plus "gros" en premier),
    et on les place dans l'usine à la plus grande capacité.

@input: une instance du problème (avec capacités),
@output: une solution (affectations des clients aux usines).
*/
Solution_hard glouton_prudent (Instance_hard &inst){
    Solution_hard solution(inst.nb_clients, inst.nb_usines, inst.capacites);

    // On tri les clients par ordre décroissant de demande :
    vector<pair<int, int>> demandes_indices(inst.nb_clients);
    for (int i = 0; i < inst.nb_clients; i++){
        demandes_indices[i] = make_pair(inst.demandes[i], i);
    }
    sort(demandes_indices.rbegin(), demandes_indices.rend());
    // A i fixé, demandes_indices[i].first est la ième plus grosse demande, et demandes_indices[i].second le client correspondant. 

    // On tri les usines par ordre décroissant de capacité :
    vector<pair<int, int>> capacites_indices(inst.nb_usines);
    for (int j = 0; j < inst.nb_usines; j++){
        capacites_indices[j] = make_pair(inst.capacites[j], j);
    }
    sort(capacites_indices.rbegin(), capacites_indices.rend());
    // A j fixé, capacites_indices[i].first est la jème plus grosse caapcité, et capacites_indices[i].second l'usine correspondante. 

    // On parcourt les clients par ordre décroissant de demande. Pour chaque client i :
    for (int i = 0; i < inst.nb_clients; i++){
        // on va essayer de placer i dans l'usine j à la plus grosse capacité.
        int j = 0;
        bool i_place = false;
        while (!i_place && j < inst.nb_usines){
            // Si la jème usine convient, on y place le ième client (et déduit sa demande la capacité),
            if (capacites_indices[j].first >= demandes_indices[i].first){
                solution.affectations[demandes_indices[i].second][capacites_indices[j].second] = true;
                capacites_indices[j].first -= demandes_indices[i].first;
                solution.capacites[capacites_indices[j].second] -= demandes_indices[i].first;
                i_place = true;
            }
            // sinon on passe à l'usine suivante (dans l'ordre décroissant des capacités).
            else {
                j++;
            }
        }
        
        // Si aucune usine n'a pu accueillir le ième client, sa demande est violée et on l'ajoute au compteur de viol global.
        if (j == inst.nb_usines){
            solution.viol += demandes_indices[i].first;
        }
    }

    return solution;
}


/*
Une heuristique initiale ayant pour but de minimiser le coût total, quitte à largement violer les contraintes de capacités.
Principe : comme pour la version du problème sans capacités, on place chaque client là où c'est le moins cher.

@input: une instance du problème (avec capacités),
@output: une solution (affectations des clients aux usines).
*/
Solution_hard ouverture_viol(Instance_hard &inst){
    Solution_hard solution(inst.nb_clients, inst.nb_usines, inst.capacites);

    // On fait une copie des prix d'ouverture des usines, pour ne pas les perdre malgré les modifications du vecteur à venir.
    vector<double> prix_ouv_cp(inst.prix_ouverture);

    // Pour chaque client i, on cherche dans quelle usine j il est le moins cher de le placer.
    // Pour ça, pour chaque client i,
    for (int i = 0; i < inst.nb_clients; i++){
        // on cherche l'usine j qui minimise (prix_ouverture[j] + prix_affectation[i][j]).
        // C'est une recherche de minimum dans une liste, donc on initialise un candidat à +infty, et la position à 0,
        double min_candidat = numeric_limits<double>::infinity();
        int pos_candidat = 0;

        for (int j = 0; j < inst.nb_usines; j++){
            double val_j = prix_ouv_cp[j] + inst.prix_affectation[i][j];
            // et pour chaque usine j, on actualise notre candidat et sa position si l'usine j permet de placer le client i à un meilleur prix.
            if (val_j < min_candidat){
                min_candidat = val_j;
                pos_candidat = j;
            }
        }
        // En sortie de boucle, min_candidat contient bien le prix minimum pour placer le client i,
        // et pos_candidat l'indice de l'usine où le placer pour payer ce prix minimum.

        // Puisque l'usine pos_candidat vient d'être ouverte, on l'indique dans le vecteur de booléens correspondant,
        solution.affectations[i][pos_candidat] = true;
        // et on met son prix d'ouverture à 0 pour les prochains clients.
        prix_ouv_cp[pos_candidat] = 0; 
    }

    return solution;
}