//
// Created by kamert on 12-05-2024.
//

#ifndef PROJETODA2_EDGE_H
#define PROJETODA2_EDGE_H

#include "Node.h"
class Node;
class Edge {
public:


    Edge(Node *source, Node *target, double distance);


    Node *getSourceNode() const;
    Node *getDest() const;
    double getDistance() const;


    void setCapacity(double capacity);
    void setFlow(double flow);

private:
    Node * source;
    Node * target;
    double distance;
};


#endif //PROJETODA2_EDGE_H
