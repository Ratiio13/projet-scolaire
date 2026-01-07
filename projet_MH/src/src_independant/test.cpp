//#include <bits/stdc++.h>
//ce fichier n'est pas a jour avec la nouvelle lecture
    
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <filesystem> // si tu l'utilises
#include <limits>
#include <chrono>
#include <iomanip>
#include <numeric> // pour std::inner_product
#include <algorithm>  // pour std::swap
#include <cstdlib>  // pour rand() et srand() génétique
#include <ctime>    // pour time() génétique
#include <algorithm> // pour std::merge génétique

//freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
using namespace std;
using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vll = vector<long long>;
using vvi = vector<vi>;
using vvll = vector<vll>;
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sz size()
#define pb(a) push_back(a)
#define mp(a, b) make_pair(a, b)
//#define endl << "\n"
#define esp << " "
    
template <typename T> 
inline void inp(vector<T> &v) {
    for (T &x : v) cin >> x;
}
    
inline void coutb(bool b) {
    cout << (b ? "YES" : "NO") << "\n";
}
double produit_scalaire(const std::vector<double>& a, const std::vector<bool>& b) {
    return std::inner_product(a.begin(), a.end(), b.begin(), 0.0);
}

/*
Prend une solution : ouverte ( qui est la liste binaire des usines ouverte ), 
et evalue le cout de cette solution en affectant tout les clients
O(nb_clients*nb_usines)
*/
double evaluate(int nb_clients, int nb_usines, vector<double> couts_ouverture, vector<vector<double>> couts_affectation, vector<bool> ouverte){
    // on initialise le cout_total, la valeur à minimiser
    double cout_total = 0;
    // pour chaque client,
    /*
    for (int i = 0; i < nb_clients; i++){
        // on dresse la liste des coûts de placement pour chaque emplacement : coût d'ouverture + coût de distance
        vector<double> couts(nb_usines,0.0);
        for (int j = 0; j < nb_usines; j++){
            if (ouverte[j] == 1){
                couts[j] = couts_affectation[i][j];
            }else{
                couts[j] = numeric_limits<double>::infinity();
            }
        }
        double cout_min = *min_element(couts.begin(), couts.end());
        cout_total += cout_min;      
    }*/
    for (int i = 0; i < nb_clients; i++){
        // on dresse la liste des coûts de placement pour chaque emplacement : coût d'ouverture + coût de distance
        double min_local = numeric_limits<double>::infinity();
        for (int j = 0; j < nb_usines; j++){
            if (ouverte[j] == 1 && couts_affectation[i][j] < min_local){
                min_local = couts_affectation[i][j];
            }
        }
        // et on l'ajoute au coût total
        cout_total += min_local;   
    }
    // on ajoute le cout d'ouverture des usines
    cout_total += produit_scalaire(couts_ouverture,ouverte);
    // en sortie de boucle, on a sommé les coûts minimaux (locaux) pour chaque client, et on retourne le total
    return cout_total;
}

/*
son nom parle pour lui même
Affiche le vecteur booléen de l'ouverture des usines
0 fermé, 1 ouverte
*/
void print_usine(int nb_usines,vector<bool> ouverte){
    for (int j = 0; j < nb_usines; j++){
        cout << ouverte[j] <<", ";
    }
    cout <<"\n";
}
void print_population(int nb_population, int nb_usines,vector<vector<bool>> population){
    for (int j = 0; j < nb_population; j++){
        print_usine(nb_usines,population[j]);
    }
    cout <<"\n";
}
void print_usine_cout(int nb_usines,vector<bool> ouverte, int nb_clients, vector<double> couts_ouverture, vector<vector<double>> couts_affectation){
    for (int j = 0; j < nb_usines; j++){
        cout << ouverte[j] <<", ";
    }
    cout << evaluate(nb_clients, nb_usines,couts_ouverture, couts_affectation,ouverte);
    cout <<"\n";
}
void print_population_cout(int nb_population, int nb_usines,vector<vector<bool>> population, int nb_clients, vector<double> couts_ouverture, vector<vector<double>> couts_affectation){
    for (int j = 0; j < nb_population; j++){
        print_usine_cout(nb_usines,population[j],nb_clients,couts_ouverture, couts_affectation);
    }
    cout <<"\n";
}




