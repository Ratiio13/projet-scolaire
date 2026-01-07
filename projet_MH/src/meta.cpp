//#include <iostream>
#include <vector>
#include <string>
#include <limits> // pour +infty
//#include <numeric> // pour std::inner_product
#include <random>
//#include <cmath>
#include <algorithm>
#include <stdexcept>


#include "traitement_instance.hpp"
#include "heuristique_init.hpp"
#include "meta.hpp"

using namespace std;


// ________________________________________________ UTILITAIRES ____________________________________________________________________________________________________________

/*
Tire un entier selon la loi uniforme sur [a, b] (inclus !).

@input: deux int
@output: un int, compris entre les deux donnés (inclus)
*/
int randint(int a, int b) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(a, b);
    return dist(gen);
}


/*
Tire un double selon la loi uniforme sur [a, b].

@input: deux doubles
@output: un double, compris entre les deux donnés.
*/
double randdouble(double a, double b) {
    static std::random_device rd;      // graine (hardware si dispo)
    static std::mt19937 gen(rd());     // moteur Mersenne Twister
    static std::uniform_real_distribution<double> dist(a, b);
    return dist(gen);                  // nombre ∈ [0.0, 1.0)
}


// ________________________________________________ VOISINAGES ____________________________________________________________________________________________________________


/*
Donne le voisin d'une solution dans la boule de Hamming de taille 1 : on change un et un seul booléen.

@input: un vecteur de booléens caractérisant notre solution : un élément est Vrai ssi l'usine indexée est ouverte.
@output: un vecteur de booléens, voisin de la solution donnée dans la boule de Hamming de taille 1.
*/
vector<bool> voisin_1_random (vector<bool> &solution){
    vector<bool> voisin_1(solution);
    int pos = randint(0, solution.size() - 1);
    voisin_1[pos] = !solution[pos];
    return voisin_1;
}


/*
Donne le voisin d'une solution dans la boule de Hamming de taille 2 : on change exactement deux booléens (distincts).

@input: un vecteur de booléens caractérisant notre solution : un élément est Vrai ssi l'usine indexée est ouverte.
@output: un vecteur de booléens, voisin de la solution donnée dans la boule de Hamming de taille 2.
*/
vector<bool> voisin_2_random (vector<bool> &solution){
    vector<bool> voisin_1(solution);
    int pos1 = randint(0, solution.size() - 1);
    int pos2 = randint(0, solution.size() - 1);
    while (pos2 == pos1){
        pos2 = randint(0, solution.size() - 1);
    }
    voisin_1[pos1] = !solution[pos1];
    voisin_1[pos2] = !solution[pos2];
    return voisin_1;
}


/*
Voisinage inclus dans la boule de Hamming de taille 1 : on ouvre une usine de plus.

@input: un vecteur de booléens caractérisant notre solution : un élément est Vrai ssi l'usine indexée est ouverte.
@output: le même vecteur de booléens, mais dont un 0 est devenu un 1.
    NB : si le vecteur était initialement rempli de 1, le vecteur retourné est identique.
*/
vector<bool> voisin_ouverture_random (vector<bool> &solution){
    vector<bool> voisin_1(solution);
    vector<int> pos_fermees;
    for (int i = 0; i < static_cast<int>(solution.size()); i++){
        if (!solution[i]){
            pos_fermees.push_back(i);
        }
    }
    if (pos_fermees.empty()){
        return solution;
    }
    int indice = randint(0, pos_fermees.size() - 1);
    voisin_1[pos_fermees[indice]] = 1;
    return voisin_1;
}


/*
Voisinage inclus dans la boule de Hamming de taille 1 : on ferme une des usines ouvertes.

@input: un vecteur de booléens caractérisant notre solution : un élément est Vrai ssi l'usine indexée est ouverte.
@output: le même vecteur de booléens, mais dont un 1 est devenu un 0.
    NB : si le vecteur était initialement rempli de 0, le vecteur retourné est identique.
*/
vector<bool> voisin_fermeture_random (vector<bool> &solution){
    vector<bool> voisin_1(solution);
    vector<int> pos_ouvertes;
    for (int i = 0; i < static_cast<int>(solution.size()); i++){
        if (solution[i]){
            pos_ouvertes.push_back(i);
        }
    }
    if (pos_ouvertes.size() == solution.size()){
        return solution;
    }
    int indice = randint(0, pos_ouvertes.size() - 1);
    voisin_1[pos_ouvertes[indice]] = 0;
    return voisin_1;
}


