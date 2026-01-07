#Etape2
#Quel est le meilleur champion de LoL
#APARICIO Maxime, AMAZIT Alan, CAPIEU Valentin, POTTIER Anne, SEIGNOUX Vivien


import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, confusion_matrix

df = pd.read_csv('ALL_Endgame_final.csv',sep=';')

champs =  [['Aatrox', 'Ambessa', 'Briar', 'Camille', 'Darius', 'Ezreal', 'Fiora', 'Gnar', 'Hecarim', 'Illaoi', 'JarvanIV', 'Jax', 'Kled', 'LeeSin', 'MonkeyKing', 'Nasus', 'Nocturne', 'Olaf', 'Pantheon', 'RekSai', 'Renekton', 'Riven', 'Senna', 'Sett', 'Shaco', 'Trundle', 'Urgot', 'Vi', 'Viego', 'XinZhao', 'Yorick'], ['Ashe', 'Belveth', 'Garen', 'Irelia', 'Kaisa', 'Kalista', 'Kindred', 'MasterYi', 'Varus', 'Vayne', 'Warwick', 'Yasuo', 'Yone'], ['Ahri', 'Anivia', 'Annie', 'Aurora', 'Cassiopeia', 'Hwei', 'Kassadin', 'KogMaw', 'Leblanc', 'Lissandra', 'Lux', 'Orianna', 'Ryze', 'Syndra', 'Taliyah', 'Veigar', 'Velkoz', 'Vex', 'Viktor', 'Xerath', 'Ziggs', 'Zoe'], ['Jayce', 'Kayn', 'Khazix', 'Naafiri', 'Qiyana', 'Quinn', 'Rengar', 'Talon', 'Zed'], ['Ivern', 'Janna', 'Karma', 'Lulu', 'Milio', 'Nami', 'Seraphine', 'Sona', 'Soraka', 'Yuumi', 'Zilean'], ['Amumu', 'Chogath', 'DrMundo', 'KSante', 'Malphite', 'Nunu', 'Ornn', 'Rammus', 'Sejuani', 'Shen', 'Sion', 'Skarner', 'TahmKench', 'Udyr', 'Volibear', 'Zac'], ['Akali', 'Azir', 'Diana', 'Ekko', 'Elise', 'Evelynn', 'Fizz', 'Galio', 'Gragas', 'Gwen', 'Katarina', 'Kayle', 'Kennen', 'Neeko', 'Nidalee', 'Shyvana', 'Sylas', 'TwistedFate', 'Vladimir'], ['Alistar', 'Bard', 'Blitzcrank', 'Braum', 'Leona', 'Maokai', 'Nautilus', 'Poppy', 'Pyke', 'Rakan', 'Rell', 'Renata', 'Taric', 'Thresh'], ['Akshan', 'Aphelios', 'Caitlyn', 'Corki', 'Draven', 'Gangplank', 'Graves', 'Jhin', 'Jinx', 'Lucian', 'MissFortune', 'Nilah', 'Samira', 'Sivir', 'Smolder', 'Tristana', 'Tryndamere', 'Twitch', 'Xayah', 'Zeri'], ['AurelionSol', 'Brand', 'FiddleSticks', 'Heimerdinger', 'Karthus', 'Lillia', 'Malzahar', 'Mordekaiser', 'Morgana', 'Rumble', 'Singed', 'Swain', 'Teemo', 'Zyra']]


# pour chqaue dataset, on ne prend que les colones que l'on veut analyser
df_filtre_1 = df[df['Champ Name'].isin(champs[0])]
df_filtre_2 = df[df['Champ Name'].isin(champs[1])]
df_filtre_3 = df[df['Champ Name'].isin(champs[2])]
df_filtre_4 = df[df['Champ Name'].isin(champs[3])]
df_filtre_5 = df[df['Champ Name'].isin(champs[4])]
df_filtre_6 = df[df['Champ Name'].isin(champs[5])]
df_filtre_7 = df[df['Champ Name'].isin(champs[6])]
df_filtre_8 = df[df['Champ Name'].isin(champs[7])]
df_filtre_9 = df[df['Champ Name'].isin(champs[8])]
df_filtre_10 = df[df['Champ Name'].isin(champs[9])]

