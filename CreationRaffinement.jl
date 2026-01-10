"""
Dimitri Watel 2024
"""

import Pkg
println("Installing packages if necessary")
Pkg.add("LightGraphs", io=devnull)
Pkg.add("LaTeXTabulars", io=devnull)
Pkg.add("Printf", io=devnull)
Pkg.add("Combinatorics", io=devnull)
Pkg.add("DataStructures", io=devnull)
println("Done")

using LightGraphs
using LaTeXTabulars
using Printf
using Combinatorics
using DataStructures

"""
Taille des graphes
"""
GRAPH_SIZE = 5

"""
Nombre de noeuds dans une requête
Peut être un entier si une seule taille est autorisée
Peut être une liste si plusieurs tailles sont autorisées
"""
REQUEST_SIZE = 4

"""
Le nombre de partition a traiter, ce nombre peut être plus petit que le nombre total de partition car le programme peut s'excecuter bout a bout
"""


NOMBRE_EFFECTUE = 3000
"""
Seules les classes passant ce filtre sont affichées
"""
function class_filter(class)
  """
  Cette partie n'affiche que les class composé d'un seul graphe
  """
  reqs, graphs = class
  if length(graphs) == 1
    return true
  end
  return false

  k3i3 = 0
  for g in graphs
    if has_triangle(g, (4,5,6))
      if k3i3 == 2
        return true
      end
      k3i3 = 1
    else
      if k3i3 == 1
        return true
      end
      k3i3 = 2
    end
  end
  return false
end




function Nb_arete(subg,nodes)
  nb_arete = 0
  for i in nodes
    nb_arete += length(neighbors(subg, i))
  end
  return nb_arete/2
end
"""
Toutes les fonction " Is____" retournent 0 si le sous graphe possède ____ .
"""
function Is_clique(g, (i, j, k, l))
#has_edge(g, i, j) && has_edge(g, j, k) && has_edge(g, k, i) && has_edge(g, i, l) && has_edge(g, j, l) && has_edge(g, k, l)
  if ne(g) == 6
    return true
  end
  return false
end
function Is_nul(g, (i, j, k, l))
#!has_edge(g, i, j) && !has_edge(g, j, k) && !has_edge(g, k, i) && !has_edge(g, i, l) && !has_edge(g, j, l) && !has_edge(g, k, l)
  if ne(g) == 0
    return true
  end
  return false
end

function Is_Co_Diamond(g, (i, j, k, l))
    if ne(g) == 1
        return true
    end
    return false
end
function Is_Diamond(g, (i, j, k, l))
    if ne(g) == 5
        return true
    end
    return false
end

function Is_Co_paw(g, (i, j, k, l))
    if ne(g) == 2
        #On récupère les arêtes de g
        e1,e2 = collect(edges(g))
        if src(e1) == src(e2) || src(e1) == dst(e2) || dst(e1) == src(e2) || dst(e1) == dst(e2)
            return true
        end
    end
    return false
end
function Is_paw(g, (i, j, k, l))
    if ne(g) == 4
        for v in vertices(g)
            if length(neighbors(g,v)) == 3
                return true
            end
        end
    end
    return false
end

function Is_Co_C4(g, (i, j, k, l))
    if ne(g) == 2
        #On récupère les arêtes de g
        e1,e2 = collect(edges(g))
        if !(src(e1) == src(e2) || src(e1) == dst(e2) || dst(e1) == src(e2) || dst(e1) == dst(e2))
            return true
        end
    end
    return false
end
function Is_C4(g, (i, j, k, l))
    if ne(g) == 4
        for v in vertices(g)
            if length(neighbors(g,v)) == 3
                return false
            end
        end
        return true
    end
    return false
end

function Is_claw(g, (i, j, k, l))
    if ne(g) == 3
        for v in vertices(g)
            if length(neighbors(g,v)) == 3
                return true
            end
        end
    end
    return false
end
function Is_Co_claw(g, (i, j, k, l))
    if ne(g) == 3
        for v in vertices(g)
            if length(neighbors(g,v)) == 0
                return true
            end
        end
    end
    return false
end

