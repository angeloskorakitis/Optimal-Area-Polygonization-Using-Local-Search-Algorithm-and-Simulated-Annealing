/////////////////////////////////////////////////////////////////////////////////
//
//
// Simulated Annealing for Area-Optimal Polygonization
//
//
/////////////////////////////////////////////////////////////////////////////////

#include "Utilities.hpp"

bool comparePoints(Point a, Point b);

bool metropolis(double difference, double temperature);

double compute_energy(Polygon polygon, double ch_area, bool minimalization);

bool edges_in_box_intersect(Polygon* polygon, Point p1, Point p2, Point p3, Point p4, PointVector points);

bool step_is_valid(Polygon* polygon, Tree* tree, Point p1, Point p2, Point p3, Point p4);

bool global_step(Polygon* polygon, Point Q = Point(-1,-1), Segment ST = Segment(Point(-1,-1), Point(-2,-2)));

bool local_step(Polygon* polygon, Tree* tree, Point Q = Point(-1,-1));