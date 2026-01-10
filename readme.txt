Ce doc est le read me,
l'objectif est d'y expliquer ce que font les codes, pourquoi ils ont été crée ( pour trouver quoi, decider quoi, en lien avec quel requete ),
comment ils fonctionnent et comment modifier leur fonctionnement

Quel résultats ils ont obtenu? ce qu'on en a tiré, quels preuves ont en a déduit


Concernant la partie graphe de raffinement et base de donnée

écriture graphe de raffinement.jl : permet de creer le graphe de raffinement et de le stocker en mémoire, grâce à "raffinement_inverse.json" et "raffinement.json"
Les partitions sont symbolisé via des lettres, pour changer la partition de départ, il faut changer L, au début du code
Le premier fichier est crée via le dictionaire "D" et contient les raffinements dans le sens inverse ( donc de a|b|c (les singletons) vers abc (celle de cardinal 1) )
Le deuxième fichier est crée grâce au dictionaire "D3" et contient les raffinements dans le bon sens ( donc de abc vers  a|b|c )
Pour créer D, on part de la partition des singletons, et on ajoute cette partition et tout ses raffinement directs dans D, puis on appel récurssivement la fonction sur chacun de ses raffinement directs
Le programme est en O(nombre de partition * n²) pour faire le graphe de raffinement inverse





 CreationRaffinement.jl :  Ce programme remplit "graphe_raffinement.json", la base de donné qui contient le pourcentage de graphe reconstructible. Notons qu'il ne crée pas le fichier, 
pour créer le fichier, on utilise "écriture graphe de raffinement.jl" et on n'ajoute seulement les clés du dictionaire et pas les valeurs.
Notons que cette base est un dico de dico de cette forme : [partition => [n => pourcentage de graphe reconstructible]]
Pour la créé, on prend une des clées ( qui est une partition ), 
on génère tousles graphes d'ordre n grâce à un programme similaire "EnumerateClasses.jl", on fait les requêtes, mais vis à vis de la partition séléctionné
, puis on regarde le nombre d'entre eux non reconstructible et on ajoute cette valeur à la base de donnée. 
Notons que l'on peut faire bout par bout et qu'a chaque excecution, le programme reprendra où il s'est arrêté.
Pour changer le nombre de partition éffectué à chaque excecution, il faut changer le flag : "NOMBRE_EFFECTUE" en début de code
Pour modifier l'ordre des graphes, il faut modifier "GRAPH_SIZE" en fin de code


Lecture graphe de raffinement.jl : ce programme lit le graphe des raffinements et permet de le requêter.



LectureRaffinement.jl : lit la base de donnée et permet de la requêter



Connexite_Raffinement.jl : 
GRAPH_SIZE permet de changer l'ordre du graphe
RAFFINEMENT_DEPART est le raffinement duquel on part et qui servira de référence
















