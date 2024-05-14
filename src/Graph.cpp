#include <cfloat>
#include <iostream>
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
                path[nodesVisited - 1] = destVertex->getId();
            }
            destVertex->setVisited(false);
        }
    }

    return bestSum;
}





