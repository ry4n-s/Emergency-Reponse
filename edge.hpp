#ifndef EDGE_HPP
#define EDGE_HPP

class Edge {
public:
    int dest; //destination vertex
    double distance; //distance
    double speed; //speed limit
    double adjustment; //adjustment factor

    Edge(); //default constructor
    Edge(int dest, double distance, double speed, double adjustment = 1.0); //parameterized constructor
};

#endif // EDGE_HPP
