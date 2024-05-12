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


bool Graph::addPipe(std::string &source, std::string &dest, double &capacity, double &direction) {
    auto v1 = findNode(source);
    auto v2 = findNode(dest);
    if(v1 == nullptr || v2 == nullptr)
        return false;
    v1->addPipe(v2, capacity, direction);
    return true;
}

Node * Graph::findNode(std::string &code) const{
    for (auto v : nodes){
        if(v->getCode() == code){
            return v;
        }
    }
    return nullptr;
}

void Graph::copyGraph(const Graph &g) {
    for(auto n : g.getNodes()) {
        NodeType type = n->getType();
        Node *toAdd;
        switch (type) {
            case NodeType::City: {
                toAdd = new Node(n->getName(), n->getId(), n->getCode(), n->getDemand(), n->getPopulation(), NodeType::City);
                addNode(toAdd);
                break;
            }
            case NodeType::PumpingStation: {
                toAdd = new Node(n->getId(), n->getCode(), NodeType::PumpingStation);
                addNode(toAdd);
                break;
            }
            case NodeType::WaterReservoir: {
                toAdd = new Node(n->getName(), n->getMunicipality(), n->getId(), n->getCode(), n->getMaxDeliveryCapacity(), NodeType::WaterReservoir);
                addNode(toAdd);
                break;
            }
        }
    }
    for(auto n : this->getNodes()){
        std::string code = n->getCode();
        Node *originalNode = g.findNode(code);
        for(auto p : originalNode->getAdj()){
            Node* originalTarget = p->getTarget();
            std::string targetCode = originalTarget->getCode();
            Node* target = this->findNode(targetCode);
            double capacity = p->getCapacity();
            double direction = p->getDirection();
            n->addPipe(target, capacity, direction);
        }
    }
}
