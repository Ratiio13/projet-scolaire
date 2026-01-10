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
GRAPH_SIZE = 8


"""
Nombre de graphes affichés par ligne dans le pdf final
"""
LINEBREAKLIMIT = 3

"""
Nombre max de classes affichées dans le dossier latex
Si LATEX_MAX_CLASSES est nothing, affiche toutes les classes
"""
LATEX_MAX_CLASSES = nothing
#LATEX_MAX_CLASSES = 100

"""
Fichier .tex où sera écrit le résultat.
Si RESULT_FILE est nothing alors un résumé du résultat est écrit en console
"""
RESULT_FILE = nothing 
RESULT_FILE = "./result.tex"




"""
Si COMPARAISON est true, alors on compare deux partitions. Pour changer les partitions, il faut modifier request_2 et request.
Il faut que RESULT_FILE soit différent de nothing 
"""
COMPARAISON = false
"""
Nombre de noeuds dans une requête
Peut être un entier si une seule taille est autorisée
Peut être une liste si plusieurs tailles sont autorisées
"""
REQUEST_SIZE = 6

function has_triangle(g, nodes)
  (i, j, k) = nodes
  if has_edge(g, i, j) && has_edge(g, j, k) && has_edge(g, k, i)
    return true
  end
  return false
end

function has_i3(g, nodes)
  (i, j, k) = nodes
  if !has_edge(g, i, j) && !has_edge(g, j, k) && !has_edge(g, k, i)
    return true
  end
  return false
end

"""
Filtre de graphes, seuls les graphes filtrés sont conservés
"""
function graph_filter(g)
  return true
  if !has_triangle(g, (1,2,3))
    return false
  end
  if !has_triangle(g, (4,5,6)) && !has_i3(g, (4, 5, 6))
    return false
  end
  return true
end

"""
Seules les classes passant ce filtre sont affichées
"""
function class_filter(class)
  """
  return true

  reqs, graphs = class
  for (cle,value) in reqs
    if value != 0
      return false
    end
  end
  """



  """
  Cette partie n'affiche que les class composé de plus de deux éléments
  """
  reqs, graphs = class
  if length(graphs) >= 2
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





"""
retourne le nombre d'arêtes dans le sous graphe
"""
function Nb_arete(subg,nodes)
  return ne(subg)
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
  if Nb_arete(g,(i, j, k, l)) == 6
    return 1
  end
  return 0
end
function Is_nul(g, (i, j, k, l))
#!has_edge(g, i, j) && !has_edge(g, j, k) && !has_edge(g, k, i) && !has_edge(g, i, l) && !has_edge(g, j, l) && !has_edge(g, k, l)
  if Nb_arete(g,(i, j, k, l)) == 0
    return 1
  end
  return 0
end

function Is_Co_Diamond(g, (i, j, k, l))
    if Nb_arete(g,(i, j, k, l)) == 1
        return 1
    end
    return 0
end
function Is_Diamond(g, (i, j, k, l))
    if Nb_arete(g,(i, j, k, l)) == 5
        return 1
    end
    return 0
end

function Is_Co_paw(g, (i, j, k, l))
    if Nb_arete(g,(i, j, k, l)) == 2
        #On récupère les arêtes de g
        e1,e2 = collect(edges(g))
        if src(e1) == src(e2) || src(e1) == dst(e2) || dst(e1) == src(e2) || dst(e1) == dst(e2)
            return 1
        end
    end
    return 0
end
function Is_paw(g, (i, j, k, l))
    if Nb_arete(g,(i, j, k, l)) == 4
        for v in vertices(g)
            if length(neighbors(g,v)) == 3
                return 1
            end
        end
    end
    return 0
end

function Is_Co_C4(g, (i, j, k, l))
    if Nb_arete(g,(i, j, k, l)) == 2
        #On récupère les arêtes de g
        e1,e2 = collect(edges(g))
        if !(src(e1) == src(e2) || src(e1) == dst(e2) || dst(e1) == src(e2) || dst(e1) == dst(e2))
            return 1
        end
    end
    return 0
end
function Is_C4(g, (i, j, k, l))
    if Nb_arete(g,(i, j, k, l)) == 4
        for v in vertices(g)
            if length(neighbors(g,v)) == 3
                return 0
            end
        end
        return 1
    end
    return 0
