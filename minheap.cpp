#include "minheap.hpp"

//constructor: Initializes a MinHeap with given capacity
MinHeap::MinHeap(int cap) : capacity(cap), heapSize(0) {
    heapArray = new HeapNode[capacity];
}

//destructor: Cleans up the heap array
MinHeap::~MinHeap() {
    delete[] heapArray;
}

//inserts a new key (vertex and its distance) into the heap
void MinHeap::insertKey(int v, double dist) {
    //ignore if heap is already full
    if (heapSize == capacity) {
        return;
    }
    //insert new element at the end
    heapSize++;
    int i = heapSize - 1;
    heapArray[i] = HeapNode(v, dist);

    //maintain heap property
    while (i != 0 && heapArray[(i - 1) / 2].distance > heapArray[i].distance) {
        HeapNode temp = heapArray[i];
        heapArray[i] = heapArray[(i - 1) / 2];
        heapArray[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

//decreases the distance of a vertex in the heap
void MinHeap::decreaseKey(int v, double dist) {
    //find the vertex in the heap
    int i = 0;
    for (; i < heapSize; ++i) {
        if (heapArray[i].vertex == v) {
            break;
        }
    }
    //return if vertex is not found
    if (i == heapSize) {
        return;
    }

    //update the distance and percolate up
    heapArray[i].distance = dist;
    while (i != 0 && heapArray[(i - 1) / 2].distance > heapArray[i].distance) {
        HeapNode temp = heapArray[i];
        heapArray[i] = heapArray[(i - 1) / 2];
        heapArray[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

//extracts and returns the minimum element (vertex) from the heap
int MinHeap::extractMin() {
    //return -1 if heap is empty
    if (isEmpty()) {
        return -1;
    }
    
    //store the root vertex, replace it with the last element, and reduce heap size
    int rootVertex = heapArray[0].vertex;
    heapArray[0] = heapArray[heapSize - 1];
    heapSize--;

    //restore heap property starting from the root
    minHeapify(0);

    return rootVertex;
}

//restores the MinHeap property starting from the given index
void MinHeap::minHeapify(int idx) {
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    int smallest = idx;

    //find the smallest among the node, its left, and right children
    if (left < heapSize && heapArray[left].distance < heapArray[idx].distance) {
        smallest = left;
    }
    if (right < heapSize && heapArray[right].distance < heapArray[smallest].distance) {
        smallest = right;
    }

    //swap and continue heapifying if the node is not the smallest
    if (smallest != idx) {
        HeapNode temp = heapArray[idx];
        heapArray[idx] = heapArray[smallest];
        heapArray[smallest] = temp;
        minHeapify(smallest);
    }
}

//checks if the heap is empty
bool MinHeap::isEmpty() const {
    return heapSize == 0;
}