# Séparation des variables explicatives et cible
# drop des variables surreprésenté
X_1 = df_filtre_1.drop(columns=["win","Champ Name","damageDealtToTurrets", "damageDealtToObjectives", "turretKills", "inhibitorKills", "largestKillingSpree", "largestMultiKill"])
X_2 = df_filtre_2.drop(columns=["win", "Champ Name", "damageDealtToTurrets", "damageDealtToObjectives", "turretKills", "inhibitorKills", "largestKillingSpree", "largestMultiKill"])
X_3 = df_filtre_3.drop(columns=["win", "Champ Name", "damageDealtToTurrets", "damageDealtToObjectives", "turretKills", "inhibitorKills", "largestKillingSpree", "largestMultiKill"])
X_4 = df_filtre_4.drop(columns=["win", "Champ Name", "damageDealtToTurrets", "damageDealtToObjectives", "turretKills", "inhibitorKills", "largestKillingSpree", "largestMultiKill"])
X_5 = df_filtre_5.drop(columns=["win", "Champ Name", "damageDealtToTurrets", "damageDealtToObjectives", "turretKills", "inhibitorKills", "largestKillingSpree", "largestMultiKill"])
X_6 = df_filtre_6.drop(columns=["win", "Champ Name", "damageDealtToTurrets", "damageDealtToObjectives", "turretKills", "inhibitorKills", "largestKillingSpree", "largestMultiKill"])
X_7 = df_filtre_7.drop(columns=["win", "Champ Name", "damageDealtToTurrets", "damageDealtToObjectives", "turretKills", "inhibitorKills", "largestKillingSpree", "largestMultiKill"])
X_8 = df_filtre_8.drop(columns=["win", "Champ Name", "damageDealtToTurrets", "damageDealtToObjectives", "turretKills", "inhibitorKills", "largestKillingSpree", "largestMultiKill"])
X_9 = df_filtre_9.drop(columns=["win", "Champ Name", "damageDealtToTurrets", "damageDealtToObjectives", "turretKills", "inhibitorKills", "largestKillingSpree", "largestMultiKill"])
X_10 = df_filtre_10.drop(columns=["win", "Champ Name", "damageDealtToTurrets", "damageDealtToObjectives", "turretKills", "inhibitorKills", "largestKillingSpree", "largestMultiKill"])

y_1 = df_filtre_1["win"]
y_2 = df_filtre_2["win"]
y_3 = df_filtre_3["win"]
y_4 = df_filtre_4["win"]
y_5 = df_filtre_5["win"]
y_6 = df_filtre_6["win"]
y_7 = df_filtre_7["win"]
y_8 = df_filtre_8["win"]
y_9 = df_filtre_9["win"]
y_10 = df_filtre_10["win"]

# Normalisation des données
scaler = StandardScaler()
X_scaled_1 = scaler.fit_transform(X_1)
X_scaled_2 = scaler.fit_transform(X_2)
X_scaled_3 = scaler.fit_transform(X_3)
X_scaled_4 = scaler.fit_transform(X_4)
X_scaled_5 = scaler.fit_transform(X_5)
X_scaled_6 = scaler.fit_transform(X_6)
X_scaled_7 = scaler.fit_transform(X_7)
X_scaled_8 = scaler.fit_transform(X_8)
X_scaled_9 = scaler.fit_transform(X_9)
X_scaled_10 = scaler.fit_transform(X_10)

# Séparation en ensembles d'entraînement et de test
#X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)

# Modèle de régression Lasso
alpha = 0.002
from sklearn.linear_model import LogisticRegression
lasso_1 = LogisticRegression(penalty='l1', solver='liblinear', max_iter=1000, C=alpha)
lasso_2 = LogisticRegression(penalty='l1', solver='liblinear', max_iter=1000, C=alpha)
lasso_3 = LogisticRegression(penalty='l1', solver='liblinear', max_iter=1000, C=alpha)
lasso_4 = LogisticRegression(penalty='l1', solver='liblinear', max_iter=1000, C=alpha)
lasso_5 = LogisticRegression(penalty='l1', solver='liblinear', max_iter=1000, C=alpha)
lasso_6 = LogisticRegression(penalty='l1', solver='liblinear', max_iter=1000, C=alpha)
lasso_7 = LogisticRegression(penalty='l1', solver='liblinear', max_iter=1000, C=alpha)
lasso_8 = LogisticRegression(penalty='l1', solver='liblinear', max_iter=1000, C=alpha)
lasso_9 = LogisticRegression(penalty='l1', solver='liblinear', max_iter=1000, C=alpha)
lasso_10 = LogisticRegression(penalty='l1', solver='liblinear', max_iter=1000, C=alpha)


