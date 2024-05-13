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



