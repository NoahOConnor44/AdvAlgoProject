
import itertools
import networkx as nx
from networkx.classes.function import subgraph
from networkx.readwrite import edgelist
from networkx.algorithms.euler import eulerian_circuit

#converts input text file to nx graph
def read_input(in_txt: str):
    nodes = []
    G = nx.Graph()
    with open(in_txt) as file:
        next(file)
        line = file.readline()
        while line:
            contents = line.replace("\n", "").split(" ")
            nodes.append((contents[0], contents[1], contents[2]))
            line = file.readline()

    if len(nodes) > 0:
        G.add_weighted_edges_from(nodes)
        return G

def print_graph(graph):
    print(list(graph.edges.data()))

def MST(graph_initial):
    
    e = graph_initial.edges()
    weighted_e = {}
    graph_mst = nx.Graph()
    n = []

    #Kruskal's Algorithm
    for (node_u, node_v) in e:
        weighted_e[(node_u, node_v)] = int(graph_initial.get_edge_data(node_u, node_v)["weight"])
    weighted_e = sorted(weighted_e.items(), key = lambda x: x[1])

    for m in weighted_e:
        x, y = m[0]
        edge_weight = graph_initial.get_edge_data(x, y)["weight"]
        graph_mst.add_edge(x, y, weight = edge_weight)
        try:
            nx.algorithms.find_cycle(graph_mst)
            graph_mst.remove_edge(x, y)
        except nx.NetworkXNoCycle:
            n.append(x)
            n.append(y)
    return graph_mst

def MCPM(T, G):
    # calculate degrees
    deg = {}
    odd_deg = {}
    for x in T.degree():
        deg[x[0]] = x[1]
    # T.has_edge();
    # calculate odd degrees
    for y in deg.keys():
        if (deg[y]%2) != 0 :
            odd_deg[y] = deg[y]
    print("Odd degrees: ", odd_deg)

    # create subgraph
    print("Subgraph: ")
    T_subgraph = nx.Graph(G.subgraph(odd_deg))
    print_graph(T_subgraph)

    # minimum perfect matching
    Mgraph = nx.Graph()
    for edge in T_subgraph.edges():
        if not T.has_edge(edge[0],edge[1]):
            Mgraph.add_edge(edge[0], edge[1], weight = -int((T_subgraph.get_edge_data(edge[0], edge[1])["weight"])))
    match = nx.max_weight_matching(Mgraph, maxcardinality = True)
    M = nx.Graph()
    for x in match:
        M.add_edge(x[0], x[1], weight = T_subgraph.get_edge_data(x[0], x[1])["weight"])
    print("M:")
    print_graph(M)

    # add M to T
    MT = nx.MultiGraph()
    for edge in M.edges():
        MT.add_edge(edge[0], edge[1], weight = M.get_edge_data(edge[0], edge[1])["weight"])
        #MT.add_edge(edge[0], edge[1], weight = None)
    for edge in T.edges():
        MT.add_edge(edge[0], edge[1], weight = T.get_edge_data(edge[0], edge[1])["weight"])
        #MT.add_edge(edge[0], edge[1], weight = None)
    
    return MT



def euler_tour(MT, G):
    et = eulerian_circuit(MT)
    e_tour = []
    for x in et:
        e_tour.append(x)
    print("Euler tour:", e_tour)

    euler_graph = nx.Graph()
    for edge in e_tour:
        euler_graph.add_edge(edge[0], edge[1], weight = G.get_edge_data(edge[0], edge[1])["weight"])

    e_tour = list(itertools.chain.from_iterable(list(e_tour)))
    e_tour = list(dict.fromkeys(e_tour).keys())
    e_tour.append(e_tour[0]);
    return e_tour

def TS_Tour(eulertour, G):
    TST = nx.DiGraph()
    for x in range(len(eulertour)-1):
        TST.add_edge(eulertour[x],eulertour[x+1], weight = G.get_edge_data(eulertour[x],eulertour[x+1])["weight"])
    print("Traveling Salesmen Tour:")
    print_graph(TST)

    #cost of tour
    c = 0
    for x in range(1, len(eulertour)):
        c += int(G.get_edge_data(eulertour[x-1],eulertour[x])["weight"])
    print("Cost: ", c)
    
def main():
    in_txt = r"DATA\32TSP\input1.txt"
    G = read_input(in_txt)
    print("Input Graph:")
    print_graph(G)
    G_complete = nx.complete_graph(list(G.nodes))
    if nx.is_isomorphic(G, G_complete):    

        # Step 1. Find a Minimum Spanning tree on initial graph
        T = nx.Graph()
        T = MST(G)
        print("MST Graph T:")
        print_graph(T)

        # Step 2. Compose a min. cost perfect matching, M, on the set of odd-degree vertices of T. Add M to T.
        MT = MCPM(T, G)
        print("Minimum cost perfect matching (MT):")
        print_graph(MT)
        print("Degree of MT: ", MT.degree)

        # Step 3. Find a Euler Tour of this graph
        eulertour = euler_tour(MT, G)
        print(eulertour)

        # Step 4. Shortcut Euler tour to get the traveling salesmen tour
        TS_Tour(eulertour, G)

    else:
        print("Incomplete graph. Try again.")


    


if __name__ == "__main__":
    main()