lasso_1.fit(X_scaled_1, y_1)
lasso_2.fit(X_scaled_2, y_2)
lasso_3.fit(X_scaled_3, y_3)
lasso_4.fit(X_scaled_4, y_4)
lasso_5.fit(X_scaled_5, y_5)
lasso_6.fit(X_scaled_6, y_6)
lasso_7.fit(X_scaled_7, y_7)
lasso_8.fit(X_scaled_8, y_8)
lasso_9.fit(X_scaled_9, y_9)
lasso_10.fit(X_scaled_10, y_10)

# Prédictions
#y_pred = lasso.predict(X_test)

# Afficher les coefficients
#print(X.columns)
#print("Coefficients des variables :", lasso.coef_)

# Évaluer le modèle
#mse = mean_squared_error(y_test, y_pred)
#print("Erreur quadratique moyenne (MSE) :", mse)

# Prédictions sur l'ensemble de test
#print("Prédictions :", y_pred)

def transform_list(input_list):
    return [1 if x > 0 else -1 if x < 0 else None for x in input_list[0] if x != 0]

transformed_list_1 = transform_list(lasso_1.coef_)
transformed_list_2 = transform_list(lasso_2.coef_)
transformed_list_3 = transform_list(lasso_3.coef_)
transformed_list_4 = transform_list(lasso_4.coef_)
transformed_list_5 = transform_list(lasso_5.coef_)
transformed_list_6 = transform_list(lasso_6.coef_)
transformed_list_7 = transform_list(lasso_7.coef_)
transformed_list_8 = transform_list(lasso_8.coef_)
transformed_list_9 = transform_list(lasso_9.coef_)
transformed_list_10 = transform_list(lasso_10.coef_)


non_zero_columns_1 = [col+": "+ str(round(coef, 4)) for col, coef in zip(X_1.columns, lasso_1.coef_[0]) if coef != 0]
non_zero_columns_2 = [col+": "+ str(round(coef, 4)) for col, coef in zip(X_2.columns, lasso_2.coef_[0]) if coef != 0]
non_zero_columns_3 = [col+": "+ str(round(coef, 4)) for col, coef in zip(X_3.columns, lasso_3.coef_[0]) if coef != 0]
non_zero_columns_4 = [col+": "+ str(round(coef, 4)) for col, coef in zip(X_4.columns, lasso_4.coef_[0]) if coef != 0]
non_zero_columns_5 = [col+": "+ str(round(coef, 4)) for col, coef in zip(X_5.columns, lasso_5.coef_[0]) if coef != 0]
non_zero_columns_6 = [col+": "+ str(round(coef, 4)) for col, coef in zip(X_6.columns, lasso_6.coef_[0]) if coef != 0]
non_zero_columns_7 = [col+": "+ str(round(coef, 4)) for col, coef in zip(X_7.columns, lasso_7.coef_[0]) if coef != 0]
non_zero_columns_8 = [col+": "+ str(round(coef, 4)) for col, coef in zip(X_8.columns, lasso_8.coef_[0]) if coef != 0]
non_zero_columns_9 = [col+": "+ str(round(coef, 4)) for col, coef in zip(X_9.columns, lasso_9.coef_[0]) if coef != 0]
non_zero_columns_10 = [col+": "+ str(round(coef, 4)) for col, coef in zip(X_10.columns, lasso_10.coef_[0]) if coef != 0]

