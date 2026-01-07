#Etape 1
#Quel est le meilleur champion de LoL
#APARICIO Maxime, AMAZIT Alan, CAPIEU Valentin, POTTIER Anne, SEIGNOUX Vivien

import pandas as pd
import requests
import time
import copy


items_mapping = {
    1082: "Dark Seal",
    3070: "Tear",
    1056: "Doran Ring",
    1055: "Doran Blade",
    1083: "Cull",
    1054: "Doran Shield",
    1035: "Red Jung",  # Red Jung
    1039: "Blue Jung",   # Blue Jung
    1040: "Green Jung", # Green Jung
    3009: "Swiftness Boots",
    3020: "Sorcerer Boots",
    3158: "Lucidity Boots",
    3111: "Mercury Boots",
    3006: "Berserker Boots",
    3047: "Plated Boots",
    8020: "Abyssal Mask",
    3504: "Ardent Censer",
    6696: "Axiom Arc",
    3102: "Banshee's Veil",
    3071: "Black Cleaver",
    2503: "Blackfire torch",
    3153: "Blade of the Ruined King",
    3877: "Bloodsong",
    3072: "Bloodthirster",
    3869: "Celestial Opposition",
    6609: "Chempunk Chainsword",
    4629: "Cosmic Drive",
    3137: "Cryptbloom",
    6621: "Dawncore",
    3742: "Dead Man's Plate",
    6333: "Death's Dance",
    6620: "Echoes of Helia",
    6692: "Eclipse",
    3814: "Edge of Night",
    3508: "Essence Reaver",
    3073: "Experimental Hexplate",
    4401: "Force of Nature",
    3110: "Frozen Heart",
    3026: "Guardian Angel",
    3124: "Guinsoo's Rageblade",
    3084: "Heartsteel",
    3152: "Hextech Rocketbelt",
    6664: "Hollow Radiance",
    4628: "Horizon Focus",
    6697: "Hubris",
    3181: "Hullbreaker",
    6662: "Iceborn Gauntlet",
    6673: "Immortal Shieldbow",
    4005: "Imperial Mandate",
    3031: "Infinity Edge",
    6665: "Jak'Sho, The Protean",
    2504: "Kaenic Rookern",
    3109: "Knight's Vow",
    6672: "Kraken Slayer",
    6653: "Liandry's Anguish",
    6655: "Luden's Companion",
    3100: "Lich Bane",
    3190: "Locket of the Iron Solary",
    3036: "Lord Dominik's Regards",
    3118: "Malignance",
    3042: "Muramana",
    3156: "Maw of Malmortius",
    3041: "Mejai's Soulstealer",
    3139: "Mercurial Scimitar",
    3222: "Mikael's Blessing",
    6617: "Moonstone Renewer",
    3165: "Morellonomicon",
    3033: "Mortal Reminder",
    3115: "Nashor's Tooth",
    6675: "Navori Flickerblade",
    6701: "Opportunity",
    2501: "Overlords's Bloodmail",
    3046: "Phantom Dancer",
    6698: "Profane Hydra",
    3074: "Ravenous Hydra",
    3089: "Rabadon's Deathcap",
    3143: "Randuin's Omen",
    3094: "Rapid Firecannon",
    3107: "Redemption",
    4633: "Riftmaker",
    6657: "Rod of Ages",
    3085: "Runaan's Hurricane",
    3116: "Rylai's Crystal Scepter",
    3040: "Seraph's Embrace",
    6695: "Serpent's Fang",
    6694: "Serylda's Grudge",
    4645: "Shadowflame",
    2065: "Shurelya's Battlesong",
    3876: "Solstice Sleigh",
    3161: "Spear of Shojin",
    3065: "Spirit Visage",
    6616: "Staff of Flowing Water",
    3087: "Statikk Shiv",
    3053: "Sterak's Gage",
    4646: "Stormsurge",
    6631: "Stridebreaker",
    6610: "Sundered Sky",
    3068: "Sunfire Aegis",
    3302: "Terminus",
    6676: "The Collector",
    3075: "Thornmail",
    3748: "Titanic Hydra",
    3002: "Trailblazer",
    3078: "Trinity Force",
    3179: "Umbral Glaive",
    2502: "Unending Despair",
    4643: "Vigilant Wardstone",
    3135: "Void Staff",
    6699: "Voltaic Cyclosword",
    3083: "Warmog's Armor",
    3119: "Winter's Approach",
    3091: "Wit's End",
    3142: "Youmuu's Ghostblade",
    3032: "Yun Tal Wildarrows",
    3871: "Zaz'Zak's Realmspike",
    3050: "Zeke's Convergence",
    3157: "Zhonya's Hourglass"

}

