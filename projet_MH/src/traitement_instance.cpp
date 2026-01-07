#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

#include "traitement_instance.hpp"

using namespace std;

// ________________________________________________ PROBLÈME SIMPLE ________________________________________________________________________________________________

/*
// Rappel de la structure d'instance utilisée (définie dans 'traitement_instance.hpp') :

struct Instance {

    // Variables
    int nb_clients;
    int nb_usines;
    vector<string> capacites; 
    vector<double> prix_ouverture; 
    vector<int> demandes;
    vector<vector<double>> prix_affectation;

    // Constructeur 
    Instance(int clients, int usines):
        nb_clients(clients),
        nb_usines(usines),
        capacites(usines, "0"),
        prix_ouverture(usines, 0.0),
        demandes(clients, 0),
        prix_affectation(clients, vector<double>(usines, 0.0))
    {}
};
*/


/*
Transforme un fichier d'entrée .txt en Instance exploitable.
@input: un string : le chemin vers une instance (depuis la racine du projet), 
@output: un struct Instance, encodant l'instance donnée dans le fichier .txt d'entrée.
*/
Instance input_to_instance(const string &path_to_file){
    
    // Ouverture du fichier d'entrée .txt
    ifstream fin(path_to_file);
    // Message en cas d'erreur lors de l'ouverture :
    if (!fin) {
        throw std::runtime_error("Échec d'ouverture du fichier d'entrée.");
    } 

    // On récupère les deux premières valeurs du .txt, correspondant aux nombres d'usines et de clients 
    int nb_clients, nb_usines;
    fin  >> nb_usines >> nb_clients;

    // On définit notre variable d'instance (qui sera retournée) :
    Instance inst{nb_clients, nb_usines};

    // Conformément à la structure des .txt :
    // 1) on commence par récupérer les capacités et prix d'ouverture de chaque usine
    for (int i = 0; i < nb_usines; i++){
        fin >> inst.capacites[i] >> inst.prix_ouverture[i];
    }

    // 2) puis on réupère les demandes et prix d'affectations aux usines de chaque client
    for (int i = 0; i < nb_clients; i++){
        fin >> inst.demandes[i];
        for (int j = 0; j < nb_usines; j++){
            fin >> inst.prix_affectation[i][j];
        }
    }

    return inst;
}



// ________________________________________________ PROBLÈME (plus) COMPLEXE ________________________________________________________________________________________________

/*
// Rappel de la structure d'instance utilisée (définie dans 'traitement_instance.hpp') :

struct Instance_hard {

    // Variables
    int nb_clients;
    int nb_usines;
    vector<int> capacites; 
    vector<double> prix_ouverture; 
    vector<int> demandes;
    vector<vector<double>> prix_affectation;

    // Constructeur 
    Instance_hard(int clients, int usines):
        nb_clients(clients),
        nb_usines(usines),
        capacites(usines, 0),
        prix_ouverture(usines, 0.0),
        demandes(clients, 0),
        prix_affectation(clients, vector<double>(usines, 0.0))
    {}
};
*/


/*
Transforme un fichier d'entrée .txt en Instance exploitable.
@input: un string : le chemin vers une instance (depuis la racine du projet), 
@output: un struct Instance, encodant l'instance donnée dans le fichier .txt d'entrée.
*/
Instance_hard input_to_instance_hard(const string &path_to_file){
    
    // Ouverture du fichier d'entrée .txt
    ifstream fin(path_to_file);
    // Message en cas d'erreur lors de l'ouverture :
    if (!fin) {
        throw std::runtime_error("Échec d'ouverture du fichier d'entrée.");
    } 

    // On récupère les deux premières valeurs du .txt, correspondant aux nombres d'usines et de clients 
    int nb_clients, nb_usines;
    fin  >> nb_usines >> nb_clients;

    // On définit notre variable d'instance (qui sera retournée) :
    Instance_hard inst{nb_clients, nb_usines};

    // Conformément à la structure des .txt :
    // 1) on commence par récupérer les capacités et prix d'ouverture de chaque usine
    for (int i = 0; i < nb_usines; i++){
        fin >> inst.capacites[i] >> inst.prix_ouverture[i];
    }

    // 2) puis on réupère les demandes et prix d'affectations aux usines de chaque client
    for (int i = 0; i < nb_clients; i++){
        fin >> inst.demandes[i];
        for (int j = 0; j < nb_usines; j++){
            fin >> inst.prix_affectation[i][j];
        }
    }

    return inst;
}
