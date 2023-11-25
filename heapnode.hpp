#ifndef HEAPNODE_HPP
#define HEAPNODE_HPP

class HeapNode {
public:
    int vertex;
    double distance;

    HeapNode();
    HeapNode(int vertex, double distance);
};

#endif // HEAPNODE_HPP
