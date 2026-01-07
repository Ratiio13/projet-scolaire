// heuristique_init.hpp

#ifndef HEURISTIQUE_HPP
#define HEURISTIQUE_HPP

#include <vector>

#include "traitement_instance.hpp"


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
std::pair <double, std::vector<bool> > ouverture_gloutonne (Instance &inst);


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
double evaluate_struct(Instance inst, std::vector<bool> usines_ouvertes);


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
std::pair<double, std::vector<bool>> evaluation_gloutonne(Instance inst, std::vector<bool> usines_ouvertes);


/*
Notre heuristique initiale.
Appelle successivement les deux étapes décrites ci-dessus : 'ouverture_gloutonne' puis 'remise_gloutonne'.

@input: une instance (struct Instance définie dans 'traitement_instance.hpp'),
@output: une paire <double, vector<bool> > :
    - le double contient le coût total, ie la valeur objectif à minimiser,
    - le vecteur de booléens porte l'information de quelles usines ont été ouvertes lors de l'appel à notre heuristique.
      C'est ce vecteur qui "caractérise" la solution (dans le sens où c'est de ce vecteur que l'on regardera le voisinage).
*/
std::pair<double, std::vector<bool>> heurist (Instance inst);





#endif // HEURISTIQUE_HPP
