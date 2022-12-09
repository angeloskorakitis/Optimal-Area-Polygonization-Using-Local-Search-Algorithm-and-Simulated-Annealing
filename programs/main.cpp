#include "../include/Polygonization_Using_Incremental_Algorithm.hpp"
#include "../include/Polygonization_Using_Convex_Hull_Algorithm.hpp"
#include <iostream>
#include <ctime>

#pragma one;
enum { MINIMALIZATION = true, MAXIMALIZATION = false };
enum { GLOBAL = false, LOCAL = true };


bool comparePoints(Point a, Point b) {
  if(a.x() < b.x()) return true;
  else if(a.x() > b.x()) return false;
  else {
    if(a.y() < b.y()) return true;
    else return false;
  }
}


// Returns true if Metropolis criterion holds, false otherwise.
bool metropolis(double difference, double temperature) {

  // Random number in [0,1].
  double random_number = ( (double) rand() / (double) RAND_MAX);

  double number = exp( -difference / temperature);
  // std::cout << "Metropolis! Numb = " << number << " R = " << random_number << std::endl;
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
// with any edges of the polygon that they have a point int the box.
bool edges_in_box_intersect(Polygon* polygon, Point p1, Point p2, Point p3, Point p4, PointVector points) {

  int pos1 = position_of_point_in_polygon(*polygon, p1);
  int pos2 = position_of_point_in_polygon(*polygon, p2);

  Segment to_check_1 = *((*polygon).edges_begin() + pos1);
  Segment to_check_2 = *((*polygon).edges_begin() + pos2);

  // std::cout << "Vivaldi Bassoon Concerto... to_check_1 = " << to_check_1 << " to_check_2 = " << to_check_2 << std::endl;


  for(Point point : points) {
    if((point == p2) || (point == p3)) continue;

    if(point == p1) {

      int point_index = position_of_point_in_polygon(*polygon, point);

      int previous_edge = point_index - 1;
      if(point_index == 0) {
        previous_edge = (*polygon).size() - 1;
      }

      Segment prev = *((*polygon).edges_begin() + previous_edge);

      // std::cout << "Vivaldi Bassoon Concerto... prev = " << prev << std::endl;

      Point intersection_point;

      Object result = CGAL::intersection(to_check_1, prev);
      // The intersection is a point.
      if (CGAL::assign(intersection_point, result)) {
        if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
          // std::cout << "Intersecting! prev1 " << intersection_point << std::endl;
          return true;
        }
      }
      result = CGAL::intersection(to_check_2, prev);
      // The intersection is a point.
      if (CGAL::assign(intersection_point, result)) {
        if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
          // std::cout << "Intersecting! prev2 " << intersection_point << std::endl;
          return true;
        }
      }
    }

    if(point == p4) {

      int point_index = position_of_point_in_polygon(*polygon, point);

      int next_edge = point_index;

      if(point_index == (*polygon).size()) {
        next_edge = 0;
      }

      Segment next = *((*polygon).edges_begin() + next_edge);

      // std::cout << "Vivaldi Bassoon Concerto... next = " << next << std::endl;

      Point intersection_point;

      Object result = CGAL::intersection(to_check_1, next);
      // The intersection is a point.
      if (CGAL::assign(intersection_point, result)) {
        if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
          // std::cout << "Intersecting! next1 " << intersection_point << std::endl;
          return true;
        }
      }
      result = CGAL::intersection(to_check_2, next);
      // The intersection is a point.
      if (CGAL::assign(intersection_point, result)) {
        if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
          // std::cout << "Intersecting! next2 " << intersection_point << std::endl;
          return true;
        }
      }

    }

    int point_index = position_of_point_in_polygon(*polygon, point);

    int previous_edge = point_index - 1;
    int next_edge = point_index;

    if(point_index == 0) {
      previous_edge = (*polygon).size() - 1;
    }
    if(point_index == (*polygon).size()) {
      next_edge = 0;
    }

    Segment prev = *((*polygon).edges_begin() + previous_edge);
    Segment next = *((*polygon).edges_begin() + next_edge);

    // std::cout << "Vivaldi Bassoon Concerto... prev = " << prev << " next = " << next << std::endl;

    Point intersection_point;

    Object result = CGAL::intersection(to_check_1, prev);
    // The intersection is a point.
    if (CGAL::assign(intersection_point, result)) {
      if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
        // std::cout << "Intersecting! prev1 " << intersection_point << std::endl;
        return true;
      }
    }
    result = CGAL::intersection(to_check_1, next);
    // The intersection is a point.
    if (CGAL::assign(intersection_point, result)) {
      if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
        // std::cout << "Intersecting! next1 " << intersection_point << std::endl;
        return true;
      }
    }
    result = CGAL::intersection(to_check_2, prev);
    // The intersection is a point.
    if (CGAL::assign(intersection_point, result)) {
      if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
        // std::cout << "Intersecting! prev2 " << intersection_point << std::endl;
        return true;
      }
    }
    result = CGAL::intersection(to_check_2, next);
    // The intersection is a point.
    if (CGAL::assign(intersection_point, result)) {
      if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
        // std::cout << "Intersecting! next2 " << intersection_point << std::endl;
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

  // std::cout << "About to check my box: LowestX = " << LowestX << " LowestY = " << LowestY << " HighestX =  " << HighestX << " HighestY = " << HighestY;
  // std::cout << " Corner1 = " << Corner1 << " Corner2 = " << Corner2 << std::endl;

  Box checkbox(Corner1, Corner2);

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


  // print_point_vector(in_the_box_points);

  if(edges_in_box_intersect(polygon, p1, p2, p3, p4, in_the_box_points))
    return false;


  return true;
}