/*
glouton1 : 
pour chaque client, on ouvre argmin(ouverture + distance)
*/
double glouton1 (int nb_clients, int nb_usines, vector<double> couts_ouverture, vector<vector<double>> couts_affectation){
    // on initialise le cout_total, la valeur à minimiser
    double cout_total = 0;
    // pour chaque client,
    for (int i = 0; i < nb_clients; i++){
        // on dresse la liste des coûts de placement pour chaque emplacement : coût d'ouverture + coût de distance
        vector<double> couts(nb_usines);
        for (int j = 0; j < nb_usines; j++){
            couts[j] = couts_ouverture[j] + couts_affectation[i][j];
        }
        // on récupère l'emplacement de coût minimal,
        double cout_min = *min_element(couts.begin(), couts.end());
        // et on l'ajoute au coût total
        cout_total += cout_min;      
    }
    // en sortie de boucle, on a sommé les coûts minimaux (locaux) pour chaque client, et on retourne le total
    return cout_total;
}

/*
glouton2 : recurrence
- init : client1, on prend le argmin(ouverture + distance),
- n fixé, on sq on a des usines d'ouvertes et n clients placés,
pour le client n+1, on prend argmin(distance_usines_deja_ouvertes, ouverture + distance)
*/
void glouton3 (int nb_clients, int nb_usines, vector<double> couts_ouverture, vector<vector<double>> couts_affectation){

}

double glouton2 (int nb_clients, int nb_usines, vector<double> couts_ouverture, vector<vector<double>> couts_affectation){
    // on initialise le cout_total, la valeur à minimiser
    double cout_total = 0;
    // pour chaque client,
    for (int i = 0; i < nb_clients; i++){
        // on dresse la liste des coûts de placement pour chaque emplacement : coût d'ouverture + coût de distance
        vector<double> couts(nb_usines);
        int indice = 0;
        double min_local = numeric_limits<double>::infinity();
        for (int j = 0; j < nb_usines; j++){
            couts[j] = couts_ouverture[j] + couts_affectation[i][j];
            if (couts[j] < min_local){
                indice = j;
                min_local = couts[j];
            }
        }
        // et on l'ajoute au coût total
        cout_total += min_local;  
        // l'usine 'indice' vient d'être ouverte, donc on met son cout d'ouverture à 0 pour la suite.
        couts_ouverture[indice] = 0;
        
        // on récupère l'emplacement de coût minimal,
        //double cout_min = *min_element(couts.begin(), couts.end());
            
    }
    // en sortie de boucle, on a sommé les coûts minimaux (locaux) pour chaque client, et on retourne le total
    return cout_total;
}
/*
Pareil que glouton2, mais on rend l'instance ( un vecteur binaire d'usine )
Ceci permet l'initialisation des heuristiques de descente
*/
vector<bool> glouton2_instance (int nb_clients, int nb_usines, vector<double> couts_ouverture, vector<vector<double>> couts_affectation){
    // on initialise le cout_total, la valeur à minimiser
    double cout_total = 0;
    vector<bool> ouverte(nb_usines, 0);
    //vector<double> ouverte(nb_usines+1, 0.0);
    // pour chaque client,
    for (int i = 0; i < nb_clients; i++){
        // on dresse la liste des coûts de placement pour chaque emplacement : coût d'ouverture + coût de distance
        vector<double> couts(nb_usines,0.0);
        int indice = 0;
        double min_local = numeric_limits<double>::infinity();
        for (int j = 0; j < nb_usines; j++){
            couts[j] = couts_ouverture[j] + couts_affectation[i][j];
            if (couts[j] < min_local){
                indice = j;
                min_local = couts[j];
            }
        }
        // et on l'ajoute au coût total
        cout_total += min_local;  
        // l'usine 'indice' vient d'être ouverte, donc on met son cout d'ouverture à 0 pour la suite.
        couts_ouverture[indice] = 0;
        ouverte[indice] = 1;
            
    }
    //ouverte[nb_usines] = cout_total;
    // en sortie de boucle, on a sommé les coûts minimaux (locaux) pour chaque client, et on retourne le total
    //cout<<"gouton cout_total = " <<cout_total<<"\n";
    return ouverte;
}


