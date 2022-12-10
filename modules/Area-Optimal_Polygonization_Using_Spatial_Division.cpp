/////////////////////////////////////////////////////////////////////////////////
//
//
// Implementation of Polygonization Using Spatial Subdivision
//
//
/////////////////////////////////////////////////////////////////////////////////


#include "Area-Optimal_Polygonization_Using_Spatial_Division.hpp"
#include "Polygonization_Using_Convex_Hull_Algorithm.hpp"

enum { MINIMALIZATION = true, MAXIMALIZATION = false };

/////////////////// CREATE SPALS ///////////////////


// True if criteria is met.
// False if not.
bool check_rightmost(PointVector* spal) {
  
  Point rightmost_point = spal->at(spal->size() - 1);
  int rightmost_y = rightmost_point.y();

  for(int i = 1; i < spal->size() - 1; i++) {
    Point test = spal->at(i);
    if(test.y() < rightmost_y) return true;
  }

  return false;
}




// True if criteria is met.
// False if not.
bool check_leftmost(PointVector* spal) {
  
  Point leftmost_point = spal->at(0);
  int leftmost_y = leftmost_point.y();

  for(int i = 1; i < spal->size() - 1; i++) {
    Point test = spal->at(i);
    if(test.y() < leftmost_y) return true;
  }

  return false;
}




// Fills spal with points till the critirea are met. 
int fill_spal(PointVector* spal, PointVector points, int starting_index, int m) {
  bool last_spal = false;
  int i;
  // Starts with m points.
  for(i = starting_index; i < starting_index + m; i++) {
    if(i == points.size()) {
      last_spal = true;
      break;
    }

    spal->push_back(points[i]);
  }

  // If few points are left, include them too.
  if((points.size() - i) <= (m/2)) {
    last_spal = true;
    while(i < points.size()) {
      spal->push_back(points[i++]);
    }
  }

  // Flags to check 
  bool rightmost = false;
  bool leftmost = false;

  // This is the last spal, no need to check anything.
  if(last_spal) { 
    return i;
  }

  if(starting_index == 0) leftmost = true;

  rightmost = check_rightmost(spal);
  if(starting_index != 0) // If this is not the first spal, we need to check both right and left edges.
    leftmost = check_leftmost(spal);

  // Add points, until both right and left edge criteria are met.
  while((!rightmost) || (!leftmost)) {

    spal->push_back(points[i++]);
    
    if(starting_index != 0) 
      leftmost = check_leftmost(spal);

    rightmost = check_rightmost(spal);

    // Have we reached the end of the pointset?
    if(i == points.size()) break;
  }

  // Return the index of the next of the last point we included.
  return i;
}




// All elements of v2 are appended at the end of v1.
// The common point at the beggining of v2 and at the end of v1 is not doubled. 
void append_spals(PointVector* v1, PointVector* v2) {
  for(int i = 1; i < v2->size(); i++) {
    v1->push_back(v2->at(i));
  }
}




// Merges polygons of two neighbouring spals.
void merge_polygons(Polygon* p1, Polygon* p2) {
  Polygon::Vertex_const_iterator itr = p1->right_vertex();

  p1->insert(p1->right_vertex(), p2->begin() + 1, p2->end());
}













//////////////////// SPATIAL SUBDIVISION ALGORITHM ////////////////////



// Spatial Annealing is similar to simulated annealing, but it also ensures the 
// left and right "pinned down" edges stay unchanged. 
Polygon spatial_annealing(Polygon polygon, PointVector points, bool goal = MINIMALIZATION) {

  Polygon old_polygon;
  int L = 5000;
  double Temperature = 1.0;

  // Keep convex hull to check "energy".
  Polygon convex_hull;
  CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(convex_hull));
  double ch_area = CGAL::abs(convex_hull.area());

  double energy = compute_energy(polygon, ch_area, goal);

  // Loop.
  while(Temperature > 0) {

    old_polygon = polygon;

    // Try applying a step until a valid step is made. 
    while(!spatial_global_step(&polygon));

    // Energy and ΔΕ. 
    double new_energy = compute_energy(polygon, ch_area, goal);
    double difference = new_energy - energy;


    // Check if the step passes and the change is accepted.
    if((difference < 0) || (metropolis(difference, Temperature))) {
      // The change passes. The polygon is updated.
      // Keep new energy as current energy.
      energy = new_energy;
    }
    else {
      // The change is rejected. We go back to our old polygon.
      polygon = old_polygon;
    }


    // Temperature drops.
    Temperature -= (1.0 / (double) L);

  }

  return polygon;
}








