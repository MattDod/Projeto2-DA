#include <cfloat>
#include <iostream>
#include <limits>
#include <cmath>
#include <unordered_set>
#include <vector>
#include "Graph.h"
#include "Node.h"

// Method to add a node to the graph
void Graph::addNode(Node *node) {
    if(findNode(node->getId()) == nullptr){
        nodes.push_back(node);
    }

}

// Getter method to retrieve all nodes in the graph
const std::vector<Node *> Graph::getNodes() const {
    return nodes;
}

Node * Graph::findNode(const int &code) const{
    for (auto v : nodes){
        if(v->getId() == code){
            return v;
        }
    }
    return nullptr;
}

bool Graph::addBidirectionalEdge(int id, int id2, double dist)  {
    auto source = findNode(id);
    auto dest = findNode(id2);
    if(source == nullptr || dest == nullptr)
        return false;
    source->addEdge(dest, dist);
    dest->addEdge(source, dist);
    return true;
}

void Graph::clear() {
    for (auto node : nodes) {
        delete node;
    }
    nodes.clear();
}



void Graph::copyGraph(const Graph &g) {
    for(auto node : g.getNodes()){
        Node * newnode;
        newnode = new Node(node->getId(), node->getLongitude(), node->getLatitude());
        addNode(newnode);
    }
    for(auto node : this->getNodes()){
        int id1 = node->getId();
        Node *originalnode = g.findNode(id1);
        for(auto edge : originalnode->getAdj()){
            Node *originaltarget = edge->getDest();
            int targetid = originaltarget->getId();
            Node *target = this->findNode(targetid);
            double distance = edge->getDistance();
            node->addEdge(target, distance);
        }
    }
}


double Graph::tspBT(std::vector<int> &path) {
    for (auto v: nodes) {
        v->setVisited(false);
    }

    findNode(0)->setVisited(true);
    path[0] = 0;

    double bestDist = tspBacktracking(path, 0, 0, 100000, 1);
    path.push_back(0);


    return bestDist;
}


double Graph::tspBacktracking(std::vector<int> &path, int currNodeId, double currSum, double bestSum, int nodesVisited) {

    double thisSum = 0;
    Node *currNode = findNode(currNodeId);

    if (nodesVisited == nodes.size()) {
        Edge *edge = currNode->findEdge(0);
        if(edge != nullptr){
            return currSum + edge->getDistance();
        }
        else{
            return bestSum;
        }

    }

    for (auto node: nodes) {
        Node *destVertex = node;

        if (destVertex->isVisited()){
            continue;
        }

        Edge *e = currNode->findEdge(destVertex->getId());
        if (e == nullptr) continue;
        double dist = e->getDistance();

        if (currSum + dist < bestSum) {



            destVertex->setVisited(true);
            thisSum = tspBacktracking(path, destVertex->getId(), currSum + dist, bestSum, nodesVisited+ 1);
            if (thisSum < bestSum) {
                bestSum = thisSum;
                path[nodesVisited ] = destVertex->getId();
            }
            destVertex->setVisited(false);
        }
    }

    return bestSum;
}


double Graph::haversineDistance(const Node *node1, const Node *node2) {
    const double R = 6371.0; // Earth radius in kilometers

    double lat1 = node1->getLatitude();
    double lon1 = node1->getLongitude();
    double lat2 = node2->getLatitude();
    double lon2 = node2->getLongitude();

    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
               sin(dLon / 2) * sin(dLon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R * c;

    return distance;
}


double Graph::ttspTriangularApproximation(Graph &graph, std::vector<int> &path) {
    int numNodes = graph.getNodes().size();
    std::vector<bool> visited(numNodes, false);
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;

    double totalDistance = 0.0;
    int startNode = 0;

    visited[startNode] = true;
    path.push_back(startNode);

    for (auto edge : graph.findNode(startNode)->getAdj()) {
        pq.push({edge->getDistance(), edge->getDest()->getId()});
    }

    while (!pq.empty()) {
        auto [distance, nodeId] = pq.top();
        pq.pop();

        if (!visited[nodeId]) {
            visited[nodeId] = true;
            path.push_back(nodeId);
            totalDistance += distance;

            for (auto edge : graph.findNode(nodeId)->getAdj()) {
                pq.push({edge->getDistance(), edge->getDest()->getId()});
            }
        }
    }

    // Return to the starting node to complete the tour
    totalDistance += graph.findNode(path.back())->findEdge(startNode)->getDistance();
    path.push_back(startNode);

    return totalDistance;
}


double Graph::tspTriangularApproximation(std::vector<int> &path) {
    int numNodes = nodes.size();
    std::vector<bool> visited(numNodes, false);
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;

    double totalDistance = 0.0;
    int startNode = 0;

    visited[startNode] = true;

    // Add adjacent nodes of the start node to the priority queue
    for (auto edge : findNode(startNode)->getAdj()) {
        pq.push({edge->getDistance(), edge->getDest()->getId()});
    }

    while (!pq.empty()) {
        auto [distance, nodeId] = pq.top();
        pq.pop();

        if (!visited[nodeId]) {
            visited[nodeId] = true;
            path.push_back(nodeId);
            totalDistance += distance;

            // Add adjacent unvisited nodes to the priority queue
            for (auto edge : findNode(nodeId)->getAdj()) {
                if (!visited[edge->getDest()->getId()]) {
                    pq.push({edge->getDistance(), edge->getDest()->getId()});
                }
            }
        }
    }

    // Return to the starting node to complete the tour
    totalDistance += haversineDistance(findNode(path.back()), findNode(startNode));
    path.push_back(startNode);

    return totalDistance;
}

