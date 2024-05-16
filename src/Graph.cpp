
#include <cmath>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility> // Include <utility> for using std::pair
#include <stack>   // Include <stack> for using std::stack
#include <queue>   // Include <queue> for using std::priority_queue
#include <set>
#include "Graph.h"
#include "Node.h"

using namespace std;

// Method to add a node to the graph
void Graph::addNode(Node *node) {
    if (findNode(node->getId()) == nullptr) {
        nodes.push_back(node);
    }
}

// Getter method to retrieve all nodes in the graph
const std::vector<Node *> Graph::getNodes() const {
    return nodes;
}

Node * Graph::findNode(const int &code) const {
    for (auto v : nodes) {
        if (v->getId() == code) {
            return v;
        }
    }
    return nullptr;
}

bool Graph::addBidirectionalEdge(int id, int id2, double dist) {
    auto source = findNode(id);
    auto dest = findNode(id2);
    if (source == nullptr || dest == nullptr)
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
    for (auto node : g.getNodes()) {
        Node *newnode = new Node(node->getId(), node->getLongitude(), node->getLatitude());
        addNode(newnode);
    }
    for (auto node : this->getNodes()) {
        int id1 = node->getId();
        Node *originalnode = g.findNode(id1);
        for (auto edge : originalnode->getAdj()) {
            Node *originaltarget = edge->getDest();
            int targetid = originaltarget->getId();
            Node *target = this->findNode(targetid);
            double distance = edge->getDistance();
            node->addEdge(target, distance);
        }
    }
}

double Graph::tspBT(std::vector<int> &path) {
    for (auto v : nodes) {
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
        if (edge != nullptr) {
            return currSum + edge->getDistance();
        }
        else {
            return bestSum;
        }
    }

    for (auto node : nodes) {
        Node *destVertex = node;

        if (destVertex->isVisited()) {
            continue;
        }

        Edge *e = currNode->findEdge(destVertex->getId());
        if (e == nullptr) continue;
        double dist = e->getDistance();

        if (currSum + dist < bestSum) {
            destVertex->setVisited(true);
            thisSum = tspBacktracking(path, destVertex->getId(), currSum + dist, bestSum, nodesVisited + 1);
            if (thisSum < bestSum) {
                bestSum = thisSum;
                path[nodesVisited] = destVertex->getId();
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


double Graph::tspTriangularApproximation(std::vector<int> &path) {
    if (nodes.empty())
        return 0.0;

    int numNodes = nodes.size();
    double totalDistance = 0.0;

    // Initialize visited set and MST
    unordered_map<int, bool> visited;
    vector<pair<int, double>> mstEdges;

    visited[0] = true;

    // Step 1: Prim's Algorithm to construct Minimum Spanning Tree (MST)
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    set<int> visitedNodes;

    // Start from node 0
    visitedNodes.insert(0);
    for (auto edge : findNode(0)->getAdj()) {
        pq.push({edge->getDistance(), edge->getDest()->getId()});
    }

    while (!pq.empty() && visitedNodes.size() < numNodes) {
        auto [distance, nodeId] = pq.top();
        pq.pop();
        if (visitedNodes.find(nodeId) == visitedNodes.end()) {
            visitedNodes.insert(nodeId);
            mstEdges.push_back({nodeId, distance});

            // Add adjacent unvisited nodes to the priority queue
            for (auto edge : findNode(nodeId)->getAdj()) {
                int destNodeId = edge->getDest()->getId();
                if (visitedNodes.find(destNodeId) == visitedNodes.end()) {
                    pq.push({edge->getDistance(), destNodeId});
                }
            }
        }
    }

    // Step 2: Depth-First Search (DFS) to traverse the MST and construct path
    stack<int> dfsStack;
    dfsStack.push(0); // Start from node 0

    while (!dfsStack.empty()) {
        int currentNode = dfsStack.top();
        dfsStack.pop();

        path.push_back(currentNode);

        visited[currentNode] = true;

        for (auto [neighborId, distance] : mstEdges) {
            if (!visited[neighborId]) {
                dfsStack.push(neighborId);
                totalDistance += distance;
                break;
            }
        }
    }

    // Ensure path starts and ends at node 0
    path.push_back(0);

    // Return to the starting node to complete the tour
    totalDistance += haversineDistance(findNode(path.back()), findNode(0));

    return totalDistance;
}

