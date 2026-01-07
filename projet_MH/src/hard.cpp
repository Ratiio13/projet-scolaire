//#include <iostream>
#include <vector>
//#include <string>
#include <limits> // pour +infty
//#include <numeric> // pour std::inner_product
#include <random>
//#include <cmath>
#include <stdexcept>

#include "traitement_instance.hpp"
#include "hard.hpp"
#include "meta.hpp"

using namespace std;


// ________________________________________________ PROBLÈME (plus) COMPLEXE ________________________________________________________________________________________________



/*
Une heuristique initiale ayant pour but de minimiser le coût total, quitte à largement violer les contraintes de capacités.
Principe : comme pour la version du problème sans capacités, on place chaque client là où c'est le moins cher.

@input: une instance du problème (avec capacités),
@output: une solution (affectations des clients aux usines) et son coût_total associé.
*/
pair<double, Solution_hard> glouton_hard (Instance_hard &inst){
    // On initialise le cout_total (ie la valeur à minimiser) et le vecteur d'usines ouvertes.
    double cout_total = 0;
    //vector<vector<bool>> affectations(inst.nb_clients, vector<bool>(inst.nb_usines, false));
    Solution_hard solution(inst.nb_clients, inst.nb_usines, inst.capacites);
    // Et on fait une copie des prix d'ouverture des usines, pour ne pas les perdre malgré les modifications du vecteur à venir.
    vector<double> prix_ouv_cp(inst.prix_ouverture);
    //vector<int> capac_cp(inst.capacites);
    //solution.capacites = inst.capacites;

    // Pour chaque client i, on cherche dans quelle usine j il est le moins cher de le placer.
    // Pour ça, pour chaque client i,
    for (int i = 0; i < inst.nb_clients; i++){
        // on cherche l'usine j qui minimise (prix_ouverture[j] + prix_affectation[i][j]).
        // C'est une recherche de minimum dans une liste, donc on initialise un candidat à +infty, et la position à 0,
        double min_candidat = numeric_limits<double>::infinity();
        int pos_candidat = -1;

        for (int j = 0; j < inst.nb_usines; j++){
            double val_j = prix_ouv_cp[j] + inst.prix_affectation[i][j];
            // et pour chaque usine j, on actualise notre candidat et sa position si l'usine j permet de placer le client i à un meilleur prix.
            if (val_j < min_candidat && solution.capacites[j] >= inst.demandes[i]){
                min_candidat = val_j;
                pos_candidat = j;
            }
        }
        // En sortie de boucle, min_candidat contient bien le prix minimum pour placer le client i,
        // et pos_candidat l'indice de l'usine où le placer pour payer ce prix minimum.
        if (pos_candidat == -1){
            throw std::runtime_error("\n!!! Aucune usine n'a pu satisfaire la demande d'un client");
        }

        // On ajoute donc ce prix au coût total.
        cout_total += min_candidat;  
        // l'usine 'indice' vient d'être ouverte, donc on met son cout d'ouverture à 0 pour la suite.
        // Puisque l'usine pos_candidat vient d'être ouverte, on l'indique dans le vecteur de booléens correspondant,
        solution.affectations[i][pos_candidat] = true;
        // et on met son prix d'ouverture à 0 pour les prochains clients.
        prix_ouv_cp[pos_candidat] = 0; 
        solution.capacites[pos_candidat] -= inst.demandes[i];
    }

    // En sortie de boucle, on a sommé les coûts minimaux (locaux) pour chaque client, 
    // et dressé la liste des usines à ouvrir.
    // On affiche le prix total,
    //cout << "Glouton cout_total = " << cout_total << "\n";
    // et retourne la liste des usines ouvertes.
    return make_pair(cout_total, solution);
}





/*
Fonction d'évaluation du coût total d'une solution : somme des coûts d'ouverture des usines utilisées 
et d'affectations des clients placés.

@input:
    - une instance du problème (version avec capacités),
    - une solution (affectations des clients aux usines).
@output:
    - un double : le coût total de la solution.
*/
double evaluation_hard (Instance_hard inst, Solution_hard solution){
    vector<bool> usines_ouvertes(inst.nb_usines, false);
    double cout_sol = 0.0;
    for (int i = 0; i < inst.nb_clients; i++){
        for (int j = 0; j < inst.nb_usines; j++){
            if (solution.affectations[i][j]){
                usines_ouvertes[j] = true;
                cout_sol += inst.prix_affectation[i][j];
            }
        }
    }
    for (int j = 0; j < inst.nb_usines; j++){
        if (usines_ouvertes[j]){
            cout_sol += inst.prix_ouverture[j];
        }
    }
    return cout_sol;
}


