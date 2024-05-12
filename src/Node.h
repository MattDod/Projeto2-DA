//
// Created by kamert on 12-05-2024.
//

#ifndef PROJETODA2_NODE_H
#define PROJETODA2_NODE_H

#include <string>
#include <vector>
#include "Edge.h"
class Edge;
class Node {
public:

    Node(int id);
    Node(int id, double longitude, double latitude);

    std::string getName() const;

    int getId() const;



    Edge * addEdge(Node *dest, double distancia);
    bool isVisited() const;
    void setVisited(bool value);
    void setPath(Edge *path);
    std::vector<Edge *> getAdj() const;
    std::vector<Edge *> getIncoming() const;
    double getLatitude() const;
    double getLongitude() const;
    Edge * findEdge(double dest);

private:
    std::string name;
    double longitude;
    double latitude;
    int id;
    bool visited = false;
    Edge *path = nullptr;
    std::vector<Edge *> adj;
    std::vector<Edge *> incoming;
};
#endif //PROJETODA2_NODE_H
