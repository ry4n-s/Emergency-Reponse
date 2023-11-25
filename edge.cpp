#include "edge.hpp"

Edge::Edge() : dest(0), distance(0.0), speed(0.0), adjustment(1.0) {}

Edge::Edge(int dest, double distance, double speed, double adjustment)
    : dest(dest), distance(distance), speed(speed), adjustment(adjustment) {}
