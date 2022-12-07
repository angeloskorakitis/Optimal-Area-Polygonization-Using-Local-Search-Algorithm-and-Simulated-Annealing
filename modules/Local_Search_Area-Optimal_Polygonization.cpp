/////////////////////////////////////////////////////////////////////////////////
//
//
// Local Search for Area-Optimal Polygonization
//
//
/////////////////////////////////////////////////////////////////////////////////


#include "Local_Search_Area-Optimal_Polygonization.hpp"


Polygon local_search(Polygon polygon, double threshold, int L)
{
    Polygon new_polygon = polygon;

    Polygon convex_hull;
    CGAL::convex_hull_2(polygon.begin(), polygon.end(), std::back_inserter(convex_hull));
    long int convex_hull_area = CGAL::abs(convex_hull.area());
    long int old_area = CGAL::abs(polygon.area());

    // PolygonChangesVector polygon_changes_vector;

    double delta=threshold;
    while(delta >= threshold)
    {
        // for every edge of the polygon...
        for (EdgeIterator edge_itr = polygon.edges_begin(); edge_itr != polygon.edges_end(); ++edge_itr) 
        {
            delta = 0.0;
            for(int k = 1; k <= L; k++)
            {
                VertexCirculator start_vertex_circ = polygon.vertices_circulator();

                for(int j=0; j< polygon.size(); j++)
                {
                    // Container of the path.
                    VertexCirculatorVector path;

                    // Start edge of the polygon.
                    VertexCirculator vertex_circ = start_vertex_circ;

                    // Create a k-path of vertices.
                    for(int i=1; i<=k; i++)
                    {
                        path.push_back(vertex_circ++);
                        // Go to the next edge.
                    }

                    Polygon temp_polygon = local_search_step(polygon, path, *edge_itr);
                    long int new_area = CGAL::abs(temp_polygon.area());
                    double temp_delta = (double)(new_area - old_area)/convex_hull_area;

                    // Check delta
                    if(temp_delta > delta)
                    {
                        // PolygonChanges p_changes;
                        // p_changes->delta = temp_delta;
                        // p_changes->path = path;
                        // p_changes->segment = *edge_itr;
                        // polygon_changes_vector.push_back(p_changes);
                        new_polygon = temp_polygon;
                        delta = temp_delta;
                    }

                    start_vertex_circ++;
                }
            }
        }

        // Change the search polygon to the max/min area polygon and continue the search there...
        polygon = new_polygon;

    }

    return new_polygon;
}

// bool compare_polygon_changes(polygon_changes p_changes_a, polygon_changes p_changes_b){
//     if((p_changes_a.delta - p_changes_b.delta)>=0) return true;
//     return false; 
// }


// Polygon apply_local_changes(Polygon polygon, PolygonChangesVector polygon_changes_vector)
// {
//     Polygon final_polygon = polygon;

//     std::sort(polygon_changes_vector.begin(), polygon_changes_vector.end(), compare_polygon_changes);

//     for(pPolygonChangesVector p_changes_itr = polygon_changes_vector.begin(); p_changes_itr != polygon_changes_vector.end(); ++p_changes_itr)
//     {
//         final_polygon = local_search_step(final_polygon, p_changes_itr->path, p_changes_itr->segment);
//     }

//     return final_polygon;
// }

Polygon local_search_step(Polygon polygon, VertexCirculatorVector path, Segment segment)
{
    Polygon temp_polygon = polygon;
    
    int segment_point_target;
    int segment_point_source = position_of_segment_in_polygon(temp_polygon, segment);
    if(segment_point_source==temp_polygon.size()-1) segment_point_target=0;
    else segment_point_target = segment_point_source +1;
    int position;

    // Path delete nodes
    for(pVertexCirculatorVector p_vertex_circ = path.begin(); p_vertex_circ != path.end(); ++p_vertex_circ)
    {
        // pairnw to prwto shmeio kai to vazw prin apo to target toy segment moy
        //ta ypoloipa ta bazw prin apo to teleutaio shmeio poy evala
        // int edge_point_source = position_of_segment_in_polygon(temp_polygon, *edge);
        // pairnw to prwto shmeio kai to vazw prin apo to target toy segment moy
        //ta ypoloipa ta bazw prin apo to teleutaio shmeio poy evala
        // int edge_point_source = position_of_segment_in_polygon(temp_polygon, *edge)
        // Segment
        position = position_of_point_in_polygon(temp_polygon, **p_vertex_circ);
        temp_polygon.erase(temp_polygon.begin()+position);

        temp_polygon.insert(temp_polygon.begin() + segment_point_target, **p_vertex_circ);
        segment_point_target = position_of_point_in_polygon(temp_polygon, **p_vertex_circ);

    }

    if(temp_polygon.is_simple()) return temp_polygon;

    return polygon;
}


int position_of_point_in_polygon(Polygon polygon, Point point) 
{
    int position = 0;
    for(VertexIterator i = polygon.begin(); i != polygon.end(); i++) 
    {
        if(point == *i) break;
        position++;

    }
    return position;
}


int position_of_segment_in_polygon(Polygon polygon, Segment segment) 
{
    int position = 0;
    for(EdgeIterator i = polygon.edges_begin(); i != polygon.edges_end(); i++)
    {
        if((segment == *i) || (segment.opposite() == *i)) break;
        position++;
    }
    return position;
}