function Is_P4(g, (i, j, k, l))
  if ne(g) == 3
    for v in vertices(g)
        if length(neighbors(g,v)) == 0 || length(neighbors(g,v)) == 3
            return false # on est pas un P4
        end
    end
    return true
  end
    return false
end





"""
Requête à tester
On suppose que length(nodes) == REQUEST_SIZE si REQUEST_SIZE est un entier 
ou que length(nodes) ∈ REQUEST_SIZE si REQUEST_SIZE est une liste d'entiers
"""


function request(g, nodes,P)
    D = Dict(
    'a' => Is_clique,
    'b' => Is_nul,
    'c' => Is_Co_Diamond,
    'd' => Is_Diamond,
    'e' => Is_Co_paw,
    'f' => Is_paw,
    'g' => Is_Co_C4,
    'h' => Is_C4,
    'i' => Is_claw,
    'j' => Is_Co_claw,
    'k' => Is_P4
)
  subg, _ = induced_subgraph(g, nodes) # obligatoire pour les fonction Is___
  P = split(P, "|")
  for partie in 1:length(P)
    for s in P[partie]
        if D[s](subg, [1,2,3,4])
            return partie
        end
    end
  end
  return "erreur dans request, le graphe indique ne correspond a aucun graphe repertorie"
end



"""
Renvoie REQUEST_SIZE sous forme de tableau trié
"""
function get_request_sizes()
  if REQUEST_SIZE isa Number
    sizes = [REQUEST_SIZE]
  else
    sizes = REQUEST_SIZE
  end

  sort!(sizes)
  return sizes
end

function graph_filter(g)
  return true
end
"""
Renvoie le graphe à n noeuds dont les arêtes sont données par le tableau bin
Renvoie nothing si le graphe ne passe pas le filtre graph_filter
- bin : tableau de binaires contenant n n-1 / 2 valeurs. Les n (n-1) / 2 couples de 
noeuds sont ordonnés (1, 2), (1, 3), (1, n), ..., (i, j), (i, j + 1), ..., (n-1, n)
Le i-e couple est relié par une arête si bin[i] est 1
"""
function get_graph(n, bin)
  g = SimpleGraph(n)

  # Ajout des arêtes
  index = 1
  for i in 1:n
    for j in (i + 1):n
      if bin[index] == 1
        add_edge!(g, i, j)
      end
      index += 1
    end
  end

  # On vérifie les filtres
  if !graph_filter(g)
    return nothing
  end

  return g
end

"""
Enumère tous les graphes étiquetés de taille n qui passent le filtre graph_filter
"""
function enumerate_graphs(n)
  m = n * (n-1) ÷ 2
  
  # Binaire qui correspond à la présence ou non des arêtes
  bin = [0 for _ in 1:m]

  graphs = []

  index = 0

  # Tant que le binaire n'est pas [1 1 1 ... ]
  while 0 in bin
    index += 1

    g = get_graph(n, bin)
    if !isnothing(g)
      push!(graphs, g)
    end

    # On ajoute 1 au binaire
    for i in 1:m
      if bin[i] == 0
        bin[i] = 1
        break
      end
      bin[i] = 0
    end

  end

  # On construit le dernier graphe, la clique, correspondant au binaire [1 1 1 ... 1]
  g = get_graph(n, bin)
  if !isnothing(g)
    push!(graphs, g)
  end
  
  return graphs
end

"""
Renvoie un tableau contenant, pour l'ensemble des tuples ordonnés de noeuds de g,
le résultat de la requête `request`. 

Les tuples sont de taille REQUEST_SIZE si REQUEST_SIZE est un nombre.
Si REQUEST_SIZE est une liste alors la taille est tuple doit être dans la liste. 

Les tuples sont considérés par ordre de taille. Le premier triplet considéré par le tableau Vdest (1, 2, 3), le suivant est (1, 2, 4), ..., le dernier est (n-2, n-1, n).
"""
function all_requests(g,partition,P)
  sizes = get_request_sizes()
  n = nv(g)
  nodes = vertices(g)
  reqs = Dict()
  if partition == 0 #le mode classique
    for size in sizes
      for c in combinations(1:n, size)
        reqs[c] = request(g, [nodes[i] for i in c],P)
      end
    end
  else # lors du deuxième appel avec comparaison
    for size in sizes
      for c in combinations(1:n, size)
        reqs[c] = request_2(g, [nodes[i] for i in c])
      end
    end
  end
  return reqs
