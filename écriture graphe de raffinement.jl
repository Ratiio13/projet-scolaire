#ce programme n'est pas parfaitement optimisé car on parcours tout le graphe et on met les raffinement dans un dico séparément
#f2 écrit bien le bon rafinement

using JSON


D = Dict()
D2 = Dict()
L = ["a","b","c","d","e","f","g","h","i","j","k"]
println("taille de L = ",length(L))
"""
rend une liste composé des sous listes de taille n-1, c'est a dire que chaque sous liste contient tout les éléments de L,sauf pour deux éléments, qui sont concaténés
"""
function prochain_raf(L)
    result = []
    for i in 1:(length(L))
        for j in (i+1):length(L)
            L2 = [L[1:(i-1)] ; L[i]*L[j] ; L[(i+1):(j-1)] ;  L[(j+1):length(L)]]
            L2 = [join(sort(collect(s))) for s in L2]
            append!(result, [join(L2, "|")])    
        end
    end
    return result
end



"""
ajoute à L_suivant tout les rafinement de  ( direct ou non ), et pour chacun, l'ajoute en tant que clé dans D, avec comme value, les prochains rafinements
depart1 et depart2, permettent la bonne éxecution des recurtions,

à initialiser avec :
f(L,1,2,D)

"""

"""
Les arêtes vont de abc vers a|b|c ( le bon sens )
ATTENTION, dans la liste des sommets suivant, on a des doublons
"""

function f2(L,depart1,depart2,D)
    for j in (depart2):length(L)
        L2 = [L[1:(depart1-1)] ; L[depart1]*L[j] ; L[(depart1+1):(j-1)] ;  L[(j+1):length(L)]]
        f2(L2,depart1,j,D)

        raf = prochain_raf(L2)
        value = join(L2, "|")
        for el in raf
            push!(get!(D,el,String[]),value)
        end
    end 

    for i in (depart1+1):(length(L))
        for j in (i+1):length(L)

            L2 = [L[1:(i-1)] ; L[i]*L[j] ; L[(i+1):(j-1)] ;  L[(j+1):length(L)]]
            f2(L2,i,j,D)
            raf = prochain_raf(L2)
            value = join(L2, "|")
            for el in raf
                push!(get!(D,el,String[]),value)
            end
        end
    end
    raf = prochain_raf(L)
    value = join(L, "|")
    for el in raf
        push!(get!(D,el,String[]),value)
    end
    D[join(L, "|")] = []
    return D
end

#f2(L,1,2,D2)


"""
Les arêtes vont de a|b|c vers abc ( le mauvais sens )
"""
function f(L,depart1,depart2,D)
    for j in (depart2):length(L)
        L2 = [L[1:(depart1-1)] ; L[depart1]*L[j] ; L[(depart1+1):(j-1)] ;  L[(j+1):length(L)]]
        f(L2,depart1,j,D)

        D[join(L2, "|")] = prochain_raf(L2)
    end 

    for i in (depart1+1):(length(L))
        for j in (i+1):length(L)

            L2 = [L[1:(i-1)] ; L[i]*L[j] ; L[(i+1):(j-1)] ;  L[(j+1):length(L)]]
            f(L2,i,j,D)
            D[join(L2, "|")] = prochain_raf(L2)
        end
    end
    return D
end
f(L,1,2,D)

# on rajoute la partition composé de singletons
D[join(L, "|")] = prochain_raf(L)


D3= Dict()
#dans D3, on met l'inverse de D
function reverse(D,D3)
    for (cle,valeur) in D
        for el in valeur
            if !haskey(D3,el)
                D3[el] = []
            end
            push!(D3[el], cle)
        end
    end
end
reverse(D,D3)
D3[join(L, "|")] = []
println("taille de D3 = ",length(D3))

"""
for (cle,val) in D
    if !haskey(D2,cle)
        println("clé manquante : ", cle)
    end
end
"""

println("taille de D2 = ",length(D2))
println("taille de D = ",length(D))

# Sauvegarde dans un fichier Json
open("raffinement_inverse.json", "w") do io
    JSON.print(io, D)
end
"""
RESULTATS : 
taille de L => nombre de partition différentes
11 => 678570
5 => 52
4 => 15


"""
