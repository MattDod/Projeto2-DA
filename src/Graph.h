//
// Created by kamert on 12-05-2024.
//

#ifndef PROJETODA2_GRAPH_H
#define PROJETODA2_GRAPH_H


#include <vector>
#include <queue>
#include <string>
#include "Node.h"

class Graph {
private:
public:

    void addNode(Node *node);

    bool addEdge(std::string &source, std::string &dest, double &latitude, double &longitude);
    std::vector<Node *> nodes;
    const std::vector<Node *> getNodes() const;

    void copyGraph(const Graph &g);

    Node *findNode(std::string &code) const;
};
#endif //PROJETODA2_GRAPH_H
