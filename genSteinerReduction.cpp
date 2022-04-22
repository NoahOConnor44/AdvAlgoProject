/*

Input: 
    - Weighted undirected graph in edge list format (weighted_graph.txt)
    - Required nodes in the solution (required_vertices.txt)

Output: 
    Complete weighted graph satisfying the triangle inequality in edge list format (Edges are listed redundantly.)
    and a set of required vertices (the same as given in input)

Assumptions:
    The graph given as input is a connected graph. (You can reach all vertices through some means if not directly connected)

*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int INF = 999;

void readFile(ifstream& fin, double** graph);
void readReqNodes(ifstream& fin, vector<int>& reqNodes);
void printReqVertices(const vector<int> reqNodes);
void freeGraph(double **graph, int numNodes);
void floydWarshallAlgo(double **graph, int numNodes);

int main(int argc, char** argv)
{
    ifstream inGraph;
    ifstream inReqVertices;

    // stores nodeNums for required vertices
    vector<int> requiredNodes;

    int numNodes;
    
    inGraph.open("weighted_graph.txt");
    inReqVertices.open("required_vertices.txt");

    if(!inGraph || !inReqVertices)
    {
        cout << "weighted_graph.txt and required_vertices.txt expected as input. \n";
        exit(EXIT_FAILURE);
    }

    inGraph >> numNodes;

    double **graph;

    // init the graph
    graph = new double*[numNodes];

    for(int i = 0; i < numNodes; i++)
    {
        graph[i] = new double[numNodes];
    }

    // sentintel value for edges with no costs
    for(int i = 0; i < numNodes; i++)
    {
        for(int j = 0; j < numNodes; j++)
        {
            // we are on a diagonal, no loops so set distance from self->self to 0
            if(i == j)
            {
                graph[i][j] = 0;
            }
            else
            {
                graph[i][j] = INF;
            } 
        }
    }

    readReqNodes(inReqVertices, requiredNodes);
    readFile(inGraph, graph);

    cout << "Metric Steiner Tree Problem Instance (Some edges are redundant) \n";
    floydWarshallAlgo(graph, numNodes);

    cout << "Set of required vertices for Metric Steiner Tree: \n";
    printReqVertices(requiredNodes);

    freeGraph(graph, numNodes);

    return EXIT_SUCCESS;
}

// read the weighted_graph.txt file to create our graph representation with each
// vertices edge connections and weights 
void readFile(ifstream& fin, double** graph)
{
    int u, v;
    double weight;

    // vertice #'s are counted from zero in file so can reference their location directly
    while(fin >> u >> v >> weight)
    {
        // row = u
        // col = v
        // value = weight from u to v
        graph[u][v] = weight;
        graph[v][u] = weight;
    }
}

// read the required_vertices.txt file to store the nodes that must be part of the solution
void readReqNodes(ifstream& fin, vector<int>& reqNodes)
{
    int nodeNum;

    while(fin >> nodeNum)
    {
        reqNodes.push_back(nodeNum);
    }
}

// Print the vertices that are required in the steiner tree solution
void printReqVertices(const vector<int> reqNodes)
{  
    for(int i = 0; i < reqNodes.size(); i++)
    {
        cout << reqNodes.at(i) << " ";
    }
    cout << endl;
}

/*
    Find the all source shortest path to assign edges to the new metric graph
    This will fill in any edges if the input graph was not complete with an edge value
    that satisfies the inequality triangle. This does the same thing if a complete
    graph was given as input.

    Code referenced from GeeksForGeeks.com for this Algorithm
*/
void floydWarshallAlgo(double **graph, int numNodes)
{
    double **metricGraph;
    metricGraph = new double*[numNodes];

    for(int i = 0; i < numNodes; i++)
    {
        metricGraph[i] = new double[numNodes];
    }

    // set metric graph to the starting graph provided as input
    for(int i = 0; i < numNodes; i++)
    {
        for(int j = 0; j < numNodes; j++)
        {
            metricGraph[i][j] = graph[i][j];
        }
    }

   // Compute the shortest edge lengths from u to v for all nodes and update 
   // the metricGraph with the minimum value for each path.

   // intermediate nodes
    for (int intermediate = 0; intermediate < numNodes; intermediate++) 
    {
        // start nodes
        for (int u = 0; u < numNodes; u++) 
        {
            // end nodes
            for (int v = 0; v < numNodes; v++) 
            {
                // Cost from u to v is greater than using an intermediate route.
                if (metricGraph[u][v] > (metricGraph[u][intermediate] + metricGraph[intermediate][v]))
                {
                    // Make sure the path is using a valid route thats defined from the input file
                    if(metricGraph[intermediate][v] != INF && metricGraph[u][intermediate] != INF)
                    {
                        // Update path from u to v with the shorter cost / weight using the intermediate node
                        metricGraph[u][v] = metricGraph[u][intermediate] + metricGraph[intermediate][v];
                    }
                }
            }
        }
    }

    // print out the final solution (n*(n-1)) edges in edge list format
   for(int i = 0; i < numNodes; i++)
   {
       for(int j = 0; j < numNodes; j++)
       {
            if ((metricGraph[i][j] != INF && metricGraph[i][j] > 0))
            {
                cout << i << " " << j << " " << metricGraph[i][j] << "\n";
            }
       }
   }

    // deallocate dynamic memory
   freeGraph(metricGraph, numNodes);
}

void freeGraph(double **graph, int numNodes)
{
    for(int i = 0; i < numNodes; i++)
    {
        delete[] graph[i];
    }
    delete[] graph;
}