// Performs and checks validity of global step. 
// Returns true if the step is valid and the polygon is changed.
// Returns false if the step is invalid and the polygon stays the same.
bool global_step(Polygon* polygon, Point Q = Point(-1,-1), Segment ST = Segment(Point(-1,-1), Point(-2,-2))) {

  Polygon new_polygon = *polygon;
  

  int point_q;
  if(Q == Point(-1,-1)) {
    point_q = rand() % (*polygon).size();
  }
  else {
    point_q = position_of_point_in_polygon(new_polygon, Q);
  }

  int point_s;
  if(ST == Segment(Point(-1,-1), Point(-2,-2))) {
    do {
      point_s = rand() % (*polygon).size();
    // Make sure Q != S and Q != T.
    } while((point_s == point_q) || ((point_s + 1) == point_q) || ((point_s == ((*polygon).size() - 1)) && (point_q == 0)));
  }
  else {
    point_s = position_of_segment_in_polygon(new_polygon, ST);
  }

  if(point_s == -1) return false;

  int point_t = point_s + 1;
  if(point_s == new_polygon.size() - 1)
    point_t = 0;


  Q = *((*polygon).begin() + point_q);
  Point S = *((*polygon).begin() + point_s);
  Point T = *((*polygon).begin() + point_t);


  // std::cout << "\tQ = " << Q << " S = " << S << " T = " << T << std::endl;

  // std::cout << "Διαγράφω το " << *(new_polygon.begin() + point_q) << std::endl;
  new_polygon.erase(new_polygon.begin() + point_q);
  // print_polygon(new_polygon);

  if(point_q < point_s) {
    point_s--;
    point_t--;
  }

  if(point_s == -1) point_s = new_polygon.size() - 1;
  if(point_t == -1) point_t = new_polygon.size() - 1;


  // std::cout << "Προσθέτω το Q = " << Q << " πριν το σημείο T = " << T << " point t = " << point_t << std::endl;
  new_polygon.insert(new_polygon.begin() + point_t, Q);


  if(new_polygon.is_simple()) {
    *polygon = new_polygon;
    // std::cout << "Valid!" << std::endl;
    return true;
  }
  else {
    // std::cout << "Reject..." << std::endl;
    return false;
  }

}


// Performs and checks validity of local step. 
// Returns true if the step is valid and the polygon is changed.
// Returns false if the step is invalid and the polygon stays the same.
bool local_step(Polygon* polygon, Tree* tree, Point Q = Point(-1,-1)) {

  Polygon new_polygon = *polygon;
  
  
  int point_q;
  if(Q == Point(-1,-1)) {
    point_q = rand() % (*polygon).size();
    Q = *((*polygon).begin() + point_q);
  }
  else {
    point_q = position_of_point_in_polygon(new_polygon, Q);
  }


  if(point_q == -1) return false;

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


  Point PrevQ = *(new_polygon.begin() + previous_of_q);
  Point NextQ = *(new_polygon.begin() + next_of_q);
  Point SecondAfterQ  = *(new_polygon.begin() + second_after_q);


  // std::cout << "\tQ = " << Q << " Previous = " << PrevQ << " Next = " << NextQ << std::endl;

  // std::cout << "Διαγράφω το NextQ " << *(new_polygon.begin() + next_of_q) << std::endl;
  new_polygon.erase(new_polygon.begin() + next_of_q);
  // print_polygon(new_polygon);


  if(next_of_q == 0) {
    previous_of_q--;
    point_q--;
    second_after_q--;
  }


  // std::cout << "Προσθέτω το R = " << NextQ << " πριν το σημείο Q = " << Q << std::endl;
  new_polygon.insert(new_polygon.begin() + point_q, NextQ);
  // print_polygon(new_polygon);

  // Checking if the new edges are intersecting. 
  Segment edge1(PrevQ, NextQ);
  Segment edge2(Q, SecondAfterQ);

  // std::cout << " Edge 1 = " << edge1 << " Edge 2 = " << edge2 << std::endl;

  Point intersection_point;
  
  
  Object result = CGAL::intersection(edge1, edge2);

  // The intersection is a point.
  if (CGAL::assign(intersection_point, result)) {
    // std::cout << "Intersecting! " << intersection_point << std::endl;
    return false;
  }




  if(step_is_valid(&new_polygon, tree, PrevQ, Q, NextQ, SecondAfterQ) && new_polygon.is_simple()) {
    *polygon = new_polygon;
    return true;
  }
  else {
    return false;
  }

}

