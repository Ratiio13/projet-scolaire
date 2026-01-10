"""
Pour faire la connexité des raffinements

"""


# on lit les donnée contenant quels graphes est un raffinement de quel graphe
using JSON
data_raffinement = open("raffinement.json", "r") do io
    JSON.parse(io)
end
data_raffinement_inverse = open("raffinement_inverse.json", "r") do io
    JSON.parse(io)
end
# on lit les donnée contenant le pourcentage de graphe reconstructible
data_aretes = open("graphe_raffinement.json", "r") do io
    JSON.parse(io)
end

GRAPH_SIZE = "5"
RAFFINEMENT_DEPART =  "abefgh|cdij|k"
Tout = "abcdefghijk"

# on cree un set de toutes les partitions, puis, a chaque fois qu'on ajoute une partition, on l'enlève du set. Ainsi, dans le set on a seulement les partitions qui n'ont pas encore été ajouté
Partie_a_faire = Set()
push!(Partie_a_faire, Tout)

for k in keys(data_aretes)
    push!(Partie_a_faire,k)
end

proucentage_reference = data_aretes[RAFFINEMENT_DEPART][GRAPH_SIZE]
println("reférence : ",RAFFINEMENT_DEPART, " ",proucentage_reference)

while (length(Partie_a_faire) >=0)
    RAFFINEMENT_DEPART = first( du set ) # on prend un élément qui n'as pas encore été fait
    #cette partie permet de trouver toutes les partitions relié à RAFFINEMENT_DEPART, dans les deux sens du raffinement
    RAFFINEMENT_DEPART = first( du set )
    liste_raff = [RAFFINEMENT_DEPART]
    i = []
    push!(i,0)
    while(i[1] != length(liste_raff))
        i[1] +=1
        println(length(data_raffinement_inverse[liste_raff[i[1]]]))
        for raff in data_raffinement[liste_raff[i[1]]]
            if (length(data_aretes[raff]) !=0) && (data_aretes[raff][GRAPH_SIZE] == proucentage_reference)# la première partie du && permet de se proteger si les données sont incomplètes
                println(raff, " ",data_aretes[raff][GRAPH_SIZE])
                if !(raff in liste_raff)
                    push!(liste_raff,raff)
                    #on enlève raff du set
                end
            end
        end
        for raff in data_raffinement_inverse[liste_raff[i[1]]]
            if (length(data_aretes[raff]) !=0) && (data_aretes[raff][GRAPH_SIZE] == proucentage_reference)# la première partie du && permet de se proteger si les données sont incomplètes
                println(raff, " ",data_aretes[raff][GRAPH_SIZE])
                if !(raff in liste_raff)
                    push!(liste_raff,raff)
                    #on enlève raff du set
                end
            end
        end
    end



println(liste_raff)
println("i = ",i[1])

# la parité :"abefgh|cdijk"
# Tout = "abcdefghijk"

