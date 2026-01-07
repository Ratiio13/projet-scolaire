// traitement_instance.hpp

#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <string>
#include <vector>



// ________________________________________________ PROBLÈME SIMPLE ________________________________________________________________________________________________

/*
Définition d'une structure pour nos instances, regroupant pour chacune :
- les nombres de clients et d'usine,
- la capacité de chaque usine,
- la demande de chaque client,
- le prix d'ouverture (ou "d'implantation") de chaque usine,
- et le prix d'affectation de chaque client à chaque usine (une fois ouverte)
*/
struct Instance {
    // Variables
    int nb_clients;
    int nb_usines;
    std::vector<std::string> capacites; 
    std::vector<double> prix_ouverture;
    std::vector<int> demandes;
    std::vector<std::vector<double>> prix_affectation;

    // Constructeur (pas de défaut)
    Instance(int clients, int usines)
        : nb_clients(clients)
        , nb_usines(usines)
        , capacites(usines, "0") 
        , prix_ouverture(usines, 0.0)
        , demandes(clients, 0)
        , prix_affectation(clients, std::vector<double>(usines, 0.0)) {}
};

/*
Transforme un fichier d'entrée en Instance exploitable.
@input: un string : le chemin vers une instance (depuis la racine du projet), 
@output: un struct Instance, encodant l'instance donnée dans le fichier .txt d'entrée.
*/
Instance input_to_instance(const std::string& path_to_file);



// ________________________________________________ PROBLÈME (plus) COMPLEXE ________________________________________________________________________________________________

struct Instance_hard {

    // Variables
    int nb_clients;
    int nb_usines;
    std::vector<int> capacites; 
    std::vector<double> prix_ouverture; 
    std::vector<int> demandes;
    std::vector<std::vector<double>> prix_affectation;

    // Constructeur 
    Instance_hard(int clients, int usines):
        nb_clients(clients),
        nb_usines(usines),
        capacites(usines, 0),
        prix_ouverture(usines, 0.0),
        demandes(clients, 0),
        prix_affectation(clients, std::vector<double>(usines, 0.0))
    {}
};


/*
Transforme un fichier d'entrée .txt en Instance exploitable.
@input: un string : le chemin vers une instance (depuis la racine du projet), 
@output: un struct Instance, encodant l'instance donnée dans le fichier .txt d'entrée.
*/
Instance_hard input_to_instance_hard(const std::string &path_to_file);






#endif // INSTANCE_HPP
