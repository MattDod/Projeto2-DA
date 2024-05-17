
#include <cmath>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility> // Include <utility> for using std::pair
#include <stack>   // Include <stack> for using std::stack
#include <queue>   // Include <queue> for using std::priority_queue
#include <set>
#include <iostream>
#include "Graph.h"
#include "Node.h"
#include "PriorityQueue.h"
#include <iostream>

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
    vector<pair<int, double>> mstEdges;
    PriorityQueue pq;

    for(auto node : nodes) {
        node->setVisited(false);
        node->setPath(nullptr);
        node->setDistance(std::numeric_limits<double>::max());
        pq.insert(node);
    }

    this->findNode(0)->setDistance(0.0);
    pq.decreaseKey(this->findNode(0));

    set<int> visitedNodes;

    while (!pq.empty() && visitedNodes.size() < numNodes) {
        Node* node = pq.extractMin();
        node->setVisited(true);
        visitedNodes.insert(node->getId());

        if (node->getPath() != nullptr) {
            mstEdges.push_back({node->getId(), node->getDistance()});
        }

        for (auto edge : node->getAdj()) {
            Node* dest = edge->getDest();
            if (!dest->isVisited() && edge->getDistance() < dest->getDistance()) {
                dest->setDistance(edge->getDistance());
                dest->setPath(edge);
                pq.decreaseKey(dest);
            }
        }
    }

    for(auto node : nodes) {
        node->setVisited(false);
    }


    // Step 2: Depth-First Search (DFS) to traverse the MST and construct path
    stack<int> dfsStack;
    dfsStack.push(0); // Start from node 0

    while (!dfsStack.empty()) {
        int currentNode = dfsStack.top();
        dfsStack.pop();

        path.push_back(currentNode);

        findNode(currentNode)->setVisited(true);

        for (auto [neighborId, distance] : mstEdges) {
            if (!findNode(neighborId)->isVisited()) {
                dfsStack.push(neighborId);
                totalDistance += distance;
                break;
            }
        }
    }

    // Ensure path starts and ends at node 0
    path.push_back(0);

    //totalDistance += haversineDistance(findNode(path.back()), findNode(0));
    // Return to the starting node to complete the tour

    int lastNodeInPath = path[path.size() - 2];
    Node* lastNode = findNode(lastNodeInPath);
    Edge* edgeToStart = lastNode->findEdge(0);
    double lastDistance = 0.0;
    if (edgeToStart != nullptr) {
        lastDistance = edgeToStart->getDistance();
    }
    totalDistance += lastDistance;

    return totalDistance;
}