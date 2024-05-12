#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <set>
#include "System.h"

System::System(){
    graph.clear(); // Clear the graph before parsing a new one
    parseGraph("../data/toy_graphs/shipping.csv",  toy);
}

void System::parseGraph(const std::string &filename,  enum System::graph_type type) {
    ifstream file(filename);
    string line;
    if(type != medium) getline(file, line);
    while(getline(file, line)){
        istringstream iss(line);
        string id1, lat, lon, dist, id2;

        if(type == toy){
            getline(iss, id1, ',');
            getline(iss, id2, ',');
            getline(iss, dist, ',');
            if (dist.back() == '\r') dist = dist.substr(0, dist.size() - 1);

            auto v1 = graph.findNode(stoi(id1)) == nullptr ? new Node( stoi(id1)) : graph.findNode(stoi(id1));
            auto v2 = graph.findNode(stoi(id2)) == nullptr ? new Node( stoi(id2)) : graph.findNode(stoi(id2));

            graph.addNode(v1);
            graph.addNode(v2);
            graph.addBidirectionalEdge(stoi(id1), stoi(id2), stod(dist));
        }

    }
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
