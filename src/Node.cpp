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

Edge * Node::addEdge(Node *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

std::vector<Edge*> Node::getAdj() const {
    return this->adj;
}

