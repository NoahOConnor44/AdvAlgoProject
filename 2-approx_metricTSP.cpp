#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<vector<unsigned long>> adj_list;
vector<vector<double>> edgeList;
vector<vector<double>> MSTedges;
vector<double> MSTnodes, nodeList, dfs_list;
map<double, vector<double>> Euler_adjlist, graph_adjlist;
vector<double> eulerTour;
int totNodes;

void addEdge(double u, double v, double w) {
    edgeList.push_back({w, u, v});
    if (find(nodeList.begin(), nodeList.end(), u) == nodeList.end())
        nodeList.push_back(u);
    if (find(nodeList.begin(), nodeList.end(), v) == nodeList.end())
        nodeList.push_back(v);
    graph_adjlist[u].push_back(v);
    graph_adjlist[v].push_back(u);
}

void printGraph() {
    cout << "w\tu\tv\t" << endl;
    for (int i = 0; i < edgeList.size(); i++) {
        for (int j = 0; j < 3; j++) {
            cout << edgeList[i][j] << "\t";
        }
        cout << endl;
    }
    for (int i = 0; i < nodeList.size(); i++)
        cout << nodeList[i] << endl;
}

void printMST() {
    for (int i = 0; i < MSTedges.size(); i++)
        cout << MSTedges[i][0] << "\t" << MSTedges[i][1] << endl;
    for (int i = 0; i < MSTnodes.size(); i++)
        cout << MSTnodes[i] << "\t";
    cout << endl;
}

void printEuler() {
    for (auto it = Euler_adjlist.begin(); it != Euler_adjlist.end(); it++) {
        cout << it->first << " --> ";
        for (int i = 0; i < it->second.size(); i++)
            cout << it->second[i] << " ";
        cout << endl;
    }
}

/*
 * Function reads in the input data file,
 * and stores the node information into adj_list.
 */
int ReadIn(string inFile) {

    string line, delimiter;
    adj_list.clear();
    ifstream myfile(inFile);
    double edge[3];

    if (myfile.is_open()) {
        getline(myfile, line);
        getline(myfile, line);
        for (int i = 0; i < line.length(); i++) {
            if (!isdigit(line[i]) && line[i] != '.') {
                delimiter = line[i];
                break;
            }
        }
        myfile.clear();
        myfile.seekg(0);
        getline(myfile, line);
        totNodes = stoi(line);
        cout << "No. of Nodes: " << totNodes << endl;
        while (getline(myfile, line)) {
            for (int i = 0, pos = line.find(delimiter); i < 3; i++, pos = line.find(delimiter)) {
                edge[i] = stod(line.substr(0, pos));
                line = &line[pos + 1];
            }
            addEdge(edge[0], edge[1], edge[2]);
        }
        myfile.close();
    } else cout << "Unable to open input file";
    return 0;
}


void DepthFirstSearch(double node) {
    double neighbor;
    dfs_list.push_back(node);
    for (int i = 0; graph_adjlist.find(node) != graph_adjlist.end() && i < graph_adjlist[node].size() &&
                    dfs_list.size() != nodeList.size(); i++) {
        neighbor = graph_adjlist[node][i];
        if (find(dfs_list.begin(), dfs_list.end(), neighbor) != dfs_list.end()) {
            continue;
        }
        DepthFirstSearch(neighbor);
    }
}


bool isConnected() {
    double node = nodeList[0];
    DepthFirstSearch(node);
    if (dfs_list.size() == nodeList.size())
        return true;
    return false;
}

bool isComplete() {
    int count;
    for (int i = 0; i < nodeList.size(); i++) {
        count = 0;
        for (int j = 0; j < nodeList.size(); j++) {
            if (nodeList[i] != nodeList[j]) {
                for (int e = 0; e < edgeList.size(); e++) {
                    if ((edgeList[e][1] == nodeList[i] && edgeList[e][2] == nodeList[j]) ||
                        (edgeList[e][1] == nodeList[j] && edgeList[e][2] == nodeList[i])) {
                        count++;
                        break;
                    }
                }
            }
        }
        if (count != totNodes - 1)
            return false;
    }
    return true;
}

