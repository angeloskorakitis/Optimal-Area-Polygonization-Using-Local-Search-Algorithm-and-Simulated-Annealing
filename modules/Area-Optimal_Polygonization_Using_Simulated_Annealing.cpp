/////////////////////////////////////////////////////////////////////////////////
//
//
// Implementation of Polygonization Using Simulated Annealing
//
//
/////////////////////////////////////////////////////////////////////////////////


#include "Area-Optimal_Polygonization_Using_Simulated_Annealing.hpp"

enum { GLOBAL = false, LOCAL = true };
enum { MINIMALIZATION = true, MAXIMALIZATION = false };


//////////////////// LOCAL STEP ////////////////////


// Checks if the new edges created from the local step intersect
// with any edges of the polygon that they have a point in the kd-tree rectangular.
bool edges_in_box_intersect(Polygon* polygon, Point p1, Point p2, Point p3, Point p4, PointVector points) {

  int pos1 = position_of_point_in_polygon(*polygon, p1);
  int pos2 = position_of_point_in_polygon(*polygon, p2);

  Segment to_check_1 = *((*polygon).edges_begin() + pos1);
  Segment to_check_2 = *((*polygon).edges_begin() + pos2);

  // For each point in the rectangular.
  for(Point point : points) {
    // Ignore Q and NextOfQ.
    if((point == p2) || (point == p3)) continue;

    // If point is previous of Q.
    // Only check the edge before it.
    if(point == p1) {

      int point_index = position_of_point_in_polygon(*polygon, point);

      int previous_edge = point_index - 1;
      if(point_index == 0) {
        previous_edge = (*polygon).size() - 1;
      }

      Segment prev = *((*polygon).edges_begin() + previous_edge);

      Point intersection_point;
      Object result = CGAL::intersection(to_check_1, prev);
      // The intersection is a point.
      if (CGAL::assign(intersection_point, result)) {
        if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
          return true;
        }
      }
      result = CGAL::intersection(to_check_2, prev);
      // The intersection is a point.
      if (CGAL::assign(intersection_point, result)) {
        if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
          return true;
        }
      }
    }


    // If point is Second After Q.
    // Only check the edge after it.
    if(point == p4) {

      int point_index = position_of_point_in_polygon(*polygon, point);

      int next_edge = point_index;

      Segment next = *((*polygon).edges_begin() + next_edge);

      Point intersection_point;
      Object result = CGAL::intersection(to_check_1, next);
      // The intersection is a point.
      if (CGAL::assign(intersection_point, result)) {
        if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
          return true;
        }
      }
      result = CGAL::intersection(to_check_2, next);
      // The intersection is a point.
      if (CGAL::assign(intersection_point, result)) {
        if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
          return true;
        }
      }

    }


    // Point is another than Previous of Q, Q, Next of Q, Second After Q.
    // Check both edges next to this point.
    int point_index = position_of_point_in_polygon(*polygon, point);

    int previous_edge = point_index - 1;
    int next_edge = point_index;

    if(point_index == 0) {
      previous_edge = (*polygon).size() - 1;
    }

    Segment prev = polygon->edge(previous_edge);
    Segment next = polygon->edge(next_edge);

    Point intersection_point;
    Object result = CGAL::intersection(to_check_1, prev);
    // The intersection is a point.
    if (CGAL::assign(intersection_point, result)) {
      if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
        return true;
      }
    }
    result = CGAL::intersection(to_check_1, next);
    // The intersection is a point.
    if (CGAL::assign(intersection_point, result)) {
      if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
        return true;
      }
    }
    result = CGAL::intersection(to_check_2, prev);
    // The intersection is a point.
    if (CGAL::assign(intersection_point, result)) {
      if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
        return true;
      }
    }
    result = CGAL::intersection(to_check_2, next);
    // The intersection is a point.
    if (CGAL::assign(intersection_point, result)) {
      if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
        return true;
      }
    }

  }

  return false;
}



