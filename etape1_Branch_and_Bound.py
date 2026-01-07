#Etape 1
#Quel est le meilleur champion de LoL
#APARICIO Maxime, AMAZIT Alan, CAPIEU Valentin, POTTIER Anne, SEIGNOUX Vivien
import pandas as pd
import copy
from scipy.spatial.distance import pdist, squareform
from sklearn.preprocessing import StandardScaler

df = pd.read_csv('grouped_stats.csv',sep=';')
X = df.iloc[:,1:]


# Initialisation du scaler
scaler = StandardScaler()

# Application de la standardisation
X = pd.DataFrame(scaler.fit_transform(X))

# on calcul une matrice de distance
distances = pdist(X, metric='euclidean')
distance_matrix = squareform(distances)

nb_champ = len(distance_matrix)

n_clusters = 2
groupe_champ = []
groupe_officiel = []
for i in range(n_clusters):
    groupe_champ.append([])
val_sol = sum(sum(distance_matrix))

def f_LB(groupement):
    somme = 0
    for gr in groupement:
        for n_c1 in range(len(gr)):
            for c2 in gr[n_c1+1:]:
                somme+= distance_matrix[gr[n_c1]][c2]
    return somme


def BandB(groupement,i):
    if (i == nb_champ) and (f_LB(groupement) < val_sol): #on est sur une feuille qui est optimale, on rend la solution
        print("on est sur une feuille")
        print("groupement = ",groupement)
        groupe_officiel = groupement
    else:
        #calcul de la LB actuelle

        LB = f_LB(groupement)
        if LB < val_sol: #ca vaut le coup de continuer
        #pour 2 clusters
            groupement2 = copy.deepcopy(groupement)
            groupement2[0].append(i)
            BandB(groupement2,i+1)

            groupement3 = copy.deepcopy(groupement)
            groupement3[1].append(i)
            BandB(groupement3,i+1)

    #sinon, on ne continue pas dans cette voie


BandB(groupe_champ,0)
# la séparation se fait sur le fait de mettre un champion dans tel ou tel cluster
# évaluation :  pour chaque champion qui n'est pas dans un cluster, on on ajoute la distance entre ce champion et tous les champions déjà dans un cluster + distance intra cluster







