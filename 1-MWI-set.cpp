#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <math.h>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

using namespace std;

vector<int> findNodes(string str);
double findWeight(string str);


int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "usage: main.o input.txt" << endl;
        return 0;
    }

    ifstream inputFile;
    string str;
    int nodesCount;
    inputFile.open(argv[1]);

    vector<int> nodes;
    vector<int> vertices;
    double weight;

    if(inputFile) {
        getline(inputFile, str);
        nodesCount = stoi(str);

        // for storing total weight of each node
        double weightNodes[nodesCount];
        // for storing neighbor nodes using edges
        vector<int> edges[nodesCount];

        while (getline(inputFile, str))
        {
            vertices = findNodes(str);
            weight = findWeight(str);

            // in edges array each node will have all of its edged nodes
            // so here we make both nodes to store each other as neighbors
            edges[vertices[0]].push_back(vertices[1]);
            edges[vertices[1]].push_back(vertices[0]);

            // add up the weight for both nodes
            weightNodes[vertices[0]] += weight;
            weightNodes[vertices[1]] += weight;
        }

        // find max weighted node
        int maxWeight = 0;
        int maxWeightIndex = 0;
        for (int i = 0; i < nodesCount; i++) {
            if (weightNodes[i] > maxWeight) {
                maxWeight = weightNodes[i];
                maxWeightIndex = i;
            }
        }

        cout << "Maximum Weighted Node is: " << maxWeightIndex << endl;
        cout << "Maximum-weight-independent Set is: " << endl;
        for (auto itr = edges[maxWeightIndex].begin(); itr != edges[maxWeightIndex].end(); itr++)
            cout << *itr << " ";
        cout << "\n";
    } else {
        cout << "invalid file\n" << endl;
    }

}

vector<int> findNodes(string str) {
    vector<int> nodes;
    int index=0;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (isspace(str[i])) {
            nodes.push_back(stoi(str.substr(index, i)));
            index=i;
        }
    }

    return nodes;
}

double findWeight(string str) {
    int index=0;
    double w;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (isspace(str[i])) index=i;
    }

    w = stod(str.substr(index, str.size()));
    return w;
}
