/////////////////////////////////////////////////////////////////////////////////
//
//
// Area-Optimal_Polygonization_Using_Local_Search
//
//
/////////////////////////////////////////////////////////////////////////////////


#include "Area-Optimal_Polygonization_Using_Local_Search.hpp"


bool compare_delta(double temp_delta, double delta, String optimization)
{
    if(optimization == "max")
    {
        // If temp_delta is larger than delta...
        if(temp_delta > delta) return true;
        return false;
    }

    // If optimization is min
    if(temp_delta < delta) return true;
    return false;
}

Polygon local_search(Polygon polygon, double threshold, int L, String optimization)
{
    Polygon new_polygon = polygon;

    // Calculate the area of the convex hull to use in delta.
    Polygon convex_hull;
    CGAL::convex_hull_2(polygon.begin(), polygon.end(), std::back_inserter(convex_hull));
    long int convex_hull_area = CGAL::abs(convex_hull.area());

    // The area of the initial polygon.
    long int area = CGAL::abs(polygon.area());

    int counter_edge_check = 1;

    // For set of points bigger that 500 we check at random 20 edges to perform the algorithm.
    // See more in the documentation.
    static int max_edge_check = 10;
    static int threshold_polygon_size = 500;

    double delta=threshold;
    
    // The local search algorithm...
    while(std::abs(delta) >= threshold)
    {

        delta = 0.0;

        // for every edge of the polygon...
        for (EdgeIterator edge_itr = polygon.edges_begin(); edge_itr < polygon.edges_end(); ++edge_itr) 
        {

            // Checks the polygon size and threshold. More are explaned in the documentation.
            if(polygon.size() >= threshold_polygon_size)
            {
                edge_itr = polygon.edges_begin() + rand()%polygon.size();

                counter_edge_check++;
            }


            // Checks path of size 1, i.e segments till L, i.e L segments
            for(int k = 1; k <= L; k++)
            {

                VertexCirculator start_vertex_circ = polygon.vertices_circulator();

                // Iterate through the polygon to perform the local search step
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
                    }

                    // Perform the local search step and calculate the 
                    Polygon temp_polygon = local_search_step(polygon, path, *edge_itr);
                    long int temp_area = CGAL::abs(temp_polygon.area());
                    double temp_delta = (double)(temp_area - area)/convex_hull_area;

                    // Check delta. If temp delta is bigger then keep the temp_polygon.
                    if(compare_delta(temp_delta,delta,optimization))
                    {
                        new_polygon = temp_polygon;
                        delta = temp_delta;
                    }

                    // Start the next path from the next polygon segment...
                    start_vertex_circ++;
                }
            }

            if(counter_edge_check == max_edge_check) edge_itr = polygon.edges_end();

        }

        // Change the search polygon to the max/min area polygon and continue the search there...
        polygon = new_polygon;
        area = CGAL::abs(polygon.area());

    }

    return new_polygon;
}

Polygon local_search_step(Polygon polygon, VertexCirculatorVector path, Segment segment)
{
    Polygon temp_polygon = polygon;
    
    // Configure where the point will be added.
    int segment_point_target;
    int segment_point_source = position_of_segment_in_polygon(temp_polygon, segment);
    if(segment_point_source==temp_polygon.size()-1) segment_point_target=0;
    else segment_point_target = segment_point_source +1;
    
    
    int position;

    // We erase one point and we add one. The first point will be added before the target point of the segment. 
    //The next point will be added before the point that we added etc.
    for(pVertexCirculatorVector p_vertex_circ = path.begin(); p_vertex_circ != path.end(); ++p_vertex_circ)
    {
        position = position_of_point_in_polygon(temp_polygon, **p_vertex_circ);
        temp_polygon.erase(temp_polygon.begin() + position);

        temp_polygon.insert(temp_polygon.begin() + segment_point_target, **p_vertex_circ);
        segment_point_target = position_of_point_in_polygon(temp_polygon, **p_vertex_circ);
    }

    // If the polygon after the changes is simple, return it.
    if(temp_polygon.is_simple()) return temp_polygon;
    
    // Else return the initial polygon.
    return polygon;
}