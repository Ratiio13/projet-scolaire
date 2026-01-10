using JSON
json_data = open("testraffinement.json", "r") do io
    JSON.parse(io)
end



"""
Pour requêter la base avec la partition P et l'ordre n, il faut utiliser : json_data[P][string(n)] 
"""

"""
P1 et P2 sont des partitions
Cette fonction rend la différence du pourcentage de graphe reconstructible
"""
function Difference(P1,P2,n,json_data)
    return json_data[P1][string(n)] - json_data[P2][string(n)]
end
println(Difference("adg|bk|ch|e|f|i|j","ad|g|bk|ch|e|f|i|j",5,json_data))
