#include "heapnode.hpp"

HeapNode::HeapNode() : vertex(-1), distance(0.0) {}

HeapNode::HeapNode(int v, double d) : vertex(v), distance(d) {}