end

function Is_claw(g, (i, j, k, l))
    if Nb_arete(g,(i, j, k, l)) == 3
        for v in vertices(g)
            if length(neighbors(g,v)) == 3
                return 1
            end
        end
    end
    return 0
end
function Is_Co_claw(g, (i, j, k, l))
    if Nb_arete(g,(i, j, k, l)) == 3
        for v in vertices(g)
            if length(neighbors(g,v)) == 0
                return 1
            end
        end
    end
    return 0
end

function Is_P4(g, (i, j, k, l))
  if Nb_arete(g,(i, j, k, l)) == 3
    for v in vertices(g)
        if length(neighbors(g,v)) == 0 || length(neighbors(g,v)) == 3
            return 0 # on est pas un P4
        end
    end
    return 1
  end
    return 0
end





"""
Requête à tester
On suppose que length(nodes) == REQUEST_SIZE si REQUEST_SIZE est un entier 
ou que length(nodes) ∈ REQUEST_SIZE si REQUEST_SIZE est une liste d'entiers
"""
function request(g, nodes)
  subg, _ = induced_subgraph(g, nodes) # obligatoire pour les fonction Is___
  return ne(subg)%2


  
  #Pour les singletons
  """
  if Is_P4(subg, [1,2,3,4]) + Is_claw(subg, [1,2,3,4]) + Is_Co_claw(subg, [1,2,3,4]) + Is_C4(subg, [1,2,3,4]) + Is_Co_C4(subg, [1,2,3,4]) + Is_paw(subg, [1,2,3,4]) + Is_Co_paw(subg, [1,2,3,4]) + Is_Diamond(subg, [1,2,3,4])  + Is_Co_Diamond(subg, [1,2,3,4]) + Is_clique(subg, [1,2,3,4]) + Is_nul(subg, [1,2,3,4]) >=2
    println("on a un porblème de multiclass")
    println(Is_P4(subg, [1,2,3,4]) , Is_claw(subg, [1,2,3,4]) , Is_Co_claw(subg, [1,2,3,4]) , Is_C4(subg, [1,2,3,4]) , Is_Co_C4(subg, [1,2,3,4]) , Is_paw(subg, [1,2,3,4]) , Is_Co_paw(subg, [1,2,3,4]) , Is_Diamond(subg, [1,2,3,4])  , Is_Co_Diamond(subg, [1,2,3,4]) , Is_clique(subg, [1,2,3,4]) , Is_nul(subg, [1,2,3,4]))
  end
  """
  return 11*Is_P4(subg, [1,2,3,4,5,6]) + 10*Is_claw(subg, [1,2,3,4,5,6]) + 9*Is_Co_claw(subg, [1,2,3,4,5,6]) + 8*Is_C4(subg, [1,2,3,4,5,6])   +  7*Is_Co_C4(subg, [1,2,3,4,5,6]) + 5*Is_paw(subg, [1,2,3,4,5,6]) + 4*Is_Co_paw(subg, [1,2,3,4,5,6]) + 3*Is_Diamond(subg, [1,2,3,4,5,6])  + 2*Is_Co_Diamond(subg, [1,2,3,4,5,6]) + 1*Is_clique(subg, [1,2,3,4,5,6]) + 0*Is_nul(subg, [1,2,3,4,5,6])
  
end

