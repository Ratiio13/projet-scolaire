import numpy as np
import matplotlib.pyplot as plt
data = np.loadtxt("resultat_classique.txt")


nb_boule = 25
# Exemple de données
x = np.linspace(1, nb_boule,nb_boule)

liste_var = [np.std(boule, ddof=1) for boule in data ]
liste_mean = [np.log(np.mean(boule)) for boule in data ]
var_up = [liste_mean[i]+2*liste_var[i] for i in range(nb_boule+1) ]
var_down = [liste_mean[i]-2*liste_var[i] for i in range(nb_boule+1) ]
plt.plot(x, liste_mean[1:],color ='blue', label="Classique")       # tracer la courbe
#plt.plot(x, var_up[1:],color ='red')
#plt.plot(x, var_down[1:],color ='red')


data = np.loadtxt("resultat_cook.txt")
liste_var = [np.std(boule, ddof=1) for boule in data ]
liste_mean = [np.log(np.mean(boule)) for boule in data ]
var_up = [liste_mean[i]+2*liste_var[i] for i in range(nb_boule+1) ]
var_down = [liste_mean[i]-2*liste_var[i] for i in range(nb_boule+1) ]

plt.plot(x, liste_mean[1:],color ='blue',linestyle='--', label="intensification : 10% d'usines ouvertes")       # tracer la courbe
#plt.plot(x, var_up[1:],color ='red',linestyle='--')
#plt.plot(x, var_down[1:],color ='red',linestyle='--')
plt.title("qualité de la solution trouvé en fonction du nombre de billes")
#plt.title("temps d'excecution en fonction du nombre de billes")
plt.xlabel("nombre de billes")
plt.ylabel("% de différence avec la solution optimale")
#plt.ylabel("temps d'excecution en ms")

plt.grid(True)
plt.legend(loc='upper left')  # optionnel : ajouter une grille
plt.savefig("resultat superpose log 4der echantillion  = 50.png")
plt.show()