dictio_end = {
  'MatchID': "",
  'Champ Name': "",
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
api_key = "RGAPI-d70773c8-8632"
nombre_de_joueur = 1000


liste_name = []
liste_name.append(nom_du_joueur)

requestPUUID = "https://" + region + ".api.riotgames.com/riot/account/v1/accounts/by-riot-id/" + nom_du_joueur +"/" + gametag +"?api_key=" + api_key
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

  print("len match = ",len(matches))

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



  dataset = pd.DataFrame(columns=['MatchID', 'Champ Name', 'Dark Seal', 'Tear', 'Doran Ring', 'Doran Blade', 'Cull', 'Doran Shield', 'Red Jung', 'Blue Jung', 'Green Jung', 'Swiftness Boots', 'Sorcerer Boots', 'Lucidity Boots',
                                  'Mercury Boots', 'Berserker Boots', 'Plated Boots', "Abyssal Mask", "Ardent Censer", "Axiom Arc", "Banshee's Veil", "Black Cleaver",
                                  "Blackfire torch", "Blade of the Ruined King", "Bloodsong", "Bloodthirster", "Celestial Opposition", "Chempunk Chainsword", "Cosmic Drive", "Cryptbloom", "Dawncore",
                                  "Dead Man's Plate", "Death's Dance", "Dream Maker", "Echoes of Helia", "Eclipse", "Edge of Night", "Essence Reaver", "Experimental Hexplate", "Force of Nature",
                                  "Frozen Heart", "Guardian Angel", "Guinsoo's Rageblade", "Heartsteel", "Hextech Rocketbelt", "Hollow Radiance", "Horizon Focus", "Hubris", "Hullbreaker",
                                  "Iceborn Gauntlet", "Immortal Shieldbow", "Imperial Mandate", "Infinity Edge", "Jak'Sho, The Protean", "Kaenic Rookern", "Knight's Vow", "Kraken Slayer", "Liandry's Anguish", "Lich Bane",
                                  "Locket of the Iron Solary", "Lord Dominik's Regards", "Luden's Companion", "Malignance", "Muramana", "Maw of Malmortius",
                                  "Mejai's Soulstealer", "Mercurial Scimitar", "Mikael's Blessing", "Moonstone Renewer", "Morellonomicon", "Mortal Reminder", "Nashor's Tooth", "Navori Flickerblade", "Opportunity",
                                  "Overlords's Bloodmail", "Phantom Dancer", "Profane Hydra", "Rabadon's Deathcap",
                                  "Randuin's Omen", "Rapid Firecannon", "Ravenous Hydra", "Redemption", "Riftmaker", "Rod of Ages", "Runaan's Hurricane", "Rylai's Crystal Scepter", "Seraph's Embrace", "Serpent's Fang", "Serylda's Grudge", "Shadowflame",
                                  "Shurelya's Battlesong", "Solstice Sleigh", "Spear of Shojin", "Spirit Visage", "Staff of Flowing Water", "Statikk Shiv", "Sterak's Gage", "Stormsurge", "Stridebreaker", "Sundered Sky",
                                  "Sunfire Aegis", "Terminus", "The Collector", "Thornmail", "Titanic Hydra", "Trailblazer", "Trinity Force", "Umbral Glaive", "Unending Despair", "Vigilant Wardstone", "Void Staff",
                                  "Voltaic Cyclosword", "Warmog's Armor", "Winter's Approach", "Wit's End", "Youmuu's Ghostblade", "Yun Tal Wildarrows", "Zaz'Zak's Realmspike", "Zeke's Convergence", "Zhonya's Hourglass", ])
  dictio = {
  'MatchID': "",
  'Champ Name': "",
  'Dark Seal' : 0,
  'Tear' : 0,
  'Doran Ring' : 0,
  'Doran Blade' : 0,
  'Cull' : 0,
  'Doran Shield' : 0,
  'Red Jung' : 0,
  'Blue Jung' : 0,
  'Green Jung' : 0,
  'Swiftness Boots' : 0,
  'Sorcerer Boots' : 0,
  'Lucidity Boots' : 0,
  'Mercury Boots' : 0,
  'Berserker Boots' : 0,
  'Plated Boots' : 0,
  "Abyssal Mask" : 0,
  "Ardent Censer" : 0,
  "Axiom Arc" : 0,
  "Banshee's Veil" : 0,
  "Black Cleaver" : 0,
    "Blackfire torch" : 0,
  "Blade of the Ruined King" : 0,
  "Bloodsong" : 0,
  "Bloodthirster" : 0,
  "Celestial Opposition" : 0,
  "Chempunk Chainsword" : 0,
  "Cosmic Drive" : 0,
  "Cryptbloom" : 0,
  "Dawncore" : 0,
  "Dead Man's Plate" : 0,
  "Death's Dance" : 0,
  "Dream Maker" : 0,
  "Echoes of Helia" : 0,
  "Eclipse" : 0,
  "Edge of Night" : 0,
  "Essence Reaver" : 0,
  "Experimental Hexplate" : 0,
  "Force of Nature" : 0,
  "Frozen Heart" : 0,
  "Guardian Angel" : 0,
  "Guinsoo's Rageblade" : 0,
  "Heartsteel" : 0,
  "Hextech Rocketbelt" : 0,
  "Hollow Radiance" : 0,
  "Horizon Focus" : 0,
  "Hubris" : 0,
  "Hullbreaker" : 0,
  "Iceborn Gauntlet" : 0,
  "Immortal Shieldbow" : 0,
  "Imperial Mandate" : 0,
  "Infinity Edge" : 0,
  "Jak'Sho, The Protean" : 0,
  "Kaenic Rookern" : 0,
  "Knight's Vow" : 0,
  "Kraken Slayer" : 0,
  "Liandry's Anguish" : 0,
  "Lich Bane" : 0,

  "Locket of the Iron Solary" : 0,
  "Lord Dominik's Regards" : 0,
  "Luden's Companion" : 0,
  "Malignance" : 0,
  "Muramana" : 0,
  "Maw of Malmortius" : 0,

  "Mejai's Soulstealer" : 0,
  "Mercurial Scimitar" : 0,
  "Mikael's Blessing" : 0,
  "Moonstone Renewer" : 0,
  "Morellonomicon" : 0,
  "Mortal Reminder" : 0,
  "Nashor's Tooth" : 0,
  "Navori Flickerblade" : 0,
  "Opportunity" : 0,

  "Overlords's Bloodmail" : 0,
  "Phantom Dancer" : 0,
  "Profane Hydra" : 0,
  "Rabadon's Deathcap" : 0,

  "Randuin's Omen" : 0,
  "Rapid Firecannon" : 0,
  "Ravenous Hydra" : 0,
  "Redemption" : 0,
  "Riftmaker" : 0,
  "Rod of Ages" : 0,
  "Runaan's Hurricane" : 0,
  "Rylai's Crystal Scepter" : 0,
  "Seraph's Embrace" : 0,
  "Serpent's Fang" : 0,
  "Serylda's Grudge" : 0,
  "Shadowflame" : 0,

  "Shurelya's Battlesong" : 0,
  "Solstice Sleigh" : 0,
  "Spear of Shojin" : 0,
  "Spirit Visage" : 0,
  "Staff of Flowing Water" : 0,
  "Statikk Shiv" : 0,
  "Sterak's Gage" : 0,
  "Stormsurge" : 0,
  "Stridebreaker" : 0,
  "Sundered Sky" : 0,

  "Sunfire Aegis" : 0,
  "Terminus" : 0,
  "The Collector" : 0,
  "Thornmail" : 0,
  "Titanic Hydra" : 0,
  "Trailblazer" : 0,
  "Trinity Force" : 0,
  "Umbral Glaive" : 0,
  "Unending Despair" : 0,
  "Vigilant Wardstone" : 0,
  "Void Staff" : 0,
  "Voltaic Cyclosword" : 0,
  "Warmog's Armor" : 0,
  "Winter's Approach" : 0,
  "Wit's End" : 0,
  "Youmuu's Ghostblade" : 0,
  "Yun Tal Wildarrows" : 0,
  "Zaz'Zak's Realmspike" : 0,
  "Zeke's Convergence" : 0,
  "Zhonya's Hourglass" : 0,
  }
  dataset_end = pd.DataFrame(columns=["MatchID",
  "Champ Name",
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
"effectiveHealAndShielding",
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

  #on met les items dans le dataset
  for hist_match in history:
    for person in range(10):
      tmp = copy.deepcopy(dictio)
      tmp['MatchID'] = hist_match['metadata']['matchId']
      tmp['Champ Name'] = hist_match["info"]["participants"][person]["championName"]
      for item in ["item0","item1","item2","item3","item4","item5","item6",]:
        if items_mapping.get(hist_match["info"]["participants"][person][item]) != None :
          tmp[items_mapping[hist_match["info"]["participants"][person][item]]] = 1
      newrow = pd.DataFrame([tmp])
      dataset = pd.concat([dataset,newrow],ignore_index = True)


  print("liste_name = ",liste_name)
  dataset.to_csv(liste_name[itération] + ' items.csv', sep=';', index=False)

  #   # partie permettant d'avoir les data endgame
  #
  # for hist_match in history:
  #   for person in range(10):
  #     tmp_end = copy.deepcopy(dictio_end)
  #     tmp_end['MatchID'] = hist_match['metadata']['matchId']
  #     tmp_end['Champ Name'] = hist_match["info"]["participants"][person]["championName"]
  #     for stat_data in dataset_end.columns[2:]:
  #       if stat_data == "effectiveHealAndShielding":
  #         tmp_end[stat_data] = hist_match["info"]["participants"][person]["challenges"][stat_data]
  #       else:
  #         tmp_end[stat_data] = hist_match["info"]["participants"][person][stat_data]
  #     #dataset = dataset.append(tmp,ignore_index = True)
  #     newrow_end = pd.DataFrame([tmp_end])
  #     dataset_end = pd.concat([dataset_end,newrow_end],ignore_index = True)
  #
  # dataset_end.to_csv(liste_name[itération] + ' Endgame.csv', sep=';', index=False)




















  # on ajoute des joueurs à la liste de PUUID
  if itération < 4 :
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

