#include "Edge.h"

Edge::Edge(Node *source, Node *target, double distance): source(source), target(target), distance(distance) {}

double Edge::getDistance() const {
    return this->distance;
}

Node * Edge::getDest() const {
    return this->target;
}

Node * Edge::getSourceNode() const {
    return this->source;
}