end

"""
Calcule pour chaque graphe, les résultats des requêtes obtenues avec `all_requests`. 
Ensuite, crée les classes d'équivalentes en fonction de ces résultats : deux graphes avec 
les mêmes résultats sont dans la même classe. 
Renvoie le dictionnaire qui à chaque résultat possible de requêtes associe les graphes de la 
classe associée. 

Si n vaut zéro alors on ne fait les requêtes que sur les graphes de liste_graphe
"""
function get_classes(n,liste_graphe,P)
  classes = OrderedDict()
  if n!=0
    graphs = enumerate_graphs(n)
    for g in graphs
      reqs = all_requests(g,0,P)
      # Si c'est la première fois qu'on observe ce résultat de requêtes, on le rentre dans le dictionnaire
      # et on l'associe à une liste vide.
      if !(reqs ∈ keys(classes))
        # Attention, on a un Dict de Dict
        # Il ne faut pas modifier reqs par la suite
        # sous peine de ne plus pouvoir le retrouver
        # dans classes
        classes[reqs] = []
      end
      # On ajoute g à la liste des graphes associés au résultat de requête
      push!(classes[reqs], g)
    end
    #on filtre le premier passage
    return Dict(reqs => graphs for (reqs, graphs) in classes if class_filter((reqs, graphs)))
  else
    for g in liste_graphe
      reqs = all_requests(g,1)
      # Si c'est la première fois qu'on observe ce résultat de requêtes, on le rentre dans le dictionnaire
      # et on l'associe à une liste vide.
      if !(reqs ∈ keys(classes))
        # Attention, on a un Dict de Dict
        # Il ne faut pas modifier reqs par la suite
        # sous peine de ne plus pouvoir le retrouver
        # dans classes
        classes[reqs] = []
      end
      # On ajoute g à la liste des graphes associés au résultat de requête
      push!(classes[reqs], g)
    end
    # on ne filtre pas le deuxième passage
    return classes
  end


end

"""
P est une partition ( sous forme a|bc|d ), n l'ordre du graphe
"""
function ajouteraf(P,n)
  classes = get_classes(n,[],P)
  return length(classes)
end

function creation(n,D)
  nombre_total_graphe = 2^((n*(n-1))/2)
  nombre_effectue = 0
  for (partition,val) in json_data
    if length(val) == 1 # ATTENTION, cela dépend du nombre d'ordre que l'on a déjà fait
      # si on a déjà fait pour n = 5 et n = 6, il faudrait mettre "==2" pour fait 7
      if nombre_effectue > NOMBRE_EFFECTUE
        return 0
      end
      nombre_effectue += 1
      println("partition en cours : ",partition)
      #D[partition] = Dict{Int, Any}() # a changer
      push!(D[partition], string(n) => ajouteraf(partition,n)/nombre_total_graphe)
    end
  end
  println("Toutes les partition ont été faite")
end



#ajouteraf("a|b|c|d|e|f|g|h|i|j|k" ,GRAPH_SIZE)
#"cdijk|abefgh"


using JSON
json_data = open("graphe_raffinement.json", "r") do io
    JSON.parse(io)
end

GRAPH_SIZE = 6
creation(GRAPH_SIZE,json_data)

open("graphe_raffinement.json", "w") do io
    JSON.print(io, json_data)
end





#\documentclass{article}
#\usepackage{tikz}
#\begin{document}
"""
Ce programme permet de remplir la base de donné disant le nombre de graphe reconstructible pour chaque ordre

ATTENTION : le nombre dans la base de donné (entre 0 et 1) est le nombre de graphe reconstructible a.k.a le nombre de classe composé d'un seul élément.


Pour savoir le nombre de graphe reconstructible, dans class_filter on ne garde que les classes de taille 1
Pour avoir toutes les classes il faut changer class_filter
"""

