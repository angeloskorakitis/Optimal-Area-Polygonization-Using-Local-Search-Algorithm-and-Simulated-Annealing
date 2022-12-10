/////////////////////////////////////////////////////////////////////////////////
//
//
// Polygonization Using Simulated Annealing
//
//
/////////////////////////////////////////////////////////////////////////////////

#include "Utilities.hpp"


// Checks if the new edges created from the local step intersect
// with any edges of the polygon that they have a point in the kd-tree rectangular.
bool edges_in_box_intersect(Polygon* polygon, Point p1, Point p2, Point p3, Point p4, PointVector points);


// Checks if a local step is valid.
bool step_is_valid(Polygon* polygon, Tree* tree, Point p1, Point p2, Point p3, Point p4);


// Performs and checks validity of global step. 
// Returns true if the step is valid and the polygon is changed.
// Returns false if the step is invalid and the polygon stays the same.
bool global_step(Polygon* polygon);


// Performs and checks validity of local step. 
// Returns true if the step is valid and the polygon is changed.
// Returns false if the step is invalid and the polygon stays the same.
bool local_step(Polygon* polygon, Tree* tree);



// Simulated Annealing Algorithm.
Polygon simulated_annealing(Polygon polygon, PointVector points, bool goal, bool step);