Polygon simulated_annealing(Polygon polygon, PointVector points, bool goal, bool step);


bool check_rightmost(PointVector* spal) {
  std::cout << "Rightmost check." << std::endl;
  Polygon convex_hull;
  CGAL::convex_hull_2(spal->begin(), spal->end(), std::back_inserter(convex_hull));

  Polygon::Vertex_const_iterator rightpoint = convex_hull.right_vertex();
  Point point = *rightpoint; 
  int index = position_of_point_in_polygon(convex_hull, point);

  Segment edge;
  if(index != 0) 
    edge = convex_hull.edge(index - 1);
  else
    edge = convex_hull.edge(convex_hull.size() - 1);
  
  std::cout << "EDGE = " << edge << std::endl;
  
  // If the other endpoint of the edge is "higher" than the point, the check fails.
  if((edge.source().y() > point.y()) || edge.target().y() > point.y()) return false;

  return true;
}

bool check_leftmost(PointVector* spal) {
  std::cout << "Leftmost check." << std::endl;
  Polygon convex_hull;
  CGAL::convex_hull_2(spal->begin(), spal->end(), std::back_inserter(convex_hull));

  Polygon::Vertex_const_iterator leftpoint = convex_hull.left_vertex();
  Point point = *leftpoint; 
  int index = position_of_point_in_polygon(convex_hull, point);


  Segment edge = convex_hull.edge(index);
  
  std::cout << "EDGE = " << edge << std::endl;

  // If the other endpoint of the edge is "higher" than the point, the check fails.
  if((edge.source().y() > point.y()) || edge.target().y() > point.y()) return false;

  return true;
}

// Fills spal with points till the critirea are met. 
int fill_spal(PointVector* spal, PointVector points, int starting_index, int m) {
  bool last_spal = false;
  int i;
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


  print_point_vector(*spal);

  rightmost = check_rightmost(spal);
  if(starting_index != 0) 
    leftmost = check_leftmost(spal);

  if(starting_index == 0) leftmost = true;
  if(last_spal) { // Τι γίνεται αν το κοινό σημείο του τελευταίου είναι το χαμηλότερο όλων, οέο...;
    rightmost = true;
    leftmost = true;
  }

  while((!rightmost) || (!leftmost)) {
    std::cout << "Θα δούμε." << std::endl;

    spal->push_back(points[i++]);
    
    if(starting_index != 0) 
      leftmost = check_leftmost(spal);

    rightmost = check_rightmost(spal);


    if(i == points.size()) break;

  }

  std::cout << std::endl;
  return i;
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









//////////////////////// SPATIAL SUBDIVISION /////////////

PointVector testvec = points;

// Sort points lexicografically.
sort(testvec.begin(), testvec.end(), comparePoints);

std::cout << "Sorting..." << std::endl;
print_point_vector(testvec);


int m = 20;
int k = ceil((double) (testvec.size() - 1) / (double) (m - 1));


std::cout << "K = " << k << std::endl;

std::vector<PointVector*> sets;


// Split points to k vectors of m points. 
bool next_set = false;
PointVector* set;

bool keep_going = true;
int i = 0;
while(keep_going) {
  set = new PointVector();
  sets.push_back(set);
  i = fill_spal(set, testvec, i, m);
  if(i >= testvec.size()) keep_going = false;
  i--;
}







// Sets has k points to vectors of m points each.
for(int i = 0; i < sets.size(); i++) {
  std::cout << "This is set no. " << i << std::endl;
  std::cout << "Size of set = " << sets[i]->size() << std::endl;
  print_point_vector(*sets[i]);
}

return EXIT_SUCCESS;

// 1.
// Check all that need to be checked.
// "Pin down" rightmost and leftmost edge. 
std::vector<Polygon> hulls;
for(int i = 0; i < sets.size(); i++) {
  // CH για κάθε set. 
  Polygon convex_hull;
  CGAL::convex_hull_2(sets[i]->begin(), sets[i]->end(), std::back_inserter(convex_hull));
  hulls.push_back(convex_hull);
}

  std::cout << "Hulls." << std::endl;
for(int i = 0; i < hulls.size(); i++) {
  print_polygon(hulls[i]);
  std::cout << std::endl;
  std::cout << std::endl;
}

// 2.
// Apply Simulated Annealing with global step for each set. 
// for(int i = 0; i < sets.size(); i++) {
//   Polygon a_polygon = simulated_annealing(sets[i], ..., ..., ...);
// }

// 3.
// Merge all polygons into one big polygon.

// Free allocated memory.
for(int i = 0; i < sets.size(); i++) {
  delete sets[i];
}


return EXIT_SUCCESS;

































































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

  // Print output
  // print_output(polygon, points, output_file, algorithm, edge_selection, initialization, duration);

  // If the polygon is not simple then failure
  if(!polygon.is_simple()) return EXIT_FAILURE;
  



print_polygon(polygon);



// Polygon letsgo = simulated_annealing(polygon, points, MAXIMALIZATION, LOCAL);
// Polygon letsgo = simulated_annealing(polygon, points, MAXIMALIZATION, GLOBAL);
// Polygon letsgo = simulated_annealing(polygon, points, MINIMALIZATION, LOCAL);
Polygon letsgo = simulated_annealing(polygon, points, MINIMALIZATION, GLOBAL);
print_polygon(letsgo);

// std::cout << std::endl;
// if(local_step(&polygon, &tree)) {
//   std::cout << "Κάτι άλλαξεεε!" << std::endl;
// }
// else
//   std::cout << "Τίποτα δεν άλλαξε..." << std::endl;


// print_polygon(polygon);





  return EXIT_SUCCESS;
}







