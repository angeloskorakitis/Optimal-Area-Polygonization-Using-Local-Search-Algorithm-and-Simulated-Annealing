#include "../include/Polygonization_Using_Incremental_Algorithm.hpp"
#include "../include/Polygonization_Using_Convex_Hull_Algorithm.hpp"
#include <iostream>
#include <ctime>

#pragma one;
enum { MINIMALIZATION = true, MAXIMALIZATION = false };
enum { GLOBAL = false, LOCAL = true };


// Compare Function for sorting point vectors.
bool comparePoints(Point a, Point b) {
  if(a.x() < b.x()) return true;
  else if(a.x() > b.x()) return false;
  else {
    if(a.y() < b.y()) return true;
    else return false;
  }
}


Polygon spatial_subdivision(PointVector points, bool goal);


// Returns true if Metropolis criterion holds, false otherwise.
bool metropolis(double difference, double temperature) {

  // Random number in [0,1].
  double random_number = ( (double) rand() / (double) RAND_MAX);

  double number = exp( -difference / temperature);
  if(number >= random_number) return true;
  else return false;
}


// Computates the energy of the given polygon based on the convex hull area
// and uses the correct formula depending on the state of "minimalization" flag (true/false).
double compute_energy(Polygon polygon, double ch_area, bool minimalization) {
  if(minimalization) {
  double div = CGAL::abs(polygon.area()) / ch_area;
  return polygon.size() * div;
  }
  else {
    double div = CGAL::abs(polygon.area()) / ch_area;
    double sub = 1 - div;
    return polygon.size() * sub;
  }
}

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

Polygon simulated_annealing(Polygon polygon, PointVector points, bool goal, bool step);
Polygon spatial_annealing(Polygon polygon, PointVector points, bool goal);



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


int main(int argc, char *argv[]) {


  // Input parameters.
  String error_msg = "Unable to run the program.\nUsage: ./to_polygon -i <point set input file> -o <output file> -algorithm <incremental or convex_hull> -edge_selection <1 or 2 or 3> -initialization <1a or 1b or 2a or 2b | μόνο στον αυξητικό αλγόριθμο> \n";
  std::string input_file = "-1";
  std::string output_file = "-1";
  std::string algorithm = "-1";
  std::string initialization = "-1";
  int edge_selection = 0;

  // Arguments count check.
  if((argc != 9) && (argc != 11)) 
  {
    std::cout << error_msg;
    return EXIT_FAILURE;
  }

  // Argument pass.
  for(int i = 1; i < argc; i+=2) {
    if(strcmp(argv[i], "-i") == 0) {
      input_file = argv[i+1];
    }
    else if(strcmp(argv[i], "-o") == 0) {
      output_file = argv[i+1];
    }
    else if(strcmp(argv[i], "-algorithm") == 0) {
      algorithm = argv[i+1];
    }
    else if(strcmp(argv[i], "-edge_selection") == 0) {
      edge_selection = atoi(argv[i+1]);
    }
    else if(strcmp(argv[i], "-initialization") == 0) {
      initialization = argv[i+1];
    }
  }

  // Argument content check.
  try
  {
    if(input_file == "-1")  throw error_msg;
    if(output_file == "-1") throw error_msg;
    if(algorithm == "-1")   throw error_msg;
    // Incremental algorithm needs initialization according to documentation
    if(initialization == "-1") if(algorithm == "incremental") throw error_msg;
    if((edge_selection < 1) || (edge_selection > 3)) throw error_msg;
  }
  catch(String error_msg)
  {
      std::cerr << error_msg;
      return EXIT_FAILURE;
  }

  // Turn input file into points vector
  PointVector points = parse_file(input_file);

  // Starting timer
  auto start = std::chrono::high_resolution_clock::now();

  srand(time(NULL));






// If point size is greater than 1000 use subdivision. 
if(points.size() >= 1000) {
  Polygon poly = spatial_subdivision(points, MINIMALIZATION);
  std::cout << "Spatial Subdivision was used." << std::endl;
  print_polygon(poly);

  if(poly.is_simple()) std::cout << "Is simple!" << std::endl;

  Polygon convex_hull;
CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(convex_hull));
double ch_area = CGAL::abs(convex_hull.area());

std::cout << "Stats:" << std::endl;
std::cout << "Convex Hull Area = " << CGAL::abs(convex_hull.area()) << std::endl;
std::cout << "Area = " << CGAL::abs(poly.area()) << std::endl;
std::cout << "Ratio = " << (100 * CGAL::abs(poly.area())) / CGAL::abs(convex_hull.area()) << std::endl;

  return EXIT_SUCCESS;
}














  Polygon polygon;
  
  // Calling the algorihm function.
  if(algorithm == "incremental") {
    polygon = incremental_algorithm(points, edge_selection, initialization);
  }
  else if(algorithm == "convex_hull") {
    polygon = convex_hull_algorithm(points, edge_selection);
  }
  else {
    std::cout << "Use a valid algorithm name!" << std::endl;
    std::cerr << error_msg;
    return EXIT_FAILURE;
  }
  
  // Stoping timer
  auto stop = std::chrono::high_resolution_clock::now();
  
  // Running time
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);


  // If the polygon is not simple then failure
  if(!polygon.is_simple()) return EXIT_FAILURE;
  



print_polygon(polygon);

std::cout << std::endl;
std::cout << std::endl;

// Polygon letsgo = simulated_annealing(polygon, points, MAXIMALIZATION, LOCAL);
// Polygon letsgo = simulated_annealing(polygon, points, MAXIMALIZATION, GLOBAL);
// Polygon letsgo = simulated_annealing(polygon, points, MINIMALIZATION, LOCAL);
Polygon letsgo = simulated_annealing(polygon, points, MINIMALIZATION, GLOBAL);
print_polygon(letsgo);


Polygon convex_hull;
CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(convex_hull));
double ch_area = CGAL::abs(convex_hull.area());

std::cout << "Stats:" << std::endl;
std::cout << "Convex Hull Area = " << CGAL::abs(convex_hull.area()) << std::endl;
std::cout << "Area = " << CGAL::abs(letsgo.area()) << std::endl;
std::cout << "Ratio = " << (100 * CGAL::abs(letsgo.area())) / CGAL::abs(convex_hull.area()) << std::endl;




  return EXIT_SUCCESS;
}






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