/////////////////////////////////////////////////////////////////////////////////
//
//
// Polygonization Using Spatial Subdivision
//
//
/////////////////////////////////////////////////////////////////////////////////

#include "Utilities.hpp"


// Performs and checks validity of global step. 
// Returns true if the step is valid and the polygon is changed.
// Returns false if the step is invalid and the polygon stays the same.
bool spatial_global_step(Polygon* polygon);


// Spatial Annealing is similar to simulated annealing, but it also ensures the 
// left and right "pinned down" edges stay unchanged. 
Polygon spatial_annealing(Polygon polygon, PointVector points, bool goal);


// True if criteria is met.
// False if not.
bool check_rightmost(PointVector* spal);


// True if criteria is met.
// False if not.
bool check_leftmost(PointVector* spal);


// Fills spal with points till the critirea are met. 
int fill_spal(PointVector* spal, PointVector points, int starting_index, int m);


// All elements of v2 are appended at the end of v1.
// The common point at the beggining of v2 and at the end of v1 is not doubled. 
void append_spals(PointVector* v1, PointVector* v2);


// Merges polygons of two neighbouring spals.
void merge_polygons(Polygon* p1, Polygon* p2);

// Spatial Convex Hull is similar to convex hull algorithm for polygonization, but it also ensures the 
// left and right "pinned down" edges stay unchanged. 
Polygon spatial_convex_hull_algorithm(PointVector initial_points);

// Spatial Subdivision Algorithm
Polygon spatial_subdivision(PointVector points, bool goal);
