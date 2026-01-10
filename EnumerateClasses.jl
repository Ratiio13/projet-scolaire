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
Nombre de graphes affichés par ligne dans le pdf final
"""
LINEBREAKLIMIT = 3

"""
Nombre max de classes affichées dans le dossier latex
Si LATEX_MAX_CLASSES est nothing, affiche toutes les classes
"""
LATEX_MAX_CLASSES = nothing
# LATEX_MAX_CLASSES = 100

"""
Fichier .tex où sera écrit le résultat.
Si RESULT_FILE est nothing alors un résumé du résultat est écrit en console
"""
#RESULT_FILE = nothing 
RESULT_FILE = "./result.tex"

"""
Nombre de noeuds dans une requête
Peut être un entier si une seule taille est autorisée
Peut être une liste si plusieurs tailles sont autorisées
"""
REQUEST_SIZE = 3

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
  return true
  reqs, graphs = class
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
Requête à tester
On suppose que length(nodes) == REQUEST_SIZE si REQUEST_SIZE est un entier 
ou que length(nodes) ∈ REQUEST_SIZE si REQUEST_SIZE est une liste d'entiers
"""
function request(g, nodes)
  (i, j, k) = nodes
  if has_edge(g, i, j) && has_edge(g, j, k) && has_edge(g, k, i)
    return 0
  end
  if !has_edge(g, i, j) && !has_edge(g, j, k) && !has_edge(g, k, i)
    return 0
  end
  return 1
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
"""
function get_classes(n)
  graphs = enumerate_graphs(n)

  classes = OrderedDict()
  for g in graphs
    reqs = all_requests(g)
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

  # Filtrage
  return Dict(reqs => graphs for (reqs, graphs) in classes if class_filter((reqs, graphs)))

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
  classes = get_classes(n)
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
  classes = get_classes(n)
  title_index = 0
  for reqs in collect(keys(classes))
    if !isnothing(LATEX_MAX_CLASSES) && title_index >= LATEX_MAX_CLASSES
      break
    end

    graphs = classes[reqs]

    
    # Titre
    title_index += 1
    
    # Tableau du résultat de requêtes

    println(io, "\\documentclass{article}")
    println(io, "\\usepackage{tikz}")
    println(io, "\\usepackage{booktabs}")
    println(io, "\\begin{document}")
    println(io, "\\begin{center}")
    draw_requests(io, n, reqs)
    println(io, "\\end{center}")
    
    # Le longfigure permet à latex de découper la figure sur plusieurs pages
    println(io, "\\begin{longfigure}{c}")
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
    println(io, "\\end{longfigure}")

    # Saut de page
    println(io, "\\newpage")
  end
  println(io, "\\end{document}")
end



if isnothing(RESULT_FILE)
  print_classes_summary(GRAPH_SIZE)
else
  open(RESULT_FILE, "w") do io
    draw_classes(io, GRAPH_SIZE)
  end
end

#\documentclass{article}
#\usepackage{tikz}
#\begin{document} 