/*
Génère un voisin d'une solution donnée, selon le voisinage spécifié.

@input: une solution (vecteur de booléens) dont on veut un voisin, et le voisinage à explorer (son nom en string).
@output: un vecteur de booléens, voisin de la solution initiale dans le voisinage spécifié.
*/
vector<bool> voisin_random (vector<bool> &solution, const string voisinage){
    if (voisinage == "boule1"){
        return voisin_1_random(solution);
    } 
    else if (voisinage == "boule2"){
        return voisin_2_random(solution);
    } 
    else if (voisinage == "ouverture"){
        return voisin_ouverture_random(solution);
    } 
    else if (voisinage == "fermeture"){
        return voisin_fermeture_random(solution);
    }
    else {
        throw std::runtime_error("\n!!! Nom de voisinage inconnu.\n");
    }
}









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
pair<double, vector<bool>> recuit (Instance inst, const string voisinage, double temp_init, double temp_seuil, int nb_iter, double decroiss_lin_temp){
    auto [meilleur_cout, meilleure_sol] = heurist(inst); // ouverture_gloutonne(inst);
    //cout << "valeur initiale : " << meilleur_cout << "\n";
    double temp = temp_init;
    vector<bool> actuelle_sol = meilleure_sol;
    while (temp > temp_seuil){
        for (int i = 0; i < nb_iter; i++){
            vector<bool> voisin = voisin_random(actuelle_sol, voisinage);
            double nouveau_cout = evaluation_gloutonne(inst, voisin).first; 
            double delta = nouveau_cout - evaluation_gloutonne(inst, actuelle_sol).first;
            if (delta <= 0){
                actuelle_sol = voisin;
                if (nouveau_cout < meilleur_cout){
                    meilleur_cout = nouveau_cout;
                    meilleure_sol = actuelle_sol;
                }
            } 
            else {
                double q = randdouble(0.0, 1.0);
                if (q <= exp(- delta / temp)){
                    actuelle_sol = voisin;
                }
            }
        }
        temp *= decroiss_lin_temp;
    }
    return make_pair(meilleur_cout, meilleure_sol);
}




// ________________________________________________ RECHERCHE TABOU ____________________________________________________________________________________________________________



/*
Recherche tabou, telle quel présentée dans le cours.

@input:
    - une instance du problème (struct Instance),
    - la condition d'arrêt : au bout de combien d'itérations sans améliorations on arrête la recherche.
@output:
    - la (meilleure) valeur de la fonction objectif à minmiser obtenue,
    - et la solution correspondante (vecteurs de booléens caractérisant les usines ouvertes).
*/
pair<double, vector<bool>> taboo (Instance &inst, int max_iter_stuck){
    // Initialisation de la meilleure solution rencontrée, et de la solution actuelle.
    auto [best_cout, best_x] = heurist(inst); 
    //auto [best_cout, best_x] = recuit(inst, "boule1", 10000, 1e-3, 10, 0.999);
    double x_cout = best_cout;
    vector<bool> x = best_x;

    // Initialisation compteur et liste tabou
    int stuck_count = 0;
    int taille_liste_tabou = min(30, inst.nb_usines / 2);
    vector<int> taboo_list(taille_liste_tabou, -1);
    int dernier_ajout = -1;

    while (stuck_count < max_iter_stuck){
        double best_voisin_cout = numeric_limits<double>::infinity();
        vector<bool> best_voisin(x);
        int bit_modified = -1;
        for (int j = 0; j < inst.nb_usines; j++){
            vector<bool> voisin_interm(x);
            voisin_interm[j] = !x[j];
            auto [voisin_cout, voisin] = evaluation_gloutonne(inst, voisin_interm);
            bool est_tabou = find(taboo_list.begin(), taboo_list.end(), j) != taboo_list.end();
            if (!est_tabou && voisin_cout < best_voisin_cout){
                best_voisin = voisin;
                best_voisin_cout = voisin_cout;
                bit_modified = j;
            }
            
            if (est_tabou && voisin_cout < best_cout){
                best_voisin = voisin;
                best_voisin_cout = voisin_cout;
                bit_modified = j;
            }
        }
        x = best_voisin;
        x_cout = best_voisin_cout;
        if (x_cout < best_cout){
            best_x = x;
            best_cout = x_cout;
            stuck_count = 0;
        }
        else {
            stuck_count++;
        }
        taboo_list[(dernier_ajout + 1) % taille_liste_tabou] = bit_modified;
        dernier_ajout = (dernier_ajout + 1) % taille_liste_tabou;
    }
    return make_pair(best_cout, best_x);
}




