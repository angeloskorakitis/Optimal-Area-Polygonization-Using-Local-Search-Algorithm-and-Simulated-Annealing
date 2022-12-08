/////////////////////////////////////////////////////////////////////////////////
//
//
// Local Search for Area-Optimal Polygonization
//
//
/////////////////////////////////////////////////////////////////////////////////

#include "Utilities.hpp"

bool compare_delta(double temp_delta,double delta, String optimization);

// Returns a polygon after the local search given the threshold and L, the maximum number of paths we are going to search.

Polygon local_search(Polygon polygon, double threshold, int L, String optimization);

// Performs the path changes to the polygon. If the polygon is simple after the changes it returns it, else it returns the initial polygon.

Polygon local_search_step(Polygon polygon, VertexCirculatorVector path, Segment segment);

// Returns the position of a point in a polygon.

int position_of_point_in_polygon(Polygon polygon, Point point);

// Returns the position of the source point of a segment in a polygon.

int position_of_segment_in_polygon(Polygon polygon, Segment segment);