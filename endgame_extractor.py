#Etape 1
#Quel est le meilleur champion de LoL
#APARICIO Maxime, AMAZIT Alan, CAPIEU Valentin, POTTIER Anne, SEIGNOUX Vivien

import pandas as pd
import requests
import time
import copy



dictio_end = {
  'MatchID': "",
  'Champ Name': "",
  "win":0,
  "effectiveHealAndShielding":0,
"largestKillingSpree": 0,
"largestMultiKill" : 0,
"timeCCingOthers" : 0,

"totalDamageDealtToChampions" : 0,
"physicalDamageDealtToChampions" : 0,
"magicDamageDealtToChampions" : 0,
"trueDamageDealtToChampions" : 0,
"totalDamageDealt" : 0,
"physicalDamageDealt" : 0,
"magicDamageDealt" : 0,
"trueDamageDealt" : 0,
"damageDealtToTurrets" : 0,
"damageDealtToObjectives" : 0,

"totalHeal" : 0,
"effectiveHealAndShielding" : 0,
"totalDamageTaken" : 0,
"physicalDamageTaken" : 0,
"magicDamageTaken" : 0,
"trueDamageTaken" : 0,
"damageSelfMitigated" : 0,

"goldSpent" : 0,
"totalMinionsKilled" : 0,
"neutralMinionsKilled" : 0,

"visionScore" : 0,
"wardsPlaced" : 0,
"wardsKilled" : 0,
"visionWardsBoughtInGame" : 0,

"turretKills" : 0,
"inhibitorKills" : 0

  }

###choses a changer pour l'user
region = "europe"
nom_du_joueur = "Dr Orange"
gametag = "Caps"
api_key = "RGAPI-8c606c5e-e79a-4e3b-baa4-87df4ec2d218"
nombre_de_joueur = 1000


liste_name = []
liste_name.append(nom_du_joueur)

requestPUUID = "https://" + region +".api.riotgames.com/riot/account/v1/accounts/by-riot-id/" + nom_du_joueur +"/" + gametag +"?api_key=" + api_key
PUUID_initial = requests.get(requestPUUID).json()
print("PUUID_initial = ",PUUID_initial)
if PUUID_initial.get('status') != None:
  print("on a une erreur dans la requests")
  if PUUID_initial['status']['status_code'] == 403:
    print("\n \n ERREUR de API key, veuiller en regenerer une autre, \n Vous pouvez nous écrire à maxime.aparicio@ensiie.eu ou alan.amazit@ensiie.eu pour qu'on puisse vous en envoyer une")
liste_PUUID = [PUUID_initial["puuid"]]

for itération in range(nombre_de_joueur):
  print("itération n°",itération)
  t1 = time.time()

  ##CHOSES A CHANGER

  matches_url = "https://" + region +".api.riotgames.com/lol/match/v5/matches/by-puuid/" + liste_PUUID[itération] + "/ids?start=0&count=100&api_key=" + api_key

  matches = requests.get(matches_url).json()

  if len(matches) == 100:
    print("la récupération à bien été éffectué")
  url_list = []
  for match_id in matches:
      url_list.append('https://' + region +'.api.riotgames.com/lol/match/v5/matches/' + match_id + '?api_key=' + api_key)


  history = []
  i=0
  for match_url in url_list:# il y a un sleep car on ne peut pas faire plus de 20 requetes par seconde
      i+=1
      history.append(requests.get(match_url).json())
      if i%20 == 0:
          time.sleep(1)
  print(history[0]['info']['participants'][0]['riotIdGameName'])




  dataset_end = pd.DataFrame(columns=["MatchID",
  "Champ Name",
  "win",
  "effectiveHealAndShielding",
  "largestKillingSpree",
"largestMultiKill",
"timeCCingOthers",

"totalDamageDealtToChampions",
"physicalDamageDealtToChampions",
"magicDamageDealtToChampions",
"trueDamageDealtToChampions",
"totalDamageDealt",
"physicalDamageDealt",
"magicDamageDealt",
"trueDamageDealt",
"damageDealtToTurrets",
"damageDealtToObjectives",

"totalHeal",
"totalDamageTaken",
"physicalDamageTaken",
"magicDamageTaken",
"trueDamageTaken",
"damageSelfMitigated",

"goldSpent",
"totalMinionsKilled",
"neutralMinionsKilled",

"visionScore",
"wardsPlaced",
"wardsKilled",
"visionWardsBoughtInGame",
"turretKills",
"inhibitorKills"])
  history = [hist_match for hist_match in history if 'info' in hist_match and hist_match['info'].get('gameMode') == 'CLASSIC']
    # partie endgame

  for hist_match in history:
    for person in range(10):
      tmp_end = copy.deepcopy(dictio_end)
      tmp_end['MatchID'] = hist_match['metadata']['matchId']
      tmp_end['Champ Name'] = hist_match["info"]["participants"][person]["championName"]
      tmp_end["effectiveHealAndShielding"] = hist_match["info"]["participants"][person]["challenges"]["effectiveHealAndShielding"]
      if hist_match['info']['participants'][person]['win']:
        tmp_end["win"] = 1
      for stat_data in dataset_end.columns[4:]:
        tmp_end[stat_data] = hist_match["info"]["participants"][person][stat_data]
      newrow_end = pd.DataFrame([tmp_end])
      dataset_end = pd.concat([dataset_end,newrow_end],ignore_index = True)

  dataset_end.to_csv(liste_name[itération] + ' Endgame.csv', sep=';', index=False)


  # on ajoute des joueurs à la liste de PUUID
  if itération < 2 :
    for game in range(len(history)):
        for j in range(10):
            puuid = history[game]['info']['participants'][j]['puuid']
            if (not(puuid in liste_PUUID)):
                liste_PUUID.append(puuid)
                liste_name.append(history[game]['info']['participants'][j]['riotIdGameName'])
  #on vérifie qu'il y a suffisament de joueurs à chercher
  print("taille de liste_PUUID = ",len(liste_PUUID))
      # il y a un sleep car on ne peut pas faire plus de 100 requetes toutes les 2mins
  t2 = (t1 + 125) - time.time() # le temps que l'on a fait
  #t2 positif => t1 + 121 > temps => on a fait moins de 125s
  if (t2>0):
    time.sleep(t2)






