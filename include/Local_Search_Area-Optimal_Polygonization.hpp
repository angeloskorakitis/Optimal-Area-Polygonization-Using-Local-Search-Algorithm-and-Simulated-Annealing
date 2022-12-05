/////////////////////////////////////////////////////////////////////////////////
//
//
// Local Search for Area-Optimal Polygonization
//
//
/////////////////////////////////////////////////////////////////////////////////

#include "Utilities.hpp"


Polygon local_search(Polygon);

Polygon local_search_step(Polygon polygon, VertexCirculatorVector path, Segment segment);

int position_of_point_in_polygon(Polygon polygon, Point point);

int position_of_segment_in_polygon(Polygon polygon, Segment segment);