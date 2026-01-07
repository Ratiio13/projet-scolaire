#ceci est le code de l'Etape 1, il permet de faire les clusters et de les visualiser
#Quel est le meilleur champion de LoL
#APARICIO Maxime, AMAZIT Alan, CAPIEU Valentin, POTTIER Anne, SEIGNOUX Vivien
#Pseudo code
'''
Lecture du fichier 'grouped_stats_final.csv'
Séparation des données en X, le dataset et champ_names

Standardisation de X

X_pca_components <= Appliquation d'une PCA à X
Affichage d'un histogramme de la variance expliqué

X_tSNE <= Appliquation de t-SNE à X

Appliquer KMeans sur X
Appliquer Hierarchical Clustering sur X
Appliquer Spectral Clustering sur X

Créer des sous-graphiques pour chaque méthode de clustering (K-means, Hierarchical, Spectral)
Afficher les points dans un espace réduit (PCA et t-SNE), en coloriant les points en fonction des labels de cluster

Afficher les groupes de champions pour chaque méthode de clustering'''
import pandas as pd
from sklearn.decomposition import PCA
from sklearn.preprocessing import StandardScaler
from sklearn.manifold import TSNE
import matplotlib.pyplot as plt
import numpy as np


from sklearn.preprocessing import StandardScaler
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans, DBSCAN, AgglomerativeClustering, SpectralClustering



df = pd.read_csv('grouped_stats_final.csv',sep=';')
# d'un côté on met les données de l'autres, les noms des champions
X = df.iloc[:,1:]
champ_names = df.iloc[:,0]

# Initialisation du scaler
scaler = StandardScaler()

# On standardise les données
X = pd.DataFrame(scaler.fit_transform(X))


# X est un dataset ne comptenant que des int/float
# le nombre de lignes de X doit être supérieur ou égal au nombre de colonne
def PythonPCA(X):
  scaler = StandardScaler()
  X_cs = scaler.fit_transform(X)
  pca = PCA()
  X_pca_components = pca.fit_transform(X_cs)
  rotation_matrix = pca.components_.T
  return pca.explained_variance_ratio_, X_pca_components



## Visualisation
PCA_python, eigen_vecs = PythonPCA(X)
colors = ['blue', 'green']
plt.bar(range(1, 11), PCA_python[0:10], color=colors)
plt.xlabel('Number of Components')
plt.ylabel('Explained Variance Ratio')
plt.show()
#print("PCA_python (les valeurs propres) = ",PCA_python)

#Z représente les points après application de la PCA

Z = np.dot(X, np.transpose(eigen_vecs[0:2]))


plt.show()

### t-SNE
#Notons que pour un t-SNE efficace, il faut que le nombre de lignes de X soit sup ou égal à trois son nombre de colonne
tsne = TSNE(n_components=2, random_state=42, perplexity=30, n_iter=1000)
X_tSNE = tsne.fit_transform(X)



n_clusters = 10

# K-means
kmeans = KMeans(n_clusters=n_clusters)
kmeans_labels = kmeans.fit_predict(X)



# Hierarchical
hierarchical = AgglomerativeClustering(n_clusters=n_clusters)
hierarchical_labels = hierarchical.fit_predict(X)


# Spectral
# le nombre de lignes de X doit être strictement supérieur au nombre de colone
spectral = SpectralClustering(n_clusters=n_clusters, affinity='nearest_neighbors')
spectral_labels = spectral.fit_predict(X)

## Affichage
fig, axes = plt.subplots(2, 2, figsize=(12, 12))

def plot_with_labels(ax, Z, labels, title, champ_names):
    scatter = ax.scatter(Z[:, 0], Z[:, 1], c=labels, cmap='viridis', s=50)
    ax.set_title(title)
    # Ajouter les noms des champions
    for i, name in enumerate(champ_names):
        ax.text(Z[i, 0], Z[i, 1], name, fontsize=8, ha='right', va='bottom')


plot_with_labels(axes[0, 0], X_tSNE, kmeans_labels, "K Means t-SNE", champ_names)
plot_with_labels(axes[0, 1], Z, kmeans_labels, "K Means PCA", champ_names)
plot_with_labels(axes[1, 0], X_tSNE, spectral_labels, "spectral_labels t-SNE", champ_names)
plot_with_labels(axes[1, 1], Z, spectral_labels, "spectral_labels PCA", champ_names)

plt.tight_layout()
plt.show()

##Affichage des clusters de champions
# Avoir ces clusters nous permet de passer à l'étape 2
groupe_champ = []
for i in range(n_clusters):
    groupe_champ.append([])
for numero_champ in range(len(kmeans_labels)):
    groupe_champ[kmeans_labels[numero_champ]].append(champ_names[numero_champ])
print("via kmeans_labels, on a : ",groupe_champ)

groupe_champ = []
for i in range(n_clusters):
    groupe_champ.append([])
for numero_champ in range(len(hierarchical_labels)):
    groupe_champ[hierarchical_labels[numero_champ]].append(champ_names[numero_champ])
print("via hierarchical_labels, on a : ",groupe_champ)

groupe_champ = []
for i in range(n_clusters):
    groupe_champ.append([])
for numero_champ in range(len(spectral_labels)):
    groupe_champ[spectral_labels[numero_champ]].append(champ_names[numero_champ])
print("via spectral_labels, on a : ",groupe_champ)



