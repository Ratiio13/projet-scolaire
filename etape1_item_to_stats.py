#Etape 2
#Quel est le meilleur champion de LoL
#APARICIO Maxime, AMAZIT Alan, CAPIEU Valentin, POTTIER Anne, SEIGNOUX Vivien

import copy
import pandas as pd
df = pd.read_csv('grouped_items_final.csv',sep=';')

Champ_Name = df.iloc[:, 0]
print(Champ_Name)
df = df.drop(['Champ Name','Dream Maker'], axis=1)




items_dict ={
 1082: {"Ability power":15, "Health":50},
 3070: {"Mana": 240},
 1056: {"Ability power": 18, "Health":90},
 1055: {"Attack damage": 10, "Health": 80, "Lifesteal": 3},
 1083:{"Attack damage": 7},
 1054: {"Health": 110, "Flat Health regen": 4},
 1035:{},
 1039:{},
 1040:{},
 3006: {"Flat Movement Speed": 45, "Attack speed": 25},
 3009: {"Flat Movement Speed": 60},
 3158: {"Flat Movement Speed": 45, "Ability haste": 10},
 3111: {"Flat Movement Speed": 45, "Magic resistance": 20, "Tenacity": 30},
 3047: {"Flat Movement Speed": 45, "Armor": 25},
 3020: {"Flat Movement Speed":45, "Magic pen.": 15},


 8020:{"Ability haste": 15, "Health": 300, "Magic resistance": 45},
 3504:{"Ability power": 45, "Mana regen": 125, "Movement speed": 4, "Heal & shield power":
 10},
 6696:{"Attack damage": 55, "Ability haste": 20, "Lethality": 18},
 3102:{"Ability power": 105, "Magic resistance": 40},
 3071:{"Attack damage": 40, "Ability haste": 20, "Health": 400},
 2503:{"Ability power": 80, "Ability haste": 20, "Mana": 600},
 3153:{"Attack damage": 40, "Attack speed": 25, "Lifesteal": 10, "damage on hit": 1},
 3877:{"Health":200, "Health regen":75, "Mana regen":75, "Gold generation":5},
 3072:{"Attack damage":80, "Lifesteal":15},
 3869:{"Health":200, "Health regen":75, "Mana regen":75, "Gold generation": 5},
 6609:{"Attack damage": 45, "Ability haste": 15, "Health": 450},
4629:{"Ability power": 70, "Ability haste": 25, "Health": 350, "Movement speed": 4},
 3137:{"Ability power": 60, "Ability haste": 15, "Magic pen.": 30},
 6621:{"Ability power": 45, "Mana regen": 100, "Heal & shield power": 16},
 3742:{"Health": 350, "Armor": 55, "Movement speed": 4},
 6333:{"Attack damage": 60, "Ability haste": 15, "Armor": 50},
 3870:{"Health":200, "Health regen":75, "Mana regen":75, "Gold generation":5},
 6620:{"Ability power": 35, "Ability haste": 20, "Health": 200, "Mana regen": 125},
 6692:{"Attack damage": 60, "Ability haste": 15},
 3814:{"Attack damage": 50, "Lethality": 15, "Health": 250},
 3508:{"Attack damage": 60, "Ability haste": 15, "Critical strike chance": 25},
 3073:{"Attack damage": 40, "Attack speed": 20, "Health": 450},
 4401:{"Health": 400, "Magic resistance": 55, "Movement speed": 4},
 3110:{"Ability haste": 20, "Armor": 75, "Mana": 400},
 3026:{"Attack damage": 55, "Armor": 45},
 3124:{"Attack damage": 30, "Attack speed": 25, "Ability power": 30, "damage on hit" : 1},
 3084:{"Health":900, "Health regen":100},
 3152:{"Ability haste": 15, "Health": 350, "Ability power": 60},
 6664:{"Ability haste": 10, "Health": 400, "Health regen": 100, "Magic resistance": 40},
 4628:{"Ability power": 75, "Ability haste": 25},
 6697:{"Attack damage": 60, "Ability haste": 10, "Lethality": 18},
 3181:{"Attack damage": 40, "Movement speed": 4, "Health": 500},
 6662:{"Ability haste": 15, "Health": 300, "Armor": 50},
 6673:{"Attack damage": 55, "Critical strike chance": 25},
 4005:{"Ability power": 60, "Ability haste": 20, "Mana regen": 125},
 3031:{"Attack damage": 70, "Critical strike chance": 25, "Critical strike damage": 40},
 6665:{"Health": 350, "Armor": 45, "Magic resistance": 45},
 2504:{"Health":400, "Health regen":100, "Magic resistance":80},
 3109:{"Health":200, "Health regen":100, "Armor":40, "Ability haste":10},
 6672:{"Attack damage": 45, "Attack speed": 40, "Movement speed": 4, "damage on hit" : 1},
 6653:{"Ability power": 70, "Health": 300},
 6655: {"Ability power": 100, "Ability haste":10, "Mana":600},
 3100:{"Ability power": 115, "Ability haste": 10, "Movement speed": 4},

 3190: {"Ability haste": 10, "Health": 200, "Armor": 25, "Magic resistance": 25},
 3036: {"Attack damage": 35, "Critical strike chance": 25, "Armor pen.": 35},

 3118:{"Ability power": 85, "Ability haste": 15, "Mana": 600},
 3042: {"Attack damage": 35, "Ability haste": 15, "Mana": 860, "damage on hit": 1},
 3156:{"Attack damage": 60, "Ability haste": 15, "Magic resistance": 40},

 3041:{"Ability power": 20, "Health": 100},
 3139:{"Attack damage": 40, "Magic resistance": 40, "Lifesteal": 10},
 3222:{"Ability haste": 15, "Health":250, "Mana regen": 100, "Heal & shield power":12},
 6617:{"Ability power": 25, "Ability haste": 20, "Health": 200, "Mana regen":125},
 3165:{"Ability power": 75, "Ability haste": 15, "Health": 350},
 3033:{"Attack damage": 35, "Critical strike chance": 25, "Armor pen.": 30},
 3115:{"Ability power": 80, "Ability haste":15, "Attack speed": 50, "damage on hit":1},
 6675:{"Attack speed": 40, "Critical strike chance":25, "Movement speed": 4},
 6701:{"Attack damage": 50,"Movement speed": 4, "Lethality": 15},

 2501:{"Attack damage": 30, "Health": 550},
 3046:{"Attack speed": 60, "Critical strike chance": 25, "Movement speed": 8},
 6698:{"Attack damage": 60, "Ability haste": 10, "Lethality": 18},
 3074:{"Attack damage": 65, "Ability haste": 15, "Lifesteal": 12},
 3089:{"Ability power": 130},
 3143:{"Health": 350, "Armor": 75},
 3094:{"Attack speed": 35, "Critical strike chance": 25, "Movement speed": 4},
 3107:{"Ability haste": 15, "Health": 200, "Mana regen": 100, "Heal & shield power": 10},
 4633:{"Ability power": 70, "Ability haste": 15, "Health": 350},
 6657:{"Ability power": 50, "Health": 400, "Mana": 400},



 3157:{"Ability power": 105, "Armor": 50},
 3050:{"Ability haste": 10, "Health": 300, "Armor": 25, "Magic resistance": 25},
 3871:{"Health": 200, "Health regen": 75, "Mana regen": 75, "Gold generation": 5},
 3032:{"Attack damage": 50, "Attack speed": 20, "damage on hit": 1},
 3142:{"Attack damage": 60, "Lethality": 18},
 3091:{"Attack speed": 50, "Magic resistance": 45,"Tenacity": 20, "damage on hit":1},
 3119:{"Ability haste": 15, "Health": 550, "Mana": 500},
 3083:{"Health": 1000, "Health regen": 100, "Movement speed": 4},
 6699:{"Attack damage": 55, "Ability haste": 10, "Lethality": 18},
 3135:{"Ability power": 95, "Magic pen.": 40},
 4643:{"Ability haste": 20, "Health":250, "Armor": 25, "Magic resistance": 30},
 2502:{"Ability haste": 10, "Health": 350, "Armor": 60},
 3179:{"Attack damage": 50, "Ability haste": 10, "Lethality": 15},
 3078:{"Attack damage": 36, "Ability haste": 15, "Attack speed": 30, "Health": 333},
 3002:{"Health": 250, "Armor": 40, "Movement speed": 4},
 3748:{"Attack damage": 40, "Health": 600},
 3075:{"Health": 150, "Armor": 75},
 6676:{"Attack damage": 50, "Critical strike chance": 25, "Lethality": 10},
 3302:{"Attack damage": 30, "Attack speed": 35, "damage on hit" : 1},
 3068:{"Ability haste": 10, "Health": 350, "Armor": 50},
 6610:{"Attack damage": 40, "Ability haste": 10, "Health": 400},
 6631:{"Attack damage": 40, "Attack speed": 25, "Health": 450},
 4646:{"Ability power": 90, "Movement speed": 4, "Magic pen.":15},
 3053:{"Health": 400, "Tenacity": 20},
 3087:{"Attack damage": 50, "Attack speed": 35, "Movement speed": 4},
 6616:{"Ability power": 35, "Ability haste": 15, "Mana regen": 125, "Heal & shield power":
 10},
 3065:{"Ability haste": 10, "Health": 400, "Health regen": 100, "Magic resistance": 50},
 3161:{"Attack damage": 45, "Health": 450},
 3876:{"Health": 200, "Health regen": 75, "Mana regen": 75, "Gold generation": 5},
 2065:{"Ability power": 50, "Ability haste": 15, "Mana regen": 125, "Movement speed": 4},
 4645:{"Ability power": 110, "Magic pen.": 15},
 6694:{"Attack damage": 45, "Ability haste": 20, "Armor pen.": 30},
 6695:{"Attack damage": 55, "Lethality": 15},
 3040:{"Ability power": 70, "Ability haste": 25, "Mana": 1000},
 3116:{"Ability power": 65, "Health": 400},
 3085:{"Attack speed": 40, "Critical strike chance": 25, "Movement speed": 4, "damage on hit" : 1},

 }


