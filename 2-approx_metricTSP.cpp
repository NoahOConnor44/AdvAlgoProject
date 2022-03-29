#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<vector<unsigned long>> adj_list;
vector<vector<double>> edgeList;
vector<vector<double>> MSTedges;
vector<double> MSTnodes, nodeList;
map<double, vector<double>> Euler_adjlist;
vector<double> eulerTour;

void addEdge(double u, double v, double w) {
    edgeList.push_back({w, u, v});
    if(find(nodeList.begin(), nodeList.end(), u) == nodeList.end())
        nodeList.push_back(u);
    if(find(nodeList.begin(), nodeList.end(), v) == nodeList.end())
        nodeList.push_back(v);
}

void printGraph() {
    cout << "w\tu\tv\t" << endl;
    for (int i = 0; i < edgeList.size(); i++) {
        for (int j = 0; j < 3; j++) {
            cout << edgeList[i][j] << "\t";
        }
        cout << endl;
    }
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
        for (int i = 0; i < line.length(); i++) {
            if (!isdigit(line[i]) && line[i] != '.') {
                delimiter = line[i];
                break;
            }
        }
        myfile.clear();
        myfile.seekg(0);
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

void EulerTour(double node, double parent) {
    eulerTour.push_back(node);
    cout << node;
    if (Euler_adjlist[node].empty() || Euler_adjlist.empty())
        return;
//    if(node != parent) {
    while (!Euler_adjlist[node].empty() && Euler_adjlist.find(node) != Euler_adjlist.end()) {
        double neighbor = Euler_adjlist[node][0];
        if (neighbor == parent and Euler_adjlist[node].size() > 1) {
            neighbor = Euler_adjlist[node][1];
            Euler_adjlist[node].erase(Euler_adjlist[node].begin() + 1);
        } else
            Euler_adjlist[node].erase(Euler_adjlist[node].begin());
        if (Euler_adjlist[node].empty())
            Euler_adjlist.erase(node);
        cout << " --> ";
        EulerTour(neighbor, node);
    }
//    }
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

void kruskalsMST() {
    int i;
    bool found;
    for (i = 0, found = false; i < edgeList.size() && nodeList.size()!=MSTnodes.size(); i++) {
        if(MSTnodes.empty())
        {
            MSTnodes.push_back(edgeList[i][1]);
            MSTnodes.push_back(edgeList[i][2]);
        }
        else {
            if (find(MSTnodes.begin(), MSTnodes.end(), edgeList[i][1]) != MSTnodes.end()) {
//                cout << "edgeList[i][1] " << edgeList[i][1];
                found = true;
            }
            if (find(MSTnodes.begin(), MSTnodes.end(), edgeList[i][2]) != MSTnodes.end()) {
//                cout << " edgeList[i][2] " << edgeList[i][2];
                if (found) {
//                    cout << " cycle " << endl;
                    continue;
                } else {
//                    cout << " push " << edgeList[i][1];
                    MSTnodes.push_back(edgeList[i][1]);
                }
            } else {
//                cout << " push " << edgeList[i][2];
                MSTnodes.push_back(edgeList[i][2]);
            }
        }
        MSTedges.push_back(vector<double>{edgeList[i][1], edgeList[i][2]});
        Euler_adjlist[edgeList[i][1]].push_back(edgeList[i][2]);
        Euler_adjlist[edgeList[i][2]].push_back(edgeList[i][1]);
    }
}

int main() {
    ReadIn("D:\\FSU\\COURSES\\Adv Algo\\PROJECT\\DATA\\n6.txt");
//    printGraph();
    sort(edgeList.begin(), edgeList.end());
    kruskalsMST();
    printMST();
    printEuler();
    EulerTour(4, 4);
    cout << endl;
    shortcutting();
    cout << endl;
    std::cout << nodeList.size() << std::endl;
    return 0;
}
