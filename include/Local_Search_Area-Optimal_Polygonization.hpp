/////////////////////////////////////////////////////////////////////////////////
//
//
// Local Search for Area-Optimal Polygonization
//
//
/////////////////////////////////////////////////////////////////////////////////

#include "Utilities.hpp"

// bool compare_polygon_changes(polygon_changes p_changes_a, polygon_changes p_changes_b);

// struct polygon_changes{
//     Segment edge;
//     VertexCirculatorVector path;
//     double delta;
// };

// typedef polygon_changes* PolygonChanges;

Polygon local_search(Polygon polygon, double threshold, int L);

Polygon local_search_step(Polygon polygon, VertexCirculatorVector path, Segment segment);

// Polygon apply_local_changes(Polygon polygon, std::vector<PolygonChanges> polygon_changes_vector);

int position_of_point_in_polygon(Polygon polygon, Point point);

int position_of_segment_in_polygon(Polygon polygon, Segment segment);