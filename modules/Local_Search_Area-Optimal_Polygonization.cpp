/////////////////////////////////////////////////////////////////////////////////
//
//
// Local Search for Area-Optimal Polygonization
//
//
/////////////////////////////////////////////////////////////////////////////////

#include "Local_Search_Area-Optimal_Polygonization.hpp"

// #define L = 1;

Polygon local_search(Polygon polygon)
{
    Polygon final_polygon = polygon;
    

    double delta = 1.0;
    double old_delta = 0.0;
    while(delta >= 0.0001)
    {
        // for every edge of the polygon...
        for (EdgeIterator edge_itr = polygon.edges_begin(); edge_itr != polygon.edges_end(); ++edge_itr) 
        {
            VertexCirculator start_vertex = polygon.vertices_circulator();
            
            // for path of length 1 till length L...
            for(int k = 1; k <= 5; k++)
            {
                // Container of the path.
                VertexCirculatorVector path;

                // Start edge of the polygon.
                // EdgeCirculator start_edge_circ = polygon.edges_circulator();
                    
                // EdgeCirculator edge_circ = start_edge_circ;
                VertexCirculator vertex_circ = start_vertex;


                // Create a k-path of vertices.
                for(int i=k; i<= k; i++)
                {
                    path.push_back(vertex_circ);
                    
                    // Go to the next edge.
                    vertex_circ++;
                }

                long int old_area = CGAL::abs(polygon.area());
                Polygon temp_polygon = local_search_step(polygon, path, *edge_itr);
                long int new_area = CGAL::abs(temp_polygon.area());
                delta = new_area - old_area;

                // XXXXXXX
                if(delta > old_delta){
                    final_polygon = temp_polygon;
                    old_delta = delta;
                }

                start_vertex++;
            }
        }
    }

    return final_polygon;
}



Polygon local_search_step(Polygon polygon, VertexCirculatorVector path, Segment segment)
{
    //μπλα μπλα μπλα
    Polygon temp_polygon = polygon;

    // int segment_point_target;
    // if(segment_point_source==temp_polygon.size()-1) segment_point_target = 0;
    // else segment_point_target = segment_point_source + 1;

    

    int segment_point_target;
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
        int segment_point_source = position_of_segment_in_polygon(temp_polygon, segment);
        if(segment_point_source==temp_polygon.size()-1) segment_point_target=0;
        else segment_point_target = segment_point_source +1;

        temp_polygon.insert(temp_polygon.begin() + segment_point_target, **p_vertex_circ);
        // segment_point_target++;

        temp_polygon.erase(temp_polygon.begin()+segment_point_source);
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