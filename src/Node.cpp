//
// Created by kamert on 12-05-2024.
//

#include "Node.h"

Node::Node(int id) {
    this->latitude = 0;
    this->longitude = 0;
    this->id = id;
}

Node::Node(int id, double longitude, double latitude) {
    this->id = id;
    this->name = "nome";
    this->latitude = latitude;
    this->longitude = longitude;
}

int Node::getId() const {
    return this->id;
}

double Node::getLongitude() const {
    return this->longitude;
}

std::string Node::getName() const {
    return this->name;
}

double Node::getLatitude() const {
    return this->latitude;
}

Edge* Node::getPath() const {
    return this->path;
}

double Node::getDistance() const {
    return this->distance;
}

Edge * Node::addEdge(Node *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

std::vector<Edge*> Node::getAdj() const {
    return this->adj;
}

void Node::setVisited(bool value) {
    this->visited = value;
}

void Node::setPath(Edge *value) {
    this->path = value;
}

void Node::setDistance(double value) {
    this->distance = value;
}

bool Node::isVisited() const {
    return this->visited;
}

Edge *Node::findEdge(int dest) {
    for (Edge *e: this->adj) {
        if (e->getDest()->getId() == dest)
            return e;
    }

    return nullptr;
}

