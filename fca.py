import pandas as pd
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import numpy as np
from scipy.linalg import svd
import matplotlib.pyplot as plt

# TABLEAU DE CONTINGENCE

# On recupere les donnees
df = pd.read_csv('ALL_Items_final.csv',sep=';')
# On cree le tableau de contingence avec les champions en ligne et les items en colonnes
# Chaque cellule correspond au nombre de fois où le champion a utilise l'item
contingency_table = df.groupby("Champ Name").sum()
contingency_table = contingency_table.reset_index()
champions = contingency_table["Champ Name"]
contingency_table = contingency_table.drop("Champ Name", axis=1)


# NETTOYAGE DES DONNEES

# On enleve les items qui ne sont jamais utilises (colonnes où il n'y a que des 0)
contingency_table = contingency_table.loc[:, (contingency_table != 0).any(axis=0)]
# On "nettoie" les donnees en enlevant celles où ils manquent des valeurs 
has_nan = contingency_table.isna().any().any()
if has_nan:
    print("There are NaN values in the table.")
else:
    print("There are no NaN values in the table.")


# NORMALISATION 

total = contingency_table.values.sum()  # Somme totale 
row_totals = contingency_table.sum(axis=1).values.reshape(-1, 1)  # Totaux des lignes
col_totals = contingency_table.sum(axis=0).values.reshape(1, -1)  # Totaux des colonnes
# Calcul des frequences
P = contingency_table / total  # Matrice des frequences du temps où le champion utilise l'objet
r = row_totals / total         # Proportion de l'utilisation totale des items par chaque champion
c = col_totals / total         # Proportion d'un item dans l'utilisation totale des items
# On centre les donnees
P_centered = P - r @ c


# PONDERATION

P_weighted = P_centered / np.sqrt(r @ c)


# DECOMPOSITION EN VALEURS SINGULIERES

U, S, Vt = svd(P_weighted, full_matrices=False)


# DETERMINATION DES COORDONNEES FACTORIELLES

# On projette les lignes et colonnes sur les axes principaux
row_coordinates = U * S
col_coordinates = Vt.T * S


# VISUALISATION GRAPHIQUE

plt.figure(figsize=(12, 12))
# Scatter plot des champions avec des points plus petits et plus transparents
plt.scatter(row_coordinates[:, 0], row_coordinates[:, 1], color='blue', alpha=0.7, s=50, label='Champions')
# Annoter tous les champions
for i in range(len(champions)):
    # Déplacement des labels pour éviter les chevauchements
    plt.annotate(
        champions[i],
        (row_coordinates[i, 0], row_coordinates[i, 1]),
        color='blue', fontsize=9,
        xytext=(5, 5), textcoords='offset points'  
    )
# Ajouter des lignes et titres
plt.axhline(0, color='black', linewidth=0.5, linestyle='--')
plt.axvline(0, color='black', linewidth=0.5, linestyle='--')
plt.title("Analyse des Correspondances (FCA)", fontsize=16)
plt.grid(True)
# Afficher
plt.show()