// Checks if a local step is valid.
bool step_is_valid(Polygon* polygon, Tree* tree, Point p1, Point p2, Point p3, Point p4) {

  Point HighestX, HighestY, LowestX, LowestY;

  // Find Highest X.
  if((p1.x() >= p2.x()) && (p1.x() >= p3.x()) && (p1.x() >= p4.x())) HighestX = p1;
  else if((p2.x() >= p1.x()) && (p2.x() >= p3.x()) && (p2.x() >= p4.x())) HighestX = p2;
  else if((p3.x() >= p1.x()) && (p3.x() >= p2.x()) && (p3.x() >= p4.x())) HighestX = p3;
  else if((p4.x() >= p1.x()) && (p4.x() >= p2.x()) && (p4.x() >= p3.x())) HighestX = p4;

  // Find Lowest X.
  if((p1.x() <= p2.x()) && (p1.x() <= p3.x()) && (p1.x() <= p4.x())) LowestX = p1;
  else if((p2.x() <= p1.x()) && (p2.x() <= p3.x()) && (p2.x() <= p4.x())) LowestX = p2;
  else if((p3.x() <= p1.x()) && (p3.x() <= p2.x()) && (p3.x() <= p4.x())) LowestX = p3;
  else if((p4.x() <= p1.x()) && (p4.x() <= p2.x()) && (p4.x() <= p3.x())) LowestX = p4;

  // Find Highest Y.
  if((p1.y() >= p2.y()) && (p1.y() >= p3.y()) && (p1.y() >= p4.y())) HighestY = p1;
  else if((p2.y() >= p1.y()) && (p2.y() >= p3.y()) && (p2.y() >= p4.y())) HighestY = p2;
  else if((p3.y() >= p1.y()) && (p3.y() >= p2.y()) && (p3.y() >= p4.y())) HighestY = p3;
  else if((p4.y() >= p1.y()) && (p4.y() >= p2.y()) && (p4.y() >= p3.y())) HighestY = p4;

  // Find Lowest Y.
  if((p1.y() <= p2.y()) && (p1.y() <= p3.y()) && (p1.y() <= p4.y())) LowestY = p1;
  else if((p2.y() <= p1.y()) && (p2.y() <= p3.y()) && (p2.y() <= p4.y())) LowestY = p2;
  else if((p3.y() <= p1.y()) && (p3.y() <= p2.y()) && (p3.y() <= p4.y())) LowestY = p3;
  else if((p4.y() <= p1.y()) && (p4.y() <= p2.y()) && (p4.y() <= p3.y())) LowestY = p4;

  Point Corner1(LowestX.x(), LowestY.y());
  Point Corner2(HighestX.x(), HighestY.y());

  Box checkbox(Corner1, Corner2);

  // Create Point vector with all points in kd-tree rectangular.
  std::filebuf fb;
  fb.open("mypointstempfile.txt", std::ios::out);
  std::ostream os(&fb);

  (*tree).search(std::ostream_iterator<Point>(os, "\n"), checkbox);
  PointVector in_the_box_points;
  fb.close();

  std::ifstream is("mypointstempfile.txt");
  int x, y;
  while(is >> x >> y) {
    in_the_box_points.push_back(Point(x,y));
  }

  if(remove("mypointstempfile.txt") != 0)
    perror("Error deleting file");


  if(edges_in_box_intersect(polygon, p1, p2, p3, p4, in_the_box_points))
    return false;


  return true;
}


// Performs and checks validity of local step. 
// Returns true if the step is valid and the polygon is changed.
// Returns false if the step is invalid and the polygon stays the same.
bool local_step(Polygon* polygon, Tree* tree) {

  Polygon new_polygon = *polygon;
  
  
  int point_q;
  point_q = rand() % (*polygon).size();


  int previous_of_q = point_q - 1;
  if(point_q == 0) {
    previous_of_q = new_polygon.size() - 1;
  }

  int next_of_q = point_q + 1;
  if(point_q == new_polygon.size() - 1) {
    next_of_q = 0;
  }

  int second_after_q = next_of_q + 1;
  if(next_of_q == new_polygon.size() - 1) {
    second_after_q = 0;
  }


  Point Q = polygon->vertex(point_q);
  Point PrevQ = new_polygon.vertex(previous_of_q);
  Point NextQ = new_polygon.vertex(next_of_q);
  Point SecondAfterQ  = new_polygon.vertex(second_after_q);


  // Delete point Next of Q.
  new_polygon.erase(new_polygon.begin() + next_of_q);

  if(next_of_q == 0) {
    previous_of_q--;
    point_q--;
    second_after_q--;
  }

  // Insert point Next of Q between points Previous of Q and Q.
  new_polygon.insert(new_polygon.begin() + point_q, NextQ);

  // Checking if the new edges are intersecting. 
  Segment edge1(PrevQ, NextQ);
  Segment edge2(Q, SecondAfterQ);


  Point intersection_point; 
  
  Object result = CGAL::intersection(edge1, edge2);
  // The intersection is a point.
  if (CGAL::assign(intersection_point, result)) {
    return false;
  }


  // Valid if polygon is still simple and kd-tree check passes.
  if(step_is_valid(&new_polygon, tree, PrevQ, Q, NextQ, SecondAfterQ) && new_polygon.is_simple()) {
    *polygon = new_polygon;
    return true;
  }
  else {
    return false;
  }

}








//////////////////// GLOBAL STEP ////////////////////


// Performs and checks validity of global step. 
// Returns true if the step is valid and the polygon is changed.
// Returns false if the step is invalid and the polygon stays the same.
bool global_step(Polygon* polygon) {

  Polygon new_polygon = *polygon;
  Point Q;


  // Pick a random Point Q and a random edge ST.
  int point_q;
  point_q = rand() % (*polygon).size();

  int point_s;
  do {
    point_s = rand() % (*polygon).size();
  // Make sure Q != S and Q != T.
  } while((point_s == point_q) || ((point_s + 1) == point_q) || ((point_s == ((*polygon).size() - 1)) && (point_q == 0)));


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







//////////////////// SIMULATED ANNEALING ////////////////////



// Simulated Annealing Algorithm.
Polygon simulated_annealing(Polygon polygon, PointVector points, bool goal = MINIMALIZATION, bool step = GLOBAL) {

  // Create kd-tree.
  Tree tree;

  for(int i = 0; i < points.size(); i++)
    tree.insert(points[i]);



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
    if(step == LOCAL)
      while(!local_step(&polygon, &tree));
    else if(step == GLOBAL)
      while(!global_step(&polygon));


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
