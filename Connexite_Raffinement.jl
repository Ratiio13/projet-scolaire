"""
Pour faire la connexité des raffinements

"""


# on lit les donnée contenant quels graphes est un raffinement de quel graphe
using JSON
data_raffinement = open("raffinement.json", "r") do io
    JSON.parse(io)
end
# on lit les donnée contenant le pourcentage de graphe reconstructible
data_aretes = open("graphe_raffinement.json", "r") do io
    JSON.parse(io)
end

GRAPH_SIZE = "5"
RAFFINEMENT_DEPART =  "abefgh|cdijk"

proucentage_reference = data_aretes[RAFFINEMENT_DEPART][GRAPH_SIZE]
println("reférence : ",RAFFINEMENT_DEPART, " ",proucentage_reference)

liste_raff = [RAFFINEMENT_DEPART]
i = []
push!(i,0)
while(i[1] != length(liste_raff))
    i[1] +=1
    println(length(data_raffinement[liste_raff[i[1]]]))
    for raff in data_raffinement[liste_raff[i[1]]]
        if (length(data_aretes[raff]) !=0) && (data_aretes[raff][GRAPH_SIZE] == proucentage_reference)# la première partie du && permet de se proteger si les données sont incomplètes
            println(raff, " ",data_aretes[raff][GRAPH_SIZE])
            if !(raff in liste_raff)
                push!(liste_raff,raff)
            end
        end
    end
end
println(liste_raff)
println("i = ",i[1])

# la parité :"abefgh|cdijk"