bool EulerTour(double node) {
    double neighbor;
    int i;
    eulerTour.push_back(node);
    cout << node;
    if (Euler_adjlist.empty())
        return true;
    else if (Euler_adjlist[node].empty())
        return false;
    while (!Euler_adjlist[node].empty() && Euler_adjlist.find(node) != Euler_adjlist.end()) {
        for (i = 0; i < Euler_adjlist[node].size(); i++) {
            neighbor = Euler_adjlist[node][i];
            if (find(eulerTour.begin(), eulerTour.end(), neighbor) != eulerTour.end() and
                Euler_adjlist[node].size() > 1) {
                continue;
            } else
                break;
        }
        Euler_adjlist[node].erase(Euler_adjlist[node].begin() + i);
        if (Euler_adjlist[node].empty())
            Euler_adjlist.erase(node);
        cout << " --> ";
        if (!EulerTour(neighbor))
            break;
    }
    return true;
}

void shortcutting() {
    for (int i = 0; i < eulerTour.size(); i++) {
        for (int j = i + 2; j < eulerTour.size() - 1; j++) {
            if (eulerTour[i] == eulerTour[j]) {
                eulerTour.erase(eulerTour.begin() + j);
                j--;
            }
        }
    }
    for (int i = 0; i < eulerTour.size(); i++) {
        cout << eulerTour[i];
        if (i != eulerTour.size() - 1)
            cout << " --> ";
    }
}


bool find_union(vector<vector<double>>& forest, vector<double> edge) {
    vector<double> res(nodeList.size());
    vector<vector<double>>::iterator node_u;
    vector<double>::iterator inter;
    if (edge[0] == edge[1])
        return false;
    sort(edge.begin(), edge.end());
    for (int i = 0, u_idx = -1; i < forest.size(); i++) {
        sort(forest[i].begin(), forest[i].end());
        inter = set_intersection(edge.begin(), edge.end(), forest[i].begin(), forest[i].end(), res.begin());

        switch (inter - res.begin()) {
            case 0:
                continue;
            case 1:
                if (u_idx == -1) {
                    u_idx = i;
                } else {
                    inter = set_union(forest[u_idx].begin(), forest[u_idx].end(), forest[i].begin(), forest[i].end(),
                                      res.begin());
                    forest.erase(forest.begin() + i);
                    forest.push_back({res.begin(), inter});
                    forest.erase(forest.begin() + u_idx);
                    return true;
                }

                break;
            case 2:
                return false;
            default:
                cout << "Error\n";
        }
    }
    return false;
}

void kruskalsMST() {
    int i = 0;
    bool found;
    vector<vector<double>> forest;
    for (i = 0; i < nodeList.size(); i++)
        forest.push_back({nodeList[i]});

    for (i = 0, found = false;
         i < edgeList.size() && forest.size() != 1 && forest[0].size() != nodeList.size(); i++, found = false) {
        found = find_union(forest, {edgeList[i][1], edgeList[i][2]});
        if (found) {

            MSTedges.push_back(vector<double>{edgeList[i][1], edgeList[i][2]});
            Euler_adjlist[edgeList[i][1]].push_back(edgeList[i][2]);
            Euler_adjlist[edgeList[i][2]].push_back(edgeList[i][1]);
        }
    }
}

double getWeight(double u, double v) {
    for (int i = 0; i < edgeList.size(); i++) {
        if ((edgeList[i][1] == u && edgeList[i][2] == v) || (edgeList[i][1] == v && edgeList[i][2] == u))
            return edgeList[i][0];
    }
    return 0;
}


int main(int argc, char *argv[]) {
    ReadIn("weighted_graph.txt");
    if (!isConnected()) {
        cout << "Input is not a connected graph." << endl;
        return -1;
    }
    if (!isComplete()) {
        cout << "Input graph is not complete." << endl;
        return -1;
    }
    sort(edgeList.begin(), edgeList.end());
    kruskalsMST();
    cout << "MST: ";
    printMST();
    cout << "Euler tour: ";
    for (int i = 0; i < MSTedges.size(); ++i) {
        if (EulerTour(MSTedges[i][1]))
            break;
    }
    cout << endl;
    cout << "TSP: ";
    shortcutting();
    cout << endl;
    double cost = 0;
    for (int i = 0; i < eulerTour.size() - 1; i++) {
        cost += getWeight(eulerTour[i], eulerTour[i + 1]);
    }
    cout << "Cost of TSP: " << cost << endl;
    return 0;
}