/*
On prend une solution et on descend le voisinage
le voisinage est tous les autres vecteurs dont un seul bit differe
*/
double Descente_vois_1(int nb_clients, int nb_usines, vector<double> couts_ouverture, vector<vector<double>> couts_affectation){
    vector<bool > ouverte(nb_usines, 0);
    //on prend une solution initiale
    //ouverte = glouton2_instance(nb_clients, nb_usines, couts_ouverture, couts_affectation);
    double cout_original = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
    vector<bool> ouverte_tmp = ouverte;
    int indice = 1;
    //on swap pour qu'a la première itération, on ait le vecteur initial
    ouverte[indice] = !ouverte[indice];
    int limite_iteration = 0;
    while(limite_iteration<1000 && indice != -1){
        double curent = 0;
        //ici, indice contient la bonne composante a swap, pour avoir le minimum du voisinage
        ouverte[indice] = !ouverte[indice];
        indice = -1;
        double min_local = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
        for (int j = 0; j < nb_usines; j++){
            //on swap
            //if (ouverte[j]==0){ouverte[j] =1}
            //else {ouverte[j] = 0}
            ouverte[j] = !ouverte[j];
            curent = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
            if (curent < min_local){;
                min_local = curent;
                indice = j;
            }
            //on reswap, pour revenir au vecteur de base
            ouverte[j] = !ouverte[j];
        }
        limite_iteration +=1;
    }
    //ouverte[indice] = !ouverte[indice];
    //cout << "indice final = "<<indice<<"\n" << " et nb iteration = "<<limite_iteration<<"\n";
    double total = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
    print_usine(nb_clients,ouverte);
    //cout << "amélioration : " << total/cout_original<<"\n"<<"\n";
    return total;
    //return limite_iteration;
}
/*
On prend une solution et on descend le voisinage
le voisinage est tous les autres vecteurs dont un seul bit differe
*/
vector<bool> Descente_vois_1_sol(int nb_clients, int nb_usines, vector<double> couts_ouverture, vector<vector<double>> couts_affectation,vector<bool> ouverte){
    double cout_original = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
    vector<bool> ouverte_tmp = ouverte;
    int indice = 1;
    //on swap pour qu'a la première itération, on ait le vecteur initial
    ouverte[indice] = !ouverte[indice];
    int limite_iteration = 0;
    while(limite_iteration<1000 && indice != -1){
        double curent = 0;
        //ici, indice contient la bonne composante a swap, pour avoir le minimum du voisinage
        ouverte[indice] = !ouverte[indice];
        indice = -1;
        double min_local = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
        for (int j = 0; j < nb_usines; j++){
            //on swap
            //if (ouverte[j]==0){ouverte[j] =1}
            //else {ouverte[j] = 0}
            ouverte[j] = !ouverte[j];
            curent = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
            if (curent < min_local){;
                min_local = curent;
                indice = j;
            }
            //on reswap, pour revenir au vecteur de base
            ouverte[j] = !ouverte[j];
        }
        limite_iteration +=1;
    }
    //cout << "indice final = "<<indice<<"\n" << " et nb iteration = "<<limite_iteration<<"\n";
    //double total = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
    return ouverte;
}
/*
On prend une solution et on descend le voisinage
le voisinage est tous les autres vecteurs dont deux bits differe
*/
double Descente_vois_2(int nb_clients, int nb_usines, vector<double> couts_ouverture, vector<vector<double>> couts_affectation){
    vector<bool> ouverte(nb_usines, 1);
    //ouverte = glouton2_instance(nb_clients, nb_usines, couts_ouverture, couts_affectation);
    double cout_original = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
    int indice = 1;
    int indice2 = 1;
    //on swap pour qu'a la première itération, on ait le vecteur initial
    ouverte[indice] = !ouverte[indice];
    ouverte[indice2] = !ouverte[indice2];
    int limite_iteration = 0;
    while(limite_iteration<1000 && indice != -1){
        double curent = 0;
        //ici, j contient la bonne composante a swap, pour avoir le minimum du voisinage
        ouverte[indice] = !ouverte[indice];
        ouverte[indice2] = !ouverte[indice2];
        indice = -1;
        indice2 = -1;
        double min_local = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
        for (int j = 0; j < nb_usines; j++){
            for (int j2 = j+1; j2 < nb_usines; j2++){
            //on swap
            //if (ouverte[j]==0){ouverte[j] =1}
            //else {ouverte[j] = 0}
            ouverte[j] = !ouverte[j];
            ouverte[j2] = !ouverte[j2];
            curent = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
            if (curent < min_local){
                min_local = curent;
                indice = j;
                indice2 = j2;
            }
            //on reswap, pour revenir au vecteur de base
            ouverte[j] = !ouverte[j];
            ouverte[j2] = !ouverte[j2];
            }
        }
        limite_iteration +=1;
    }
    //cout << "indice final = "<<indice<<"\n";
    double total = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
    //cout << "amélioration : " << total/cout_original<<"\n";
    return total;
    //return limite_iteration;
}