Polygon simulated_annealing(Polygon polygon, PointVector points, bool goal = MINIMALIZATION, bool step = GLOBAL) {

  Tree tree;

  for(int i = 0; i < points.size(); i++)
    tree.insert(points[i]);

  Polygon old_polygon;
  int L = 5000;
  double Temperature = 1.0;
  // int goal = MINIMALIZATION;
  // int goal = MAXIMALIZATION;


  // Keep convex hull to check "energy".
  Polygon convex_hull;
  CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(convex_hull));
  double ch_area = CGAL::abs(convex_hull.area());

  double energy = compute_energy(polygon, ch_area, goal);

  // std::cout << "Convex Hull Area = " << ch_area << " Min energy = " << energy << " Max energy = " << energy2 << std::endl;



  while(Temperature > 0) {

    // Try global step till a valid step is made.
    old_polygon = polygon;

    if(step == LOCAL)
      while(!local_step(&polygon, &tree));
    else if(step == GLOBAL)
      while(!global_step(&polygon));
    // std::cout << std::endl;
    // print_polygon(polygon);

    double new_polygon_area = CGAL::abs(polygon.area());

    double new_energy = compute_energy(polygon, ch_area, goal);
    // double new_energy2 = compute_energy(polygon, ch_area, false);

    double difference = new_energy - energy;

    // std::cout << "New polygon Area = " << new_polygon_area << " Min energy = " << new_energy << std::endl;
    // std::cout << "Difference = " << difference << std::endl;

    if((difference < 0) || (metropolis(difference, Temperature))) {
      // std::cout << "Όλα κομπλέ μπρω μου περνάς το vajb test." << std::endl;
      // The change passes. The polygon is updated.
      energy = new_energy;
    }
    else {
      // std::cout << "Δεν περνάς δεν περνάς." << std::endl;
      // The change is rejected. The polygon is not updated.
      polygon = old_polygon;
    }


    // double aykala = 1.0 / (double) L;
    // std::cout << "OJPA! aykala = " << aykala << std::endl; 
    // // Temperature = (double) (Temperature - (double) (1 / L));
    // Temperature = (double) (Temperature - aykala);


    Temperature -= (1.0 / (double) L);
    // std::cout << "Temperature = " << Temperature << std::endl;


  }




      std::cout << std::endl;
      std::cout << std::endl;

      // print_polygon(polygon);
  std::cout << "Convex Hull Area = " << ch_area << std::endl;
  std::cout << "Final Polygon Area = " << CGAL::abs(polygon.area()) << std::endl;
  std::cout << "Ratio = " << (100*CGAL::abs(polygon.area())) / ch_area << std::endl;
      std::cout << std::endl;
      std::cout << std::endl;


  return polygon;
}
