
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
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

double Graph::tspChristofides(std::vector<int> &path) {
    int numNodes = nodes.size();
    double totalDistance = 0.0;

    /* Compute MST using Prim's algorithm*/

    //Vector to store the edges of mst (Format -> source, destination)
    vector<pair<int, int>> mstEdges;
    PriorityQueue pq;

    //Clear/Reset values and add nodes to pq
    for(auto node : nodes) {
        node->setVisited(false);
        node->setPath(nullptr);
        node->setDistance(std::numeric_limits<double>::max());
        pq.insert(node);
    }

    //Make the first node of the pq the one with id 0
    this->findNode(0)->setDistance(0.0);
    pq.decreaseKey(this->findNode(0));

    //Set to keep track of visited nodes
    set<int> visitedNodes;

    while (!pq.empty() && visitedNodes.size() < numNodes) {
        Node* node = pq.extractMin();
        node->setVisited(true);
        visitedNodes.insert(node->getId());

        if (node->getPath() != nullptr) {
            mstEdges.push_back({node->getPath()->getSourceNode()->getId(), node->getId()});
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

    /* Find the vertexes with an odd degree in the mst*/

    unordered_map<int,int> vertexCount;

    for(auto pair : mstEdges){
        vertexCount[pair.first]++;
        vertexCount[pair.second]++;
    }

    vector<int> oddDegreeNodes;
    for(auto values : vertexCount){
        if(values.second % 2 != 0){
            oddDegreeNodes.push_back(values.first);
        }
    }

    /* Compute a minimum weight perfect matching for the odd-degree nodes*/

    vector<pair<int,int>> perfectMatching;
    while(!oddDegreeNodes.empty()){
        int u = oddDegreeNodes.back();
        oddDegreeNodes.pop_back();
        double minWeight = std::numeric_limits<double>::max();
        int minIndex = -1;

        for (int i = 0; i < oddDegreeNodes.size(); ++i) {
            Node* uNode = findNode(u);
            Node* vNode = findNode(oddDegreeNodes[i]);
            Edge* edge = uNode->findEdge(vNode->getId());
            if (edge && edge->getDistance() < minWeight) {
                minWeight = edge->getDistance();
                minIndex = i;
            }
        }

        int v = oddDegreeNodes[minIndex];
        perfectMatching.push_back({u, v});
        oddDegreeNodes.erase(oddDegreeNodes.begin() + minIndex);
    }

    /* Combine the edges of the MST and the perfect matching to form an Eulerian graph*/
    //Format: node -> connected nodes
    /*For each key (node) in the unordered_map, there are stored the nodes it's connected to (vector)*/
    unordered_map<int, vector<int>> eulerianGraph;
    for (auto [u, v] : mstEdges) {
        eulerianGraph[u].push_back(v);
        eulerianGraph[v].push_back(u);
    }
    for (auto [u, v] : perfectMatching) {
        eulerianGraph[u].push_back(v);
        eulerianGraph[v].push_back(u);
    }

    /* Find an Eulerian tour*/

    stack<int> stack;
    unordered_set<int> visitedEulerian;
    vector<int> eulerianTour;

    stack.push(0); // Start from node 0

    while (!stack.empty()) {
        int currentNode = stack.top();
        stack.pop();
        //If the node is not yet visited, add it to the tour
        if (visitedEulerian.find(currentNode) == visitedEulerian.end()) {
            eulerianTour.push_back(currentNode);
            visitedEulerian.insert(currentNode);

            for (int neighbor : eulerianGraph[currentNode]) {
                //If the neighbor is not yet visited, add it to the stack
                if (visitedEulerian.find(neighbor) == visitedEulerian.end()) {
                    stack.push(neighbor);
                }
            }
        }
    }

    /* Convert Eulerian tour to Hamiltonian circuit */
    //To do this, we remove repeated nodes whilst keeping the order
    unordered_set<int> visitedHamiltonian;
    for (int node : eulerianTour) {
        if (visitedHamiltonian.find(node) == visitedHamiltonian.end()) {
            path.push_back(node);
            visitedHamiltonian.insert(node);
        }
    }
    path.push_back(0); // Ensure path ends at node 0

    // Calculate the total distance
    for (size_t i = 1; i < path.size(); ++i) {
        Node* node = findNode(path[i - 1]);
        Node* nextNode = findNode(path[i]);
        Edge* edge = node->findEdge(nextNode->getId());
        if (edge != nullptr) {
            totalDistance += edge->getDistance();
        }
    }

    return totalDistance;
}

double Graph::tspNearestNeighbor(int start, std::vector<int> &path) {
    Node *currentNode = findNode(start);
    double totalDistance = 0.0;
    for(auto node : nodes) {
        node->setVisited(false);
    }
    //Add initial node to the path
    path.push_back(start);
    currentNode->setVisited(true);

    while(path.size() < nodes.size()) {
        Edge *shortestEdge = nullptr;
        double shortestDistance = numeric_limits<double>::max();

        //Find the shortest edge
        for (Edge *edge: currentNode->getAdj()) {
            //If destination is not yet visited and the distance is shorter than the current shortest distance store it
            if (!edge->getDest()->isVisited() && edge->getDistance() < shortestDistance) {
                shortestEdge = edge;
                shortestDistance = edge->getDistance();
            }
        }
        //If there is a shortest edge, move to its destination
        if (shortestEdge) {
            currentNode = shortestEdge->getDest();
            currentNode->setVisited(true);
            path.push_back(currentNode->getId());
            totalDistance += shortestEdge->getDistance();
        } else {
            //Shortest edge doesn't exist, so we exit the loop
            break;
        }
    }

        //Now we check if all nodes have been visited
        if (path.size() == nodes.size()){
            //Check if we can go back to the starting node
            Edge *returnEdge = currentNode->findEdge(start);
            if (returnEdge == nullptr){
                path.clear();
                totalDistance = std::numeric_limits<double>::max();
            }
            else{
                totalDistance += returnEdge->getDistance();
                path.push_back(start);
            }
        }
        //Else, not all nodes were visited, so a tour wasn't found
        else{
            totalDistance = std::numeric_limits<double>::max();
            path.clear();
        }


    return totalDistance;
}