/*
Retourne le voisinage d'une solution donnée selon l'idée intuitive : "on déplace 1 client".
@input:
    - une instance du problème (version avec capacités),
    - une solution (affectations des clients aux usines).
@output:
    - une sorte de liste d'adjacence : 
      une liste regroupant, pour chaque client, la liste des usines pouvant accueillir sa demande.
*/
vector<vector<int>> voisinage_hard (Instance_hard &inst, Solution_hard solution){
    vector<vector<int>> voisinage(inst.nb_clients);
    for (int i = 0; i < inst.nb_clients; i++){
        for (int j = 0; j < inst.nb_usines; j++){
            if (solution.affectations[i][j] == 0 && solution.capacites[j] >= inst.demandes[i]){
                voisinage[i].push_back(j);
            }
        }
    }
    return voisinage;
}


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
Solution_hard voisin_hard_client_random (Instance_hard &inst, Solution_hard &solution) {
    vector<vector<int>> voisinage = voisinage_hard(inst, solution);
    int i = randint(0, voisinage.size() - 1);
    int j = voisinage[i][randint(0, voisinage[i].size() - 1)];
    Solution_hard voisin(solution);
    int ancienne_usine = 0;
    while (voisin.affectations[i][ancienne_usine] != 1){
        ancienne_usine++;
    }
    voisin.affectations[i][ancienne_usine] = 0;
    voisin.affectations[i][j] = 1;
    voisin.capacites[ancienne_usine] += inst.demandes[i];
    voisin.capacites[j] -= inst.demandes[i];
    return voisin;
}


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
Solution_hard voisin_hard_full_random (Instance_hard &inst, Solution_hard &solution) {
    vector<vector<int>> voisinage = voisinage_hard(inst, solution);
    int nb_elem = 0;
    for (int i = 0; i < static_cast<int>(voisinage.size()); i++){
        nb_elem += voisinage[i].size();
    }
    int elem = randint(1, nb_elem);
    int i = 0, j = elem;
    while (j - voisinage[i].size() > 0){
        j -= voisinage[i].size();
        i++;
    }
    j -= 1;

    Solution_hard voisin(solution);
    int ancienne_usine = 0;
    while (voisin.affectations[i][ancienne_usine] != 1){
        ancienne_usine++;
    }
    voisin.affectations[i][ancienne_usine] = 0;
    voisin.affectations[i][j] = 1;
    voisin.capacites[ancienne_usine] += inst.demandes[i];
    voisin.capacites[j] -= inst.demandes[i];
    return voisin;
}


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
pair<double, Solution_hard> recuit_hard (Instance_hard inst, double temp_init, double temp_seuil, int nb_iter, double decroiss_lin_temp){
    auto [meilleur_cout, meilleure_sol] = glouton_hard(inst);
    double temp = temp_init;
    Solution_hard actuelle_sol = meilleure_sol;
    double actuel_cout = meilleur_cout;
    while (temp > temp_seuil){
        for (int i = 0; i < nb_iter; i++){
            Solution_hard voisin = voisin_hard_client_random(inst, actuelle_sol);
            double nouveau_cout = evaluation_hard(inst, voisin);
            double delta = nouveau_cout - actuel_cout;
            if (delta <= 0){
                actuelle_sol = voisin;
                actuel_cout = nouveau_cout;
                if (nouveau_cout < meilleur_cout){
                    meilleur_cout = nouveau_cout;
                    meilleure_sol = actuelle_sol;
                    //cout << "meilleur : " << meilleur_cout << "\n";
                }
            } 
            else {
                double q = randdouble(0.0, 1.0);
                if (q <= exp(- delta / temp)){
                    actuelle_sol = voisin;
                    actuel_cout = nouveau_cout;
                }
            }
        }
        temp *= decroiss_lin_temp;
    }
    return make_pair(meilleur_cout, meilleure_sol);
}
