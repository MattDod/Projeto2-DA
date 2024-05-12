#include "Graph.h"
#include "Node.h"

// Method to add a node to the graph
void Graph::addNode(Node *node) {
    nodes.push_back(node);
}

// Getter method to retrieve all nodes in the graph
const std::vector<Node *> Graph::getNodes() const {
    return nodes;
}

Node * Graph::findNode(double &code) const{
    for (auto v : nodes){
        if(v->getId() == code){
            return v;
        }
    }
    return nullptr;
}

bool Graph::addBidirectionalEdge(double id, double id2, double dist)  {
    auto source = findNode(id);
    auto dest = findNode(id2);
    if(source == nullptr || dest == nullptr)
        return false;
    source->addEdge(dest, dist);
    dest->addEdge(source, dist);
    return true;
}