/*
On descend le voisinage
à chaque opération, on ouvre une usine
On s'arrête lorsqu'ouvrir une usine augmente le coût
*/

double Descente_ouverture_fermeture(int nb_clients, int nb_usines, vector<double> couts_ouverture, vector<vector<double>> couts_affectation, int ouverture){
    vector<bool > ouverte(nb_usines, ouverture);
    int indice = 1;
    //on swap pour qu'a la première itération, on ait le vecteur initial
    ouverte[indice] = !ouverte[indice];
    int limite_iteration = 0;
    double min_local = numeric_limits<double>::infinity();
    while(limite_iteration<1000 && indice != -1){
        double curent = 0;
        //ici, indice contient la bonne composante a swap, pour avoir le minimum du voisinage
        //Rq, on swap au début, parce que si on swap a la fin, il se pourrait que indice = -1
        ouverte[indice] = !ouverte[indice];
        indice = -1;
        for (int j = 0; j < nb_usines; j++){
            if (ouverte[j] == ouverture){
                //on swap
                ouverte[j] = !ouverte[j];
                curent = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
                if (curent < min_local){;
                    min_local = curent;
                    indice = j;
                }
                //on reswap, pour revenir au vecteur de base
                ouverte[j] = !ouverte[j];
            }
        }
        double min_local = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
        limite_iteration +=1;
        //print_usine(nb_usines, ouverte);
        
    }
    //ouverte[indice] = !ouverte[indice];
    //cout << "indice final = "<<indice<<"\n" << " et nb iteration = "<<limite_iteration<<"\n";
    double total = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, ouverte);
    return total;
}
/*
Cette fonction est la première méta, le concept est de partir de plusieurs solution ( idéalement écarté )
et de faire une descente sur chacune d'entre elles, et on garde la meilleure
dans cette version on ne fait qu'une seule descente, mais on pourrait en faire d'autres

*/

