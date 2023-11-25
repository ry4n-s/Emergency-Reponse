#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include "heapnode.hpp"

class MinHeap {
private:
    HeapNode* heapArray;
    int capacity;
    int heapSize;

    void minHeapify(int idx);

public:
    MinHeap(int cap);
    ~MinHeap();
    void insertKey(int v, double dist);
    void decreaseKey(int v, double dist);
    int extractMin();
    bool isEmpty() const;
};

#endif // MINHEAP_HPP