print(champs[0], "\n" + "est associé à :\n", non_zero_columns_1, "\n")
print(champs[1], "\n" + "est associé à :\n", non_zero_columns_2, "\n")
print(champs[2], "\n" + "est associé à :\n", non_zero_columns_3, "\n")
print(champs[3], "\n" + "est associé à :\n", non_zero_columns_4, "\n")
print(champs[4], "\n" + "est associé à :\n", non_zero_columns_5, "\n")
print(champs[5], "\n" + "est associé à :\n", non_zero_columns_6, "\n")
print(champs[6], "\n" + "est associé à :\n", non_zero_columns_7, "\n")
print(champs[7], "\n" + "est associé à :\n", non_zero_columns_8, "\n")
print(champs[8], "\n" + "est associé à :\n", non_zero_columns_9, "\n")
print(champs[9], "\n" + "est associé à :\n", non_zero_columns_10, "\n")

non_zero_columns_1 = [col for col, coef in zip(X_1.columns, lasso_1.coef_[0]) if coef != 0]
non_zero_columns_2 = [col for col, coef in zip(X_2.columns, lasso_2.coef_[0]) if coef != 0]
non_zero_columns_3 = [col for col, coef in zip(X_3.columns, lasso_3.coef_[0]) if coef != 0]
non_zero_columns_4 = [col for col, coef in zip(X_4.columns, lasso_4.coef_[0]) if coef != 0]
non_zero_columns_5 = [col for col, coef in zip(X_5.columns, lasso_5.coef_[0]) if coef != 0]
non_zero_columns_6 = [col for col, coef in zip(X_6.columns, lasso_6.coef_[0]) if coef != 0]
non_zero_columns_7 = [col for col, coef in zip(X_7.columns, lasso_7.coef_[0]) if coef != 0]
non_zero_columns_8 = [col for col, coef in zip(X_8.columns, lasso_8.coef_[0]) if coef != 0]
non_zero_columns_9 = [col for col, coef in zip(X_9.columns, lasso_9.coef_[0]) if coef != 0]
non_zero_columns_10 = [col for col, coef in zip(X_10.columns, lasso_10.coef_[0]) if coef != 0]

non_zero_columns_1.append("Champ Name")
non_zero_columns_2.append("Champ Name")
non_zero_columns_3.append("Champ Name")
non_zero_columns_4.append("Champ Name")
non_zero_columns_5.append("Champ Name")
non_zero_columns_6.append("Champ Name")
non_zero_columns_7.append("Champ Name")
non_zero_columns_8.append("Champ Name")
non_zero_columns_9.append("Champ Name")
non_zero_columns_10.append("Champ Name")

df_filtre_1 = df_filtre_1[non_zero_columns_1]
df_filtre_2 = df_filtre_2[non_zero_columns_2]
df_filtre_3 = df_filtre_3[non_zero_columns_3]
df_filtre_4 = df_filtre_4[non_zero_columns_4]
df_filtre_5 = df_filtre_5[non_zero_columns_5]
df_filtre_6 = df_filtre_6[non_zero_columns_6]
df_filtre_7 = df_filtre_7[non_zero_columns_7]
df_filtre_8 = df_filtre_8[non_zero_columns_8]
df_filtre_9 = df_filtre_9[non_zero_columns_9]
df_filtre_10 = df_filtre_10[non_zero_columns_10]

df_list = [df_filtre_1, df_filtre_2, df_filtre_3, df_filtre_4, df_filtre_5, df_filtre_6, df_filtre_7, df_filtre_8, df_filtre_9, df_filtre_10]

transformed_list = [transformed_list_1, transformed_list_2, transformed_list_3, transformed_list_4, transformed_list_5, transformed_list_6, transformed_list_7, transformed_list_8, transformed_list_9, transformed_list_10]




coefs=[0.5, 0.75, 1, 1.25, 1.5]

i=1
for df in df_list:
    df_grouped = df.groupby("Champ Name", as_index=False).mean().copy(deep=True)
    df_mean = df_grouped.drop(columns=["Champ Name"]).mean()
    df_mean["Champ Name"] = 0

    for k in range(5):
        df_grouped.loc[len(df_grouped), "Champ Name"] = f"{k+1} Star"
        j=0
        for stat, value in df_mean.items():
            if value != 0:
                if transformed_list[i-1][j] > 0:
                    df_grouped.loc[len(df_grouped) - 1, stat] = value*coefs[k]
                else:
                    df_grouped.loc[len(df_grouped) - 1, stat] = value*coefs[len(coefs)-k-1]
            j += 1


    file_path = f'grouped_c{i}.csv'
    df_grouped.to_csv(file_path, sep=';', index=False)
    i += 1

