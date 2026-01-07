#include <vector>
#include <limits> // pour +infty
#include <numeric> // pour std::inner_product

#include "traitement_instance.hpp"
#include "heuristique_init.hpp"

using namespace std;


/*
Première étape de notre heuristique.
Parcours les clients (ordre arbitraire), et pour chaque client i :
- regarde dans quelle usine j il revient le moins cher de le placer
    (ie quelle usine j minimise : prix_ouverture[j] + prix_affectation[i][j]),
- place i à cette usine j, en ajoutant au coût total le prix d'ouverture de j (si pas déjà ouverte) et le prix d'affectation de i à j,
- et met le prix d'ouverture de j à 0 pour les prochains clients.

@input: une instance (struct Instance définie dans 'traitement_instance.hpp'),
@output: une paire <double, vector<bool> > :
    - le double contient le coût total, ie la valeur objectif à minimiser,
    - le vecteur de booléens porte l'information de quelles usines ont été ouvertes lors de l'appel à la fonction.
      C'est ce vecteur qui "caractérise" la solution (dans le sens où c'est de ce vecteur que l'on regardera le voisinage).
*/
pair<double, vector<bool>> ouverture_gloutonne (Instance &inst){
    // On initialise le cout_total (ie la valeur à minimiser) et le vecteur d'usines ouvertes.
    double cout_total = 0;
    vector<bool> usines_ouvertes(inst.nb_usines, false);
    // Et on fait une copie des prix d'ouverture des usines, pour ne pas les perdre malgré les modifications du vecteur à venir.
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

        // On ajoute donc ce prix au coût total.
        cout_total += min_candidat;  
        // l'usine 'indice' vient d'être ouverte, donc on met son cout d'ouverture à 0 pour la suite.
        // Puisque l'usine pos_candidat vient d'être ouverte, on l'indique dans le vecteur de booléens correspondant,
        usines_ouvertes[pos_candidat] = true;
        // et on met son prix d'ouverture à 0 pour les prochains clients.
        prix_ouv_cp[pos_candidat] = 0; 
    }

    // En sortie de boucle, on a sommé les coûts minimaux (locaux) pour chaque client, 
    // et dressé la liste des usines à ouvrir.
    // On affiche le prix total,
    //cout << "Glouton cout_total = " << cout_total << "\n";
    // et retourne la liste des usines ouvertes.
    return make_pair(cout_total, usines_ouvertes);
}


/*
Fonction NON utilisée car on lui préfère 'remise_gloutonne' ci-dessous, mais qui sert à des fins de comparaisons de performances.
Imaginons que lors de l'appel à 'ouverture_gloutonne', un client i ait été placé à une usine j car ouvrir la k coûtait trop cher "à son tour".
Il est pourtant possible que si les deux avaient déjà été ouvertes, k aurait été préférable (prix_affectation[i][j] > prix_affectation[i][k]).
Dès lors, si k a été par la suite ouverte pour un autre client, on peut améliorer la solution globale en plaçant i à k et non j.
C'est ce que fait cette fonction.
'remise_gloutonne' va plus loin, en remarquant qu'il est alors possible que l'usine j ne soit plus utilisée, 
et qu'on pourrait donc économiser son prix d'ouverture.

@input: une instance, et la solution fournie par 'ouverture_gloutonne' (ie un vecteur de booléen précisant quelles usines ont été ouvertes).
@output: un double pour le nouveau coût total après éventuels échanges d'usines.
*/
double evaluate_struct(Instance inst, vector<bool> usines_ouvertes){
    double cout_total = 0;
    for (int i = 0; i < inst.nb_clients; i++){
        double min_local = numeric_limits<double>::infinity();
        for (int j = 0; j < inst.nb_usines; j++){
            if (usines_ouvertes[j] == 1 && inst.prix_affectation[i][j] < min_local){
                min_local = inst.prix_affectation[i][j];
            }
        }
        cout_total += min_local;   
    }
    cout_total += inner_product(inst.prix_ouverture.begin(), inst.prix_ouverture.end(), usines_ouvertes.begin(), 0.0);
    return cout_total;
}


/*
Deuxième partie de notre heuristique initiale.
Imaginons que lors de l'appel à 'ouverture_gloutonne', un client i ait été placé à une usine j car ouvrir la k coûtait trop cher "à son tour".
Il est pourtant possible que si les deux avaient déjà été ouvertes, k aurait été préférable (prix_affectation[i][j] > prix_affectation[i][k]).
Dès lors, si k a été par la suite ouverte pour un autre client, on peut améliorer la solution globale en plaçant i à k et non j.
De plus, il est possible que l'usine j ne soit alors plus utilisée. Il faut alors vérifier, pour éventuellement économiser son prix d'ouverture.

@input: une instance, et la solution fournie par 'ouverture_gloutonne' (ie un vecteur de booléen précisant quelles usines ont été ouvertes).
@output: une paire <double, vector<bool> > :
    - un double pour le nouveau coût total après éventuels échanges d'usines,
    - et le vecteur de booléens pour la nouvelle "solution" : quelles usines sont utilisées après "remise".
*/
pair<double, vector<bool>> evaluation_gloutonne (Instance inst, vector<bool> usines_ouvertes){
    // La structure est similmaire à celle de 'ouverture_gloutonne'.

    // On initialise le cout_total (ie la valeur à minimiser), et le vecteur d'usines qui seront effectivement utilisées.
    double cout_total = 0;
    vector<bool> usines_utilisees(inst.nb_usines, false);

    // Pour chaque client i, on cherche dans quelle usine j il est le moins cher de le placer, PARMI LES USINES OUVERTES.
    for (int i = 0; i < inst.nb_clients; i++){
        double min_local = numeric_limits<double>::infinity();
        for (int j = 0; j < inst.nb_usines; j++){
            // Ainsi, on regarde si l'usine j permet des économies ET si j a déjà été ouverte,
            if (usines_ouvertes[j] == 1 && inst.prix_affectation[i][j] < min_local){
                min_local = inst.prix_affectation[i][j];
                // auquel cas on marque j comme étant bien utilisée.
                usines_utilisees[j] = true;
            }
        }
        cout_total += min_local;   
    }
    // En sortie de boucle, on ajoute le coût d'ouverture seulement des usines utilisées (et non des usines initialement ouvertes).
    cout_total += inner_product(inst.prix_ouverture.begin(), inst.prix_ouverture.end(), usines_utilisees.begin(), 0.0);
    return make_pair(cout_total, usines_utilisees);
}


/*
Notre heuristique initiale.
Appelle successivement les deux étapes décrites ci-dessus : 'ouverture_gloutonne' puis 'remise_gloutonne'.

@input: une instance (struct Instance définie dans 'traitement_instance.hpp'),
@output: une paire <double, vector<bool> > :
    - le double contient le coût total, ie la valeur objectif à minimiser,
    - le vecteur de booléens porte l'information de quelles usines ont été ouvertes lors de l'appel à notre heuristique.
      C'est ce vecteur qui "caractérise" la solution (dans le sens où c'est de ce vecteur que l'on regardera le voisinage).
*/
pair<double, vector<bool>> heurist (Instance inst){
    return evaluation_gloutonne(inst, ouverture_gloutonne(inst).second);
}



