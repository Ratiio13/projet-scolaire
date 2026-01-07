#Etape 1
#Quel est le meilleur champion de LoL
#APARICIO Maxime, AMAZIT Alan, CAPIEU Valentin, POTTIER Anne, SEIGNOUX Vivien

import pandas as pd
import os


# Pour avoir un ALL des items, mettez : items.csv
nom_fichier = "Endgame.csv"
csv_files = [f for f in os.listdir() if f.endswith(nom_fichier)]


df_list = []

# on ajoute chaque .csv dans une liste
for file in csv_files:
    df = pd.read_csv(file, sep=';')
    df_list.append(df)

# on concatène
combined_df = pd.concat(df_list, ignore_index=True)


#suppression des doublons, on suppose que ['MatchID', "Champ Name"] est une clé primaire de chaque observation, et donc on suppose que chaque chaque champion ne peut être séléctionné qu'une seule fois dans chaque partie
#Notons que celui peut ne pas être véridique pour le mode de Jeu "Aveugle" or, les joueurs pro ne jouent que très rarement à ce mode, la suppresion de données qui se serait avéré pertinante est donc minime
final_df = combined_df.drop_duplicates(subset=['MatchID', "Champ Name"])

#on peut enlever la colonne MatchID
final_df = final_df.drop("MatchID", axis=1)

final_df.to_csv('ALL_Endgame_final.csv', index=False, sep = ";")



