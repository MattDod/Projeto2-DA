#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <set>
#include "System.h"

System::System(){
    graph.clear(); // Clear the graph before parsing a new one

}

void System::close() {
    graph.clear();
}


void System::parseGraph(const std::string &filename,  enum System::graph_type type, int limit) {
    ifstream file1(filename);
    string line;
    getline(file1, line);
    while((limit != 0) && getline(file1, line)){
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
        limit--;

    }
}


void System::parseGraphEdges(const std::string &filename, bool skip) {
    ifstream file2(filename);
    string line;
    if(skip) getline(file2, line);
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

void System::callChristofides() {
    vector<int> path(graph.getNodes().size() + 1);
    double shortestDistance = graph.tspChristofides(path);
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

void System::callNearestNeighbor(int node) {
    vector<int> path;
    double shortestDistance = graph.tspNearestNeighbor(node, path);

    if(path.empty() && shortestDistance == numeric_limits<double>::max()){
        cout << "No feasible path found" << endl;
        return;
    }
    else{
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
}