#___________________________________ICI_DEBUT__________________________________

old_items_mapping = {
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
#on inverse le mapping ci dessus
items_mapping = {v: k for k, v in old_items_mapping.items()}

#___________________________________________ICI_FIN_______________________________________________

### par calcul matriciel
#création de la matrice item to stats



Liste_items = ['MatchID', 'Champ Name', 'Dark Seal', 'Tear', 'Doran Ring', 'Doran Blade', 'Cull', 'Doran Shield', 'Red Jung', 'Blue Jung', 'Green Jung', 'Swiftness Boots', 'Sorcerer Boots', 'Lucidity Boots',
                                  'Mercury Boots', 'Berserker Boots', 'Plated Boots', "Abyssal Mask", "Ardent Censer", "Axiom Arc", "Banshee's Veil", "Black Cleaver",
                                  "Blackfire torch", "Blade of the Ruined King", "Bloodsong", "Bloodthirster", "Celestial Opposition", "Chempunk Chainsword", "Cosmic Drive", "Cryptbloom", "Dawncore",
                                  "Dead Man's Plate", "Death's Dance", "Echoes of Helia", "Eclipse", "Edge of Night", "Essence Reaver", "Experimental Hexplate", "Force of Nature",
                                  "Frozen Heart", "Guardian Angel", "Guinsoo's Rageblade", "Heartsteel", "Hextech Rocketbelt", "Hollow Radiance", "Horizon Focus", "Hubris", "Hullbreaker",
                                  "Iceborn Gauntlet", "Immortal Shieldbow", "Imperial Mandate", "Infinity Edge", "Jak'Sho, The Protean", "Kaenic Rookern", "Knight's Vow", "Kraken Slayer", "Liandry's Anguish", "Lich Bane",
                                  "Locket of the Iron Solary", "Lord Dominik's Regards", "Luden's Companion", "Malignance", "Muramana", "Maw of Malmortius",
                                  "Mejai's Soulstealer", "Mercurial Scimitar", "Mikael's Blessing", "Moonstone Renewer", "Morellonomicon", "Mortal Reminder", "Nashor's Tooth", "Navori Flickerblade", "Opportunity",
                                  "Overlords's Bloodmail", "Phantom Dancer", "Profane Hydra", "Rabadon's Deathcap",
                                  "Randuin's Omen", "Rapid Firecannon", "Ravenous Hydra", "Redemption", "Riftmaker", "Rod of Ages", "Runaan's Hurricane", "Rylai's Crystal Scepter", "Seraph's Embrace", "Serpent's Fang", "Serylda's Grudge", "Shadowflame",
                                  "Shurelya's Battlesong", "Solstice Sleigh", "Spear of Shojin", "Spirit Visage", "Staff of Flowing Water", "Statikk Shiv", "Sterak's Gage", "Stormsurge", "Stridebreaker", "Sundered Sky",
                                  "Sunfire Aegis", "Terminus", "The Collector", "Thornmail", "Titanic Hydra", "Trailblazer", "Trinity Force", "Umbral Glaive", "Unending Despair", "Vigilant Wardstone", "Void Staff",
                                  "Voltaic Cyclosword", "Warmog's Armor", "Winter's Approach", "Wit's End", "Youmuu's Ghostblade", "Yun Tal Wildarrows", "Zaz'Zak's Realmspike", "Zeke's Convergence", "Zhonya's Hourglass", ]
# on met les stats des items

ITS = pd.DataFrame(columns= ["Movement speed", "Ability power", "Armor", "Ability haste", "Health", "Magic resistance",
 "Mana", "Mana regen", "Heal & shield power", "Health regen", "Gold generation", "Attack damage", "Attack speed", "Lethality", "Lifesteal", "Tenacity", "Flat Health regen", "Magic pen.",
 "Flat Movement Speed", "Critical strike chance", "Armor pen.", "Critical strike damage", "damage on hit"],index=Liste_items[2:])

# Nouvelle ligne sous forme de DataFrame
dictio = {"Movement speed": 0, "Ability power": 0, "Armor": 0, "Ability haste": 0, "Health": 0, "Magic resistance": 0, "Mana": 0, "Mana regen": 0, "Heal & shield power": 0, "Health regen": 0, "Gold generation": 0, "Attack damage": 0, "Attack speed": 0, "Lethality": 0, "Lifesteal": 0, "Tenacity": 0, "Flat Health regen": 0, "Magic pen.": 0, "Flat Movement Speed": 0, "Armor pen.": 0, "Critical strike damage": 0, "Critical strike chance": 0,  "damage on hit":0}


#création de la matrice ITS faisant le lien entre item et statistique
for item in Liste_items[2:]:# on prend toute les colonnes sauf MatchID et Champ Name
  for statistique,value in items_dict[items_mapping[item]].items():
    ITS[statistique][item] = value
# on met des zéro là où on a ajouter aucune statistique
ITS.fillna(0, inplace=True)

#on multiplie le dataset des items avec ITS
result = df.dot(ITS)


result = pd.concat([Champ_Name, result], axis=1, ignore_index=True)

result.to_csv('grouped_stats_final.csv', sep=';', index=False)