double pluie_de_bille(int nb_clients, int nb_usines, vector<double> couts_ouverture, vector<vector<double>> couts_affectation){
    int nb_billes = 1;
    // on crée les billes
    vector<vector<bool>> nuage(nb_billes, vector<bool>(nb_usines));
    // Remplir avec des valeurs aléatoires
    for (auto& innerVec : nuage) {
        for (size_t i = 0; i < innerVec.size(); ++i) {
            innerVec[i] = rand() % 2;
        }
    }
    /*
    for (int j = 0; j < nb_usines; j++){
        nuage[nb_billes-1][j] = 0;
    }
    */
    //on fait couler les billes
    for (int bille = 0; bille < nb_billes; bille++){
        nuage[bille] = Descente_vois_1_sol(nb_clients, nb_usines, couts_ouverture, couts_affectation,nuage[bille]);
    }
    // on prend la meilleur
    double min_local = numeric_limits<double>::infinity();
    double cout_current = 0;
    for (int bille = 0; bille < nb_billes; bille++){
        cout_current = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, nuage[bille]);
        if (cout_current < min_local){
            min_local = cout_current;
        }
    }
    return min_local;

}


/*
Cette fonction fait une méta génétique
Deux visions : 
On prend uniquement les meilleurs, quitte a avoir de la consenguinité
 - pas de forcage
 - on force à garder 50% des enfants
 - on ne garde que les enfants 
*/

double genetique_1(int nb_clients, int nb_usines, vector<double> couts_ouverture, vector<vector<double>> couts_affectation){
    int nb_population  = 10;
    vector<vector<bool>> population(nb_population, vector<bool>(nb_usines));
    // Remplir avec des valeurs aléatoires
    for (auto& innerVec : population) {
        for (size_t i = 0; i < innerVec.size(); ++i) {
            innerVec[i] = rand() % 2;
        }
    }
    //print_population_cout(nb_population,nb_usines,population,nb_clients, couts_ouverture, couts_affectation);
    for(int i = 0;i<10;i++ ){
        //on fait evoluer la population
        std::vector<std::pair<vector<bool>, double>> conclave_parent(nb_population);
        for (int j = 0; j < nb_population; j++){
            population[j] = Descente_vois_1_sol(nb_clients, nb_usines, couts_ouverture, couts_affectation,population[j]);
            conclave_parent[j] = {population[j],evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, population[j])};
        }
        // création des enfants
        //chaque couple a deux enfants
        //cout << "les parents" << endl;
        //print_population_cout(nb_population,nb_usines,population,nb_clients, couts_ouverture, couts_affectation);
        std::vector<std::pair<vector<bool>, double>> conclave_enfant(nb_population);
        vector<vector<bool>> enfants(nb_population);
        for (int j = 0; j < nb_population-1; j+=2){
            //on fait un boucle pour éviter les erreurs de proxy lié au stockage des bool
            for(int k = 0; k < nb_usines/2; k++) {
                enfants[j].push_back(population[j][k]);
                enfants[j+1].push_back(population[j+1][k]);
            }
            for(int k = nb_usines/2 ; k < nb_usines; k++) {
                enfants[j].push_back(population[j+1][k]);
                enfants[j+1].push_back(population[j][k]);
            }
            //on fait évoluer l'enfant avant de le mettre dans le conclave
            enfants[j] = Descente_vois_1_sol(nb_clients, nb_usines, couts_ouverture, couts_affectation,population[j]);        // et on met les enfants dans le conclave
            conclave_enfant[j] = {enfants[j],evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, enfants[j])};
            conclave_enfant[j+1] = {enfants[j+1],evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, enfants[j+1])};
        }
        //cout << "les enfants" << endl;
        //print_population_cout(nb_population,nb_usines,enfants,nb_clients, couts_ouverture, couts_affectation);
        //cout << "avant de trier" << endl;
        // on trie selon le cout de la solution
        std::sort(conclave_parent.begin(), conclave_parent.end(), [](const auto &a, const auto &b) {
            return a.second < b.second;
        });
        std::sort(conclave_enfant.begin(), conclave_enfant.end(), [](const auto &a, const auto &b) {
            return a.second < b.second;
        });
        //ici ona les listes de conclaves qui sont trié

        // on a les conclaves trié, on fait ensuite un merge
        std::vector<std::pair<vector<bool>, double>> conclave_final;
        conclave_final.reserve(conclave_parent.size() + conclave_enfant.size());  // optimisation

        std::merge(conclave_parent.begin(), conclave_parent.end(), conclave_enfant.begin(), conclave_enfant.end(), std::back_inserter(conclave_final),
                [](const auto& a, const auto& b) {
                    return a.second < b.second;  // tri selon le double
                });
        // Affichage (optionnel)
        //dans v3, on a le résultats et on ne garde que les nb_population premiers (la taille du vecteur ne change pas) 
        //population.assign(conclave_final.begin(), conclave_final.begin() + nb_population);
        population.clear();
        population.reserve(nb_population); // optionnel, pour performance

        for(int i = 0; i < nb_population; ++i) {
            population.push_back(conclave_final[i].first);
        }

        //cout << "le final" << endl;
        //print_population_cout(nb_population,nb_usines,population,nb_clients,couts_ouverture, couts_affectation);


        //print_population(nb_population, nb_usines, population);
}
    double cout_final = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, population[0]);
    return cout_final;
}