function request_2(g, nodes)
  subg, _ = induced_subgraph(g, nodes) # obligatoire pour les fonction Is___
  if Is_P4(subg, [1,2,3,4]) + Is_claw(subg, [1,2,3,4]) + Is_Co_claw(subg, [1,2,3,4]) + Is_C4(subg, [1,2,3,4]) + Is_Co_C4(subg, [1,2,3,4]) + Is_paw(subg, [1,2,3,4]) + Is_Co_paw(subg, [1,2,3,4]) + Is_Diamond(subg, [1,2,3,4])  + Is_Co_Diamond(subg, [1,2,3,4]) + Is_clique(subg, [1,2,3,4]) + Is_nul(subg, [1,2,3,4]) >=2
    println("on a un porblème de multiclass")
    println(Is_P4(subg, [1,2,3,4]) , Is_claw(subg, [1,2,3,4]) , Is_Co_claw(subg, [1,2,3,4]) , Is_C4(subg, [1,2,3,4]) , Is_Co_C4(subg, [1,2,3,4]) , Is_paw(subg, [1,2,3,4]) , Is_Co_paw(subg, [1,2,3,4]) , Is_Diamond(subg, [1,2,3,4])  , Is_Co_Diamond(subg, [1,2,3,4]) , Is_clique(subg, [1,2,3,4]) , Is_nul(subg, [1,2,3,4]))
  end
  return 11*Is_P4(subg, [1,2,3,4]) + 10*Is_claw(subg, [1,2,3,4]) + 9*Is_Co_claw(subg, [1,2,3,4]) + 8*Is_C4(subg, [1,2,3,4])   +  7*Is_Co_C4(subg, [1,2,3,4]) + 5*Is_paw(subg, [1,2,3,4]) + 4*Is_Co_paw(subg, [1,2,3,4]) + 3*Is_Diamond(subg, [1,2,3,4])  + 2*Is_Co_Diamond(subg, [1,2,3,4]) + 1*Is_clique(subg, [1,2,3,4]) + 0*Is_nul(subg, [1,2,3,4])

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
    if index % 2^8 == 0
      println(index, " ", 2^m)
    end

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
function all_requests(g)
  sizes = get_request_sizes()
  n = nv(g)
  nodes = vertices(g)
  reqs = Dict()
    for size in sizes
      for c in combinations(1:n, size)
        reqs[c] = request(g, [nodes[i] for i in c])
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
function get_classes(n,liste_graphe)
  classes = OrderedDict()






    graphs = enumerate_graphs(n)
    for g in graphs
      reqs = all_requests(g,0)
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
end

function all_zeros(d)
    all(v -> v == 0, values(d))
end


function do_each_graph(io,n)
    println(io, "\\documentclass{article}")
    println(io, "\\usepackage{tikz}")
    println(io, "\\usepackage{booktabs}")
    println(io, "\\begin{document}")
    println(io, "taille des requetes : ",REQUEST_SIZE)
    ### On énumère tout les graphes
    m = n * (n-1) ÷ 2
    # Binaire qui correspond à la présence ou non des arêtes
    bin = [0 for _ in 1:m]


    index = 0

    # Tant que le binaire n'est pas [1 1 1 ... ]
    while 0 in bin
    index += 1
    if index % 2^8 == 0
        println(index, " ", 2^m)
    end

    g = get_graph(n, bin)
    if !isnothing(g)
        ###On fait les requetes sur ce graphe
        req = all_requests(g)
        ### on regarde si le graphe est dans la même classe que In
        if all_zeros(req)
            draw_graph(io, g)
        end
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
    println(io, "fin du doc")
    println(io, "\\end{document}")
end



"""
Affiche dans le flux io un tableau latex correspondant au résultat de requêtes reqs.
"""
function draw_requests(io, n, reqs)

  """
  Renvoie ce qui doit être affiché dans la cellule du tableau correspondant aux noeuds de la requête
  Sinon affiche "X" si la requête renvoie vrai et rien sinon.
  """
  function get_cell(c)
    result = reqs[c]
    if result === true
      return "X"
    elseif result === false
      return ""
    else
      # Si result n'est pas un booléen, on le renvoie directement
      return string(result)
    end
  end

  # On utilise Tabular qui transforme un tableau Julia en tableau Latex
  # tb permet de générer la première ligne du tableau (avec les alignements)
  # Le tableau est un tableau ) 6 colonnes. Chaque colonne impaire contient un ensemble de noeuds et la case à droite contient le résultat associé

  tb = Tabular("c c c c c c")

  sizes = get_request_sizes()

  # Lignes du tableau
  lines = [
                Rule(:top), # Filet horizontal supérieur,
                repeat(["Noeuds", "Requête"], 3),
                Rule(:mid) # Filet horizontal intermédiaire
               ]

  requests_lines = collect(Iterators.flatten([[join(c, ", "), get_cell(c)]
                          for size in sizes for c in combinations(1:n, size)]))

  for i in 1:6:length(requests_lines)
    push!(lines, requests_lines[i:min(i + 5, end)])
  end

  push!(lines, Rule(:bottom))

  latex_tabular(io, tb, lines)
