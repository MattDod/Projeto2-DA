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
    //double tspTriangularApproximation(Graph& graph, std::vector<int>& path);
    double haversineDistance(const Node* node1, const Node* node2);
    double ttspTriangularApproximation(Graph &graph, std::vector<int> &path) ;


    double tspTriangularApproximation(std::vector<int> &path);


    double ttspTriangularApproximation(std::vector<int> &path);

    double calculateTourDistance(const std::vector<int> &path);

    std::vector<Edge *> generateMinimumSpanningTree() const;

    void DFS(const Node *currNode, std::vector<bool> &visited, std::vector<int> &path);

    void DFS(const std::vector<Edge *> &minimumSpanningTree, const Node *currNode, std::vector<bool> &visited,
             std::vector<int> &path);
};
#endif //PROJETODA2_GRAPH_H
