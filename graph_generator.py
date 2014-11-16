from random import randint
def graph_input():
    V = int(raw_input("Enter the number of Nodes: "))
    E = int(raw_input("Enter the number of Edges: "))
    Q = int(raw_input("Enter the capacity of the garbage van: "))

    adj_matrix = []
 # Initialize the adjacency matrix
    for i in range(0, V):
        temp = []
        for j in range(0, V):
            temp.append(0)
        adj_matrix.append(temp)
    
    for i in range(0, E):
        #s = raw_input()
        #u, v, w = s.split()
        # Choose vertices and the weights randomly
        u = randint(0, V-1)
        v = randint(0, V-1)
        w = randint(1, Q)
        adj_matrix[v][u] = adj_matrix[u][v] = w

 # print the adjacency matrix
    for i in range (0, V):
        print adj_matrix[i]

    return adj_matrix

graph = graph_input()