from sklearn.metrics import r2_score

# Calculer le R² ajusté pour chaque modèle Lasso
def adjusted_r2(X, y, model):
    n = X.shape[0]  # Nombre d'observations
    p = X.shape[1]  # Nombre de variables
    r2 = model.score(X, y)  # R²
    return 1 - (1 - r2) * (n - 1) / (n - p - 1)

# Calcul pour chaque modèle
r2_adjusted_1 = adjusted_r2(X_scaled_1, y_1, lasso_1)
r2_adjusted_2 = adjusted_r2(X_scaled_2, y_2, lasso_2)
r2_adjusted_3 = adjusted_r2(X_scaled_3, y_3, lasso_3)
r2_adjusted_4 = adjusted_r2(X_scaled_4, y_4, lasso_4)
r2_adjusted_5 = adjusted_r2(X_scaled_5, y_5, lasso_5)
r2_adjusted_6 = adjusted_r2(X_scaled_6, y_6, lasso_6)
r2_adjusted_7 = adjusted_r2(X_scaled_7, y_7, lasso_7)
r2_adjusted_8 = adjusted_r2(X_scaled_8, y_8, lasso_8)
r2_adjusted_9 = adjusted_r2(X_scaled_9, y_9, lasso_9)
r2_adjusted_10 = adjusted_r2(X_scaled_10, y_10, lasso_10)

# Afficher les résultats
print(f"R² ajusté pour le modèle 1: {r2_adjusted_1:.4f}")
print(f"R² ajusté pour le modèle 2: {r2_adjusted_2:.4f}")
print(f"R² ajusté pour le modèle 3: {r2_adjusted_3:.4f}")
print(f"R² ajusté pour le modèle 4: {r2_adjusted_4:.4f}")
print(f"R² ajusté pour le modèle 5: {r2_adjusted_5:.4f}")
print(f"R² ajusté pour le modèle 6: {r2_adjusted_6:.4f}")
print(f"R² ajusté pour le modèle 7: {r2_adjusted_7:.4f}")
print(f"R² ajusté pour le modèle 8: {r2_adjusted_8:.4f}")
print(f"R² ajusté pour le modèle 9: {r2_adjusted_9:.4f}")
print(f"R² ajusté pour le modèle 10: {r2_adjusted_10:.4f}")
#ce programme crée un dataset avec uniquement les champions séléctionné

# Prédictions
y_pred_init = lasso_1.predict(X_scaled_1)
y_pred = (y_pred_init > 0.5).astype(int)


#model = LogisticRegression(penalty='l1', solver='liblinear', max_iter=1000)

# Prédire les résultats sur l'ensemble de test

# Calcul des résidus
residuals = y_1 - y_pred
poucentage_de_réussite = (sum(1 - abs(residuals))/len(residuals))* 100
print("poucentage_de_réussite : ", poucentage_de_réussite)

# 1. Tracer des résidus vs valeurs prédites
plt.figure(figsize=(12, 6))
plt.subplot(1, 2, 1)
plt.scatter(y_pred, residuals, alpha=0.5)
plt.axhline(0, color='r', linestyle='--')
plt.title("Graphique des résidus vs valeurs prédites")
plt.xlabel("Valeurs prédites")
plt.ylabel("Résidus")

# 2. Tracer l'histogramme des résidus
plt.subplot(1, 2, 2)
sns.histplot(residuals, kde=True, color='blue', bins=30)
plt.title("Histogramme des résidus, poucentage de réussite = " + f"{poucentage_de_réussite:.2g}" + "%")
plt.xlabel("Résidus")
plt.ylabel("Fréquence")

plt.tight_layout()
plt.show()

# 3. Test de normalité des résidus (Shapiro-Wilk)
from scipy.stats import shapiro
stat, p_value = shapiro(residuals)
print(f"Test de Shapiro-Wilk: Stat={stat}, p-value={p_value}")

# Si la p-value est inférieure à 0.05, les résidus ne suivent pas une distribution normale.