// Spatial Subdivision Algorithm.
Polygon spatial_subdivision(PointVector points, bool goal) {

  // Sort points lexicografically.
  sort(points.begin(), points.end(), comparePoints);

  int m = 100;
  int k = ceil((double) (points.size() - 1) / (double) (m - 1));

  // Vector with all spals.
  std::vector<PointVector*> sets;


  // 1.
  // Split points to k spals of m points. 
  PointVector* set;

  bool keep_going = true;
  int i = 0;
  while(keep_going) {
    set = new PointVector();
    sets.push_back(set);
    i = fill_spal(set, points, i, m);
    if(i >= points.size()) keep_going = false;
    i--;
  }

  // Check for validity of last spal.
  // If last spal is not valid, merge it with the previous spal. 
  PointVector* last_spal = sets[sets.size() - 1];
  if(sets.size() > 1) {
    if(!check_leftmost(last_spal)) {
      append_spals(sets[sets.size() - 2], sets[sets.size() - 1]);
      sets.pop_back();
      delete last_spal;
    }
  }


  // 2.
  // Apply convex hull algorithm to all spals.
  // Apply Simulated Annealing with global step for each polygon. 

  // Vector of all resulting from convex hull algorithm polygons.
  std::vector<Polygon> results;
  for(int i = 0; i < sets.size(); i++) {
    // Spatial Convex Hull ensures the "pinned" edges stay. 
    Polygon first_step = spatial_convex_hull_algorithm(*sets[i]);
    // Spatial Annealing ensures the "pinned" edges stay. 
    Polygon result = spatial_annealing(first_step, *sets[i], goal);
    results.push_back(result);
  }


  // 3.
  // Merge all polygons into one big polygon.
  Polygon final_polygon = results[0];
  for(int i = 1; i < sets.size(); i++) {
    merge_polygons(&final_polygon, &results[i]);
  }


  // Free allocated memory.
  for(int i = 0; i < sets.size(); i++) {
    delete sets[i];
  }

  return final_polygon;

}





// Performs and checks validity of global step. 
// Returns true if the step is valid and the polygon is changed.
// Returns false if the step is invalid and the polygon stays the same.
bool spatial_global_step(Polygon* polygon) {

  Point Q;
  Polygon new_polygon = *polygon;
  
  
  // Finds rightmost and leftmost points and respective edges to "pin" them. 
  Point rightmost_point = *(new_polygon.right_vertex());
  Point leftmost_point = *(new_polygon.left_vertex());
  int right_index = position_of_point_in_polygon(new_polygon, rightmost_point);
  int left_index = position_of_point_in_polygon(new_polygon, leftmost_point);

  int next_of_left = left_index + 1;
  if(left_index == new_polygon.size() - 1) next_of_left = 0;
  int previous_of_right = right_index - 1;
  if(right_index == 0) previous_of_right = new_polygon.size() - 1;


  int point_q;
  do {
    point_q = rand() % (*polygon).size();
  // Making sure we don't change position of the rightmost or leftmost edge.
  } while((point_q == right_index) || (point_q == left_index) || (point_q == next_of_left) || (point_q == previous_of_right));

  int point_s;
  do {
    point_s = rand() % (*polygon).size();
  // Make sure Q != S and Q != T.
  // Also making sure we don't change position of the rightmost or leftmost edge.
  } while((point_s == left_index) || (point_s == previous_of_right) || (point_s == point_q) || ((point_s + 1) == point_q) || ((point_s == ((*polygon).size() - 1)) && (point_q == 0)));


  if(point_s == -1) return false;

  int point_t = point_s + 1;
  if(point_s == new_polygon.size() - 1)
    point_t = 0;


  Q = polygon->vertex(point_q);

  // Delete point Q.
  new_polygon.erase(new_polygon.begin() + point_q);

  if(point_q < point_s) {
    point_s--;
    point_t--;
  }

  if(point_s == -1) point_s = new_polygon.size() - 1;
  if(point_t == -1) point_t = new_polygon.size() - 1;

  // Insert point Q between points S and T.
  new_polygon.insert(new_polygon.begin() + point_t, Q);


  // Valid if polygon is still simple.
  if(new_polygon.is_simple()) {
    *polygon = new_polygon;
    return true;
  }
  else {
    return false;
  }

}




Polygon spatial_convex_hull_algorithm(PointVector input_points) {

  // Polygon initally is the convex hull.
  Polygon polygon;
  
  CGAL::convex_hull_2(input_points.begin(), input_points.end(), std::back_inserter(polygon));

  // Creating inner_points vector. A vector with all inner points. 
  PointVector inner_points;
  for(Point point : input_points) {
    if(!point_is_on_polygon(point, polygon)) {
      inner_points.push_back(point);
    }
  }


  Point not_visible_point(-1, -1);
  
  Point rightmost_point = *(polygon.right_vertex());
  Point leftmost_point = *(polygon.left_vertex());
  int right_index = position_of_point_in_polygon(polygon, rightmost_point);
  int left_index = position_of_point_in_polygon(polygon, leftmost_point);

  int previous_of_right = right_index - 1;
  if(right_index == 0) previous_of_right = polygon.size() - 1;

  Segment left_segment = polygon.edge(left_index);
  Segment right_segment = polygon.edge(previous_of_right);
  

  // While there are inner points.
  while(inner_points.size() > 0) {

    Tuple tuple;
    Segment edge;
    Point point;
    

    // Pick an edge and find the closest point to it.
    do {
      do {
        edge = pick_random_edge(polygon);
        // Make sure that "pinned down" edges are not chosen.
      } while((edge == left_segment) || (edge == right_segment));
      point = point_closest_to_edge(edge, inner_points, polygon);
      
    // Keep trying untill you find an edge with a visible point.
    // (There certainly must be one)
    } while(point == not_visible_point); 


    // Add the point to the polygon and remove it from the inner points.
    add_point_to_polygon(point, edge, &polygon);
    remove_point_from_vector(&inner_points, point);
  }

  return polygon;
}