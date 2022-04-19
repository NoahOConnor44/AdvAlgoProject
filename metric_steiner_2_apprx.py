#Code to solve the 2-approximation for metric Steiner Tree
#Involves running an Minimal Spanning Tree algorithm on the required vertices of a metric Steiner Tree

def mst(e, w, vertices):
    edge_list = list()
    weight_list = list()
    num_of_edges = 0
    #create a list of possible weights
    for k in w.keys():
        for v in w[k]:
            if v not in weight_list:
                weight_list.append(v)
    #sort the list from least to greatest
    weight_list.sort()
    #start at the smallest weights
    for x in weight_list:
        for u in e.keys():
            for v in range(0, len(e[u])):
                if w[u][v] == x:
                    #check if new edge would create a cycle
                    if not cycle(edge_list, [u,e[u][v]], vertices):
                        #make sure there are no repeats
                        if [e[u][v], u] not in edge_list:
                            edge_list.append([u, e[u][v]])
                            num_of_edges = num_of_edges + 1
                            #exit when # of edges is v - 1
                            if num_of_edges == vertices - 1:
                                return edge_list

def cycle(e, new_edge, v):
    if len(e) is 0:
        return False
    edge_list = e.copy()
    v1 = new_edge[0]
    v2 = new_edge[1]
    adjacency_list = dict()
    for i in range(0, v):
        adjacency_list.update({i:[]})
    #create an adjacency list to see what vertices each vertex is connected to
    for k in adjacency_list.keys():
        for edge in edge_list:
            if edge[0] == k:
                adjacency_list[k].append(edge[1])
            elif edge[1] == k:
                adjacency_list[k].append(edge[0])
    #if new edge has a vertex that is not connected to another, return false
    if len(adjacency_list[v1]) == 0 or len(adjacency_list[v2]) == 0:
        return False
    visited = list()
    #jump to recursive algorithm
    return cycle_aux(adjacency_list, visited, v1, v2)

#Here we are searching for v2 while starting at v1
def cycle_aux(a, v, n, f):
    #if we get to a point where there is no vertices connected, return False
    if len(a[n]) == 0:
        return False
    #if we find the vertex we are looking for, return True
    if f in a[n]:
        return True
    else:
        for x in a[n]:
            #if we have not visited vertex x
            if x not in v:
                #append it list of visited vertices
                v.append(x)
                if cycle_aux(a, v, x, f) is True:
                    return True
                else:
                    return False

if __name__ == "__main__":
    #Grabbing input from the files
    graph_file = open('weighted_graph.txt')
    required_vertex_file = open('required_vertices.txt')
    #Getting the total vertices in graph
    total_vertices = int(graph_file.readline())
    edges = dict()
    weights = dict()
    #initializing the dictionary of edges and weights
    for i in range(0, total_vertices):
        edges.update({i:[]})
        weights.update({i:[]})
    #populating edges and weights
    for line in graph_file:
        line = line.strip()
        numbers = line.split(' ')
        num_array = list()
        for num in numbers:
            num_array.append(float(num))
        num_array[0] = int(num_array[0])
        num_array[1] = int(num_array[1])
        #populating the edges with their correct weights
        edges[num_array[0]].append(num_array[1])
        weights[num_array[0]].append(num_array[2])
        edges[num_array[1]].append(num_array[0])
        weights[num_array[1]].append(num_array[2])

    #grabbing required vertices
    required_vertices = list()
    line = required_vertex_file.readline()
    line = line.strip()
    numbers = line.split(' ')
    for num in numbers:
        required_vertices.append(int(num))

    required_vertices.sort()

    #creating new dictionaries with only the required vertices
    new_edges = dict()
    new_weights = dict()
    for r in required_vertices:
        new_value = list()
        new_weight = list()
        for val in range(0,len(edges[r])):
            if edges[r][val] in required_vertices:
                new_value.append(edges[r][val])
                new_weight.append(weights[r][val])
        new_edges.update({r:new_value})
        new_weights.update({r:new_weight})

    #run the Minimal Spanning Trees algorithm on the required vertices and print the edges in the tree
    print(mst(new_edges, new_weights, len(required_vertices)))