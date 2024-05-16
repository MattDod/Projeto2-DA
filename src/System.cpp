#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <set>
#include "System.h"

System::System(){
    graph.clear(); // Clear the graph before parsing a new one
    //parseGraph("../data/medium_graphs/nodes.csv",  medium);
    //parseGraphEdges("../data/medium_graphs/edges_25.csv");
    parseGraph("../data/toy_graphs/tourism.csv",  toy);


    for(auto v : graph.getNodes()){
        cout << "Node ID: " << v->getId() << '\n';
        cout << "Adjacent Nodes:\n";
        set<int> printedNodes; // to keep track of printed nodes
        for(auto e : v->getAdj()){
            // check if the adjacent node has been printed already
            if (printedNodes.find(e->getDest()->getId()) == printedNodes.end()) {
                cout << "  " << e->getDest()->getId() << " (Distance: " << e->getDistance() << ")\n";
                printedNodes.insert(e->getDest()->getId());
            }
        }
        cout << '\n';
    }





}


void System::parseGraph(const std::string &filename,  enum System::graph_type type) {
    ifstream file1(filename);
    string line;
    getline(file1, line);
    while(getline(file1, line)){
        istringstream iss(line);
        string id1, lat, lon, dist, id2;

        if(type == toy){
            getline(iss, id1, ',');
            getline(iss, id2, ',');
            getline(iss, dist, ',');
            if (dist.back() == '\r') dist = dist.substr(0, dist.size() - 1);

            auto node1 = graph.findNode(stoi(id1)) == nullptr ? new Node( stoi(id1)) : graph.findNode(stoi(id1));
            auto node2 = graph.findNode(stoi(id2)) == nullptr ? new Node( stoi(id2)) : graph.findNode(stoi(id2));

            graph.addNode(node1);
            graph.addNode(node2);
            graph.addBidirectionalEdge(stoi(id1), stoi(id2), stod(dist));
        }
        else if(type == medium || type == real){
            getline(iss, id1, ',');
            getline(iss, lon, ',');
            getline(iss, lat, '\r');

            auto v1 = new Node(stoi(id1), stod(lon), stod(lat));
            graph.addNode(v1);

        }

    }
}


void System::parseGraphEdges(const std::string &filename) {
    ifstream file2(filename);
    string line;
    while(getline(file2, line)){
        istringstream iss(line);
        string id1, id2, dist;

        getline(iss, id1, ',');
        getline(iss, id2, ',');
        getline(iss, dist, '\r');

        auto node1 = graph.findNode(stoi(id1));
        auto node2 = graph.findNode(stoi(id2));

        graph.addNode(node1);
        graph.addNode(node2);
        graph.addBidirectionalEdge(stoi(id1), stoi(id2), stod(dist));
    }
}


void System::callBacktracking() {
    vector<int> path(graph.getNodes().size() + 1);
    double shortestDistance = graph.tspBT(path);
    cout << "Shortest Path:\n";
    cout << path[0];
    for (int i = 1; i < path.size()  ; ++i) {
        if(path[i] != path[i+1] )cout << "--->" << path[i] ;
    }
    cout << endl << "Shortest Distance: " << shortestDistance << endl;
}

void System::callTriangularApproximation() {
    vector<int> path(graph.getNodes().size() + 1);
    double shortestDistance = graph.tspTriangularApproximation(path);


    cout << "Shortest Path:\n";
    for (int i = 0; i < path.size() - 1; ++i) {
        if (path[i] != path[i + 1]) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << "--->";
            }
        }
    }
    cout << path.front() << endl << "Shortest Distance: " << shortestDistance << endl;
}
