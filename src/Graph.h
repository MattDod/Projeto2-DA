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
    Node *findNode(const int &id) const;
    bool addBidirectionalEdge(int id, int id2, double dist);
    void clear();
    void copyGraph(const Graph &g);
    double tspBT(std::vector<int> &path);
    double tspBacktracking(std::vector<int> &path, int currentNode, double curSum, double bestSum, int nodesVisited);

};
#endif //PROJETODA2_GRAPH_H
