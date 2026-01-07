#Etape2
#Quel est le meilleur champion de LoL
#APARICIO Maxime, AMAZIT Alan, CAPIEU Valentin, POTTIER Anne, SEIGNOUX Vivien


import pandas as pd
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
import numpy as np

df = pd.read_csv('grouped_c1.csv',sep=';')

old_X = df.iloc[:,1:]
X = old_X.iloc[:-5]

# Stadardisation
scaler = StandardScaler()
old_X = scaler.fit_transform(old_X)
champ_names = df.iloc[:,0]


# X est un dataset ne comptenant que des int/float
# le nombre de lignes de X doit être supérieur ou égal au nombre de colonne
def PythonPCA(X):
    # On commence par standardiser les données
    scaler = StandardScaler()
    X_cs = scaler.fit_transform(X)
    # On applique ensuite la PCA
    pca = PCA()
    X_pca_components = pca.fit_transform(X_cs)

    return pca.explained_variance_ratio_, X_pca_components

# On affiche la proportion de variance expliquée en fonction du nombre de composants
plt.figure(1)
PCA_python, eigen_vecs = PythonPCA(X)
colors = ['blue', 'green']
print("PCA_python = ",len(PCA_python))
plt.bar(range(1, len(PCA_python)+1), PCA_python, color=colors)
plt.xlabel('Number of Components')
plt.ylabel('Explained Variance Ratio')
plt.show()
print("PCA_python = ",PCA_python)

# Z est les points après PCA
Z = np.dot(old_X, np.transpose(eigen_vecs[0:2]))
# On affiche les points
plt.figure(figsize=(10, 8))
plt.scatter(Z[:, 0], Z[:, 1], color='blue')

# On écrit les noms des champions à côté des points qui leur correspondent
for i, champ_name in enumerate(champ_names):
    plt.text(Z[i, 0], Z[i, 1], champ_name, fontsize=9, ha='right', color='black')
print (df.columns)
list_stat = list(df.columns)
result = ', \n'.join(list_stat)
variance_exp = PCA_python[0] + PCA_python[1]
titre_PCA = 'PCA of Champions, Variance expliqué : '+ f"{variance_exp:.2g}"+ "\n" + "\n" +result


plt.subplots_adjust(bottom=0.1, top=0.75)
plt.title(titre_PCA)
plt.xlabel('PCA Component 1')
plt.ylabel('PCA Component 2')
plt.show()