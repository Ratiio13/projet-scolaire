# projet_MH

Archive du projet de Métaheuristiques (octobre 2025).
Contenu :
- notre rapport (pdf) de projet,
- un Makefile

Pour compiler :
```bash
make
```

Pour lancer (bien qu'il n'y ait pas grand chose à lancer) :
```bash
make run
````

- les instances fournies,

Dans src/ :
- traitement_instance.cpp : extrait les données des instances fournies et les stock dans une structure de donnée adaptée
- heuristique_init.cpp : contient une heuristique gloutonne, utilisée comme solution initiale pour les métaheuristiques 
- meta.cpp : contient les 3 métaheuristiques du cours : recuit simulé, recherche taboo et algorithme génétique,
- hard.cpp : différentes fonctions pour faire face au problème dans sa version avec demandes/capacités, mais pour des instances "pas trop restrictives" (approche booléenne, contraintes violées ou non, Cf Section 7 du rapport),
- penalite.cpp : fonctions relatives au problème "difficile", cette fois-ci en quantifiant le viol de contraintes,

Dans include/ : les headers .hpp correspondants.

Le sous-dossier src/independant contient :
- un fichier 'pluie.cpp' à compiler seul, car nous n'avons pas eu le temps de le rendre compatible avec le reste du code. C'est dans ce fichier que se trouve les algorithmes de "pluie de billes" (Cf Section 5 du Rapport),
- et le fichier python ayant permis de générer les figures du Rapport