double Bruine_de_bille(int nb_clients, int nb_usines, vector<double> couts_ouverture, vector<vector<double>> couts_affectation){
    int nb_billes = 90;
    double proba = 0.1;
    // on crée les billes
    vector<vector<bool>> nuage(nb_billes, vector<bool>(nb_usines));
    // Remplir avec des valeurs aléatoires
    for (auto& innerVec : nuage) {
        for (size_t i = 0; i < innerVec.size(); ++i) {
            innerVec[i] = (static_cast<double>(rand()) / RAND_MAX) < proba;
        }
    }
    /*
    for (int j = 0; j < nb_usines; j++){
        nuage[nb_billes-1][j] = 0;
    }
    */
    //on fait couler les billes
    for (int bille = 0; bille < nb_billes; bille++){
        nuage[bille] = Descente_vois_1_sol(nb_clients, nb_usines, couts_ouverture, couts_affectation,nuage[bille]);
    }
    // on prend la meilleur
    double min_local = numeric_limits<double>::infinity();
    double cout_current = 0;
    for (int bille = 0; bille < nb_billes; bille++){
        cout_current = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, nuage[bille]);
        if (cout_current < min_local){
            min_local = cout_current;
        }
    }
    return min_local;


}
double Bruine_de_bille_adapt(int nb_clients, int nb_usines, vector<double> couts_ouverture, vector<vector<double>> couts_affectation){
            double somme = std::accumulate(couts_ouverture.begin(), couts_ouverture.end(), 0.0);
            double moyenne = somme / couts_ouverture.size();
            
            double somme_totale = 0.0;
            std::size_t compteur = 0;

            for (const auto& ligne : couts_affectation) {
                somme_totale += std::accumulate(ligne.begin(), ligne.end(), 0.0);
                compteur += ligne.size(); 
            }

            double moyenne_af = (compteur > 0) ? somme_totale / compteur : 0.0;
            double ratio = moyenne/moyenne_af;
            int ratio_int = static_cast<int>(ratio*100);
            
            vector<double> Memoire = {0.880000,0.720000,0.620000,0.548000,0.440000,0.400000,0.400000,0.380000,0.380000,0.320000,0.320000,0.320000,0.300000,0.296000,0.300000,0.288000,0.288000,0.244000,0.240000,0.240000,0.240000,0.220000,0.220000,0.220000,0.220000,0.200000,0.200000,0.180000,0.180000,0.180000,0.180000,0.176000,0.160000,0.156000,0.160000,0.132000,0.120000,0.120000,0.120000,0.120000,0.120000,0.100000,0.100000,0.100000,0.100000,0.100000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.080000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000,0.060000};
           
    int nb_billes = 36 ;
    double proba = 0.060000;
    if (ratio_int<200)
        proba = Memoire[ratio_int];

    // on crée les billes
    vector<vector<bool>> nuage(nb_billes, vector<bool>(nb_usines));
    // Remplir avec des valeurs aléatoires
    for (auto& innerVec : nuage) {
        for (size_t i = 0; i < innerVec.size(); ++i) {
            innerVec[i] = (static_cast<double>(rand()) / RAND_MAX) < proba;
        }
    }
    /*
    for (int j = 0; j < nb_usines; j++){
        nuage[nb_billes-1][j] = 0;
    }
    */
    //on fait couler les billes
    for (int bille = 0; bille < nb_billes; bille++){
        nuage[bille] = Descente_vois_1_sol(nb_clients, nb_usines, couts_ouverture, couts_affectation,nuage[bille]);
    }
    // on prend la meilleur
    double min_local = numeric_limits<double>::infinity();
    double cout_current = 0;
    for (int bille = 0; bille < nb_billes; bille++){
        cout_current = evaluate(nb_clients, nb_usines, couts_ouverture, couts_affectation, nuage[bille]);
        if (cout_current < min_local){
            min_local = cout_current;
        }
    }
    return min_local;


}


int main2()  {
    srand(time(nullptr));  // initialise le générateur aléatoire
    std::vector<std::string> file = {"cap71", "cap72", "cap73","cap74","cap101","cap102","cap103","cap104","cap131","cap132","cap133","cap134"};
    std::vector<double> optimale = {932615.750, 977799.400,1010641.450,1034976.975,796648.437,854704.200,893782.112,928941.750,793439.562,851495.325,893076.712,928941.750};
    int nb_simulation = 12;
    double resultat = 0;
    double temps = 0;
    int nb_test = 1 ;
    //std::cout << std::fixed << std::setprecision(10);
    int solution_trop_petite = 0;
    for(int simulation = 0; simulation < nb_simulation;simulation++){
        //lecture des données
        ifstream fin("uncap_data/"+file[simulation]+".txt");
        ofstream fout("sortie.txt");
        if (!fin || !fout) return 1; // fichiers non ouverts

        int nb_clients, nb_usines;
        fin  >> nb_usines >> nb_clients;

        vector<int> capacites(nb_usines);
        vector<double> ouverture(nb_usines);
        for (int i = 0; i < nb_usines; i++){
            fin >> capacites[i] >> ouverture[i];
            //ouverture[i] = ouverture[i]/liste_norm_ouv[simulation-8];
        }

        vector<int> demandes(nb_clients);
        vector<vector<double>> affectations(nb_clients, vector<double>(nb_usines));
        
        for (int i = 0; i < nb_clients; i++){
            fin >> demandes[i];
            for (int j = 0; j < nb_usines; j++){
                fin >> affectations[i][j];
                affectations[i][j] = affectations[i][j];///liste_norm_af[simulation-8];
                
            }
        }
            for(int test = 0; test < nb_test;test++){
            //calcul de la solution
                auto start = std::chrono::high_resolution_clock::now();
                // pour changer d'heuristique, il faut changer cette ligne
                double v1 = pluie_de_bille(nb_clients, nb_usines, ouverture, affectations);
                //double v2 = genetique_1(nb_clients, nb_usines, ouverture, affectations);
                auto end = std::chrono::high_resolution_clock::now();
                if (v1<optimale[simulation]){
                    solution_trop_petite = 1;
                }
                std::chrono::duration<double, std::milli> duration = end - start;
                cout << "pour "+file[simulation]+" : " << v1 / optimale[simulation] << " pour un temps de : " << duration.count() << " ms"<<"\n";  
                
                


                resultat += (v1/optimale[simulation]-1)*100;
                temps += duration.count();

            }
        }


        //resultat += v1;
    cout << "\n";
    cout << "resultat en moyenne : " << resultat/(nb_test*nb_simulation) << "\n";

    cout << "temps en moyenne : " << temps/(nb_test*nb_simulation) << " ms" << "\n";
    if (solution_trop_petite == 1)
        cout << "/!\\ ATTENTION une des solutions est inférieur à l'optimal";

    /*
    cout << "nb clients = " << nb_clients << "\n";
    for (int i = 0; i < nb_clients; i++){
        for (int j = 0; j < nb_usines; j++){
            cout << affectations[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    */

    return 0;
}

