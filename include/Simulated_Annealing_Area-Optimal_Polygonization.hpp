/////////////////////////////////////////////////////////////////////////////////
//
//
// Simulated Annealing for Area-Optimal Polygonization
//
//
/////////////////////////////////////////////////////////////////////////////////


#include "Utilities.hpp"

#pragma one;
enum { MINIMALIZATION = true, MAXIMALIZATION = false };
enum { GLOBAL = false, LOCAL = true };


bool comparePoints(Point a, Point b);

// Returns true if Metropolis criterion holds, false otherwise.
bool metropolis(double difference, double temperature);

// Computates the energy of the given polygon based on the convex hull area
// and uses the correct formula depending on the state of "minimalization" flag (true/false).
double compute_energy(Polygon polygon, double ch_area, bool minimalization);

// Checks if the new edges created from the local step intersect
// with any edges of the polygon that they have a point int the box.
bool edges_in_box_intersect(Polygon* polygon, Point p1, Point p2, Point p3, Point p4, PointVector points);

// Checks if a local step is valid.
bool step_is_valid(Polygon* polygon, Tree* tree, Point p1, Point p2, Point p3, Point p4);


// Performs and checks validity of global step. 
// Returns true if the step is valid and the polygon is changed.
// Returns false if the step is invalid and the polygon stays the same.
bool global_step(Polygon* polygon, Point Q, Segment ST, Point);


// Performs and checks validity of global step. 
// Returns true if the step is valid and the polygon is changed.
// Returns false if the step is invalid and the polygon stays the same.
bool spatial_global_step(Polygon* polygon);


// Performs and checks validity of local step. 
// Returns true if the step is valid and the polygon is changed.
// Returns false if the step is invalid and the polygon stays the same.
bool local_step(Polygon* polygon, Tree* tree, Point Q);

bool check_rightmost(PointVector* spal);

bool check_leftmost(PointVector* spal);

// Fills spal with points till the critirea are met. 
int fill_spal(PointVector* spal, PointVector points, int starting_index, int m)

Polygon simulated_annealing(Polygon polygon, PointVector points, bool goal, bool step);

Polygon spatial_annealing(Polygon polygon, PointVector points, bool goal);