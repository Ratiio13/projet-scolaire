#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
#include <numeric>
#include <algorithm>

#include "traitement_instance.hpp"
#include "heuristique_init.hpp"
#include "meta.hpp"
#include "hard.hpp"
#include "penalite.hpp"

using namespace std;


/*
Petite fonction pour afficher un vecteur de booléen (nos solutions).
Si l'usine j est ouverte, affiche "1".
Si l'usine j est fermée, affiche un point "." .
@input: un vecteur de booléens.
@output: nothing.
*/
void print_vector_bool (const vector<bool> v){
    for (int i = 0; i < static_cast<int>(v.size()); i++){
        if (!v[i]){
            cout << ". ";
        } else {
            cout << v[i] << " ";
        }
    }
    cout << "\n";
}

void print_vector_int (const vector<int> v){
    for (int i = 0; i < static_cast<int>(v.size()); i++){
        cout << v[i] << " ";
    }
    cout << "\n";
}

void print_vector_double (const vector<double> v){
    for (int i = 0; i < static_cast<int>(v.size()); i++){
        cout << v[i] << " ";
    }
    cout << "\n";
}

/*
Fonction testant les différentes étapes de notre heuristique initiale sur 1 instance,
ainsi que le recuit simulé.

@input: nothing
@output: nothing
*/
void perf_1(){
    // double val_optimale = 12; // valeur optimale pour 'myex'

    //Instance inst = input_to_instance("myex.txt");
    Instance inst = input_to_instance("uncap_data/cap71.txt");
    double val_optimale = 932615.750;

    auto [v1_interm, ouvertes] = ouverture_gloutonne(inst);
    double v1 = v1_interm / val_optimale /* */ ;
    double v2 = evaluate_struct(inst, ouvertes)  / val_optimale /**/;
    //double v3 = remise_gloutonne(inst, ouvertes).first  / val_optimale /**/;
    double v4 = heurist(inst).first / val_optimale /**/;
    double v5 = recuit(inst, "boule1", 10000, 1e-3, 10, 0.99).first / val_optimale /**/;
    double v6 = taboo(inst, 1000).first / val_optimale;

    cout << "ouverture_gloutonne : " << v1  << "\n";
    cout << "glouton + evaluate : " << v2  << "\n";
    //cout << "glouton + evaluate + remise : " << v3  << "\n";
    cout << "heurist : " << v4 << "\n";
    cout << "recuit : " << v5 << "\n";
    cout << "taboo : " << v6 << "\n";
}


/*
Fonction testant les différentes étapes de notre heuristique initiale sur toutes les instances (sauf 'capa', 'capb', 'capc'),
ainsi que le recuit simulé.

@input: nothing
@output: nothing
*/
void perf_petites(){

    vector<std::string> files = {"cap71", "cap72", "cap73","cap74","cap101","cap102","cap103","cap104","cap131","cap132","cap133","cap134"};
    vector<double> val_optimales = {932615.750, 977799.400, 1010641.450, 1034976.975, 796648.437, 854704.200, 893782.112, 928941.750, 793439.562, 851495.325, 893076.712, 928941.750};
    
    double v1 = 0.0, v2 = 0.0, v4 = 0.0, v5 = 0.0, v6 = 0.0;
    int nb_inf1 = 0;

    for (int i = 0; i < static_cast<int>(files.size()); i++) {
        Instance inst = input_to_instance("uncap_data/" + files[i] + ".txt");

        auto [v1_interm, ouvertes] = ouverture_gloutonne(inst);
        v1 += v1_interm / val_optimales[i];
        v2 += evaluate_struct(inst, ouvertes) / val_optimales[i];
        //v3 += remise_gloutonne(inst, ouvertes).first / val_optimales[i];
        v4 += heurist(inst).first / val_optimales[i];
        v5 += recuit(inst, "boule1", 10000, 1e-3, 10, 0.9).first / val_optimales[i] /**/;
        v6 += taboo(inst, 1000).first / val_optimales[i];
        if (v6 < 1){
            nb_inf1++;
        }
    }

    cout << "ouverture_gloutonne : " << v1 / files.size() << "\n";
    cout << "glouton + evaluate : " << v2 / files.size() << "\n";
    //cout << "glouton + evaluate + remise : " << v3 / files.size() << "\n";
    cout << "heurist : " << v4 / files.size() << "\n";
    cout << "recuit : " << v5 / files.size() << "\n";
    cout << "taboo : " << v6 / files.size() << "\n";
    cout << "Nb de valeurs anormalement < à la valeur optimale : " << nb_inf1 << "\n";
}


/*
Fonction testant les différentes étapes de notre heuristique initiale sur toutes les instances (sauf 'capa', 'capb', 'capc'),
ainsi que le recuit simulé.

@input: nothing
@output: nothing
*/
void perf_abc(){

    //vector<std::string> files = {"cap71", "cap72", "cap73","cap74","cap101","cap102","cap103","cap104","cap131","cap132","cap133","cap134"};
    vector<std::string> files = {"capa", "capb", "capc"};
    vector<double> val_optimales = {17156454.478, 12979071.582, 11505594.329};

    double v1 = 0.0, v2 = 0.0, v4 = 0.0, v5 = 0.0;
    int nb_inf1 = 0;

    for (int i = 0; i < static_cast<int>(files.size()); i++) {
        Instance inst = input_to_instance("uncap_data/" + files[i] + ".txt");

        auto [v1_interm, ouvertes] = ouverture_gloutonne(inst);
        v1 += v1_interm / val_optimales[i];
        v2 += evaluate_struct(inst, ouvertes) / val_optimales[i];
        //v3 += remise_gloutonne(inst, ouvertes).first / val_optimales[i];
        v4 += heurist(inst).first / val_optimales[i];
        double v5_interm = recuit(inst, "boule1", 10000, 1e-3, 10, 0.9).first;
        v5 += v5_interm / val_optimales[i] /**/;
        cout << files[i] << " : " << v5_interm << "\n";
        if (v5 < 1){
            nb_inf1++;
        }
    }

    cout << "ouverture_gloutonne : " << v1 / files.size() << "\n";
    cout << "glouton + evaluate : " << v2 / files.size() << "\n";
    //cout << "glouton + evaluate + remise : " << v3 / files.size() << "\n";
    cout << "heurist : " << v4 / files.size() << "\n";
    cout << "recuit : " << v5 / files.size() << "\n";
    cout << "Nb de valeurs anormalement < à la valeur optimale : " << nb_inf1 << "\n";
}





// ____________________________________________________________ MAIN ________________________________________________________________________________________

int main(){
    cout << "_____ DÉBUT _____\n\n";

    //perf_1();
    perf_petites();
    //perf_abc();


    cout << "\n_____ FIN _____\n";
    return 0;
}