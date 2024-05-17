//This class is based on the MutablePriorityQueue.h file given in classes (TP3).
#ifndef PROJETODA2_PRIORITYQUEUE_H
#define PROJETODA2_PRIORITYQUEUE_H

#include <vector>
#include "Node.h"
#include <iostream>

class PriorityQueue {
private:
    std::vector<Node *> pq;
    void heapifyUp(unsigned i);
    void heapifyDown(unsigned i);
    inline void set(unsigned i, Node *x);
public:
    PriorityQueue();
    void insert(Node *x);
    Node *extractMin();
    void decreaseKey(Node *x);
    bool empty();
};

//Index calculations
#define parent(i) ((i) / 2)
#define leftChild(i) ((i) * 2)

PriorityQueue::PriorityQueue() {
    pq.push_back(nullptr);
    // indices start at 1 to facilitate parent/child calculations
}

bool PriorityQueue::empty() {
    return pq.size() == 1;
}

Node *PriorityQueue::extractMin() {
    Node *min = pq[1];
    pq[1] = pq.back();
    pq.pop_back();
    if(pq.size() > 1) heapifyDown(1);
    min->pqIndex = 0;
    return min;
}

void PriorityQueue::insert(Node *x) {
    pq.push_back(x);
    heapifyUp(pq.size() - 1);
}

void PriorityQueue::decreaseKey(Node *x) {
    heapifyUp(x->pqIndex);
}

void PriorityQueue::heapifyUp(unsigned i) {
    Node *x = pq[i];
    while((i > 1) && (*x < *pq[parent(i)])) {
        set(i, pq[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

void PriorityQueue::heapifyDown(unsigned i) {
    Node *x = pq[i];
    while(true){
        unsigned k = leftChild(i);
        if(k >= pq.size()) break;
        if((k + 1 < pq.size()) && (*pq[k + 1] < *pq[k])) k++; //right  child of i
        if(!(*pq[k] < *x)) break;
        set(i, pq[k]);
        i = k;
    }
    set(i, x);
}

void PriorityQueue::set(unsigned int i, Node *x) {
    pq[i] = x;
    x->pqIndex = i;
}

#endif //PROJETODA2_PRIORITYQUEUE_H