end

"""
Affiche dans le flux io un dessin tikz correspondant au graphe g. Le graphe est encadré. 
Note : TikzGraphs n'est pas utilisé parce que je ne comprends pas comment obtenir le résultat souhaité
"""
function draw_graph(io, g)
  println(io, "\\begin{tikzpicture}")
  println(io, "\\tikzset{tinoeud/.style={draw, circle, minimum height=0.01cm}}")
  
  # Clip pour espacer un peu atours du graphe
  println(io, "\\clip (-2, -2) rectangle (2, 2);")

  # Rectangle pour faire joli
  println(io, "\\draw (-1.95, -1.95) rectangle (1.95, 1.95);")

  # On affiche les noeuds en cercle
  n = nv(g)
  for i in 1:n
    angle = (i-1) * (360 ÷ n)
    @printf(io, "\\node[tinoeud] (V%d) at (%d:1.5cm) {%d};\n", i, angle, i)
  end

  # On affiche les arêtes
  for i in 1:n
    for j in (i + 1):n
      if has_edge(g, i, j)
        @printf(io, "\\draw (V%d) -- (V%d);\n", i, j)
      end
    end
  end

  println(io, "\\end{tikzpicture}")
end

"""
Affiche, un résumé des classes : pour chaque taille de classe affiche le nombre de classes contenant cette taille.
"""
function print_classes_summary(n)
  classes = get_classes(n,[])
  println("nombre de classes différentes = ",length(classes))
  size_to_nbclasses = SortedDict()
  for (reqs, graphs) in classes
    size = length(graphs)
    if !(size ∈ keys(size_to_nbclasses))
      size_to_nbclasses[size] = 0
    end
    size_to_nbclasses[size] += 1
  end

  @printf("Affichage des classes\n")
  for (size, nb) in size_to_nbclasses
    @printf("Classes de taille %03d : %05d\n", size, nb)
  end
end

"""
Affiche dans le flux io un document latex affichant toutes les classes d'équivalences de taille supérieure à 1. Pour chaque classe le document contient : une section, le tableau des résultats de requêtes, les graphes et un saut de page.
"""
function draw_classes(io, n)
  classes = get_classes(n,[])
  title_index = 0
  println(io, "\\documentclass{article}")
  println(io, "\\usepackage{tikz}")
  println(io, "\\usepackage{booktabs}")
  println(io, "\\begin{document}")
  println(io, "taille des requetes : ",REQUEST_SIZE)
  for reqs in collect(keys(classes))
    if !isnothing(LATEX_MAX_CLASSES) && title_index >= LATEX_MAX_CLASSES
      break
    end

    graphs = classes[reqs]

    
    # Titre
    title_index += 1
    
    # Tableau du résultat de requêtes
    #\documentclass{article}
#\usepackage{tikz}
#\begin{document} 
    
    println(io, "\\begin{center}")
    draw_requests(io, n, reqs)
    println(io, "\\end{center}")
    
    # Le longfigure permet à latex de découper la figure sur plusieurs pages
    #println(io, "\\begin{longfigure}{c}")
    println(io, "\\\\")

    # Affichage des graphes
    # A chaque fois que index vaut 0, on fait un saut de ligne (sinon tous les graphes sont sur la même ligne)
    index = LINEBREAKLIMIT 
    for g in graphs
      draw_graph(io, g)
      index -= 1
      if index == 0
        println(io, "\\\\")
        index = LINEBREAKLIMIT
      end
    end
    #println(io, "\\end{longfigure}")

    # Saut de page
    println(io, "\\newpage")
  end
  println(io, "fin du doc")
  println(io, "\\end{document}")
end


open(RESULT_FILE, "w") do io
    do_each_graph(io, GRAPH_SIZE)
end
#\documentclass{article}
#\usepackage{tikz}
#\begin{document}

"""
On énumère tout les graphes, 
Pour chaque graphe, on fait les requetes sur ce graphe, puis, s'il est dans la même classe que In, on le draw
"""