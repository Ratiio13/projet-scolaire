#Etape 1
#Quel est le meilleur champion de LoL
#APARICIO Maxime, AMAZIT Alan, CAPIEU Valentin, POTTIER Anne, SEIGNOUX Vivien

#on regroupe toute les lignes représentant un même champion et on prend la moyenne des données

import pandas as pd
df = pd.read_csv('ALL_items_final.csv',sep=';')
grouped = df.groupby('Champ Name').mean()
grouped = grouped.reset_index()
grouped.to_csv('grouped_items_final.csv', sep=';', index=False)