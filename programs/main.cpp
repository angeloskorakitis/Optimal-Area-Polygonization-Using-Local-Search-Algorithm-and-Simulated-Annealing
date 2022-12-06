#include "../include/Polygonization_Using_Incremental_Algorithm.hpp"
#include "../include/Polygonization_Using_Convex_Hull_Algorithm.hpp"
#include <iostream>
#include <ctime>

#pragma one;


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

bool edges_in_box_intersect(Polygon* polygon, Point p1, Point p2, Point p3, Point p4, PointVector points) {

  int pos1 = position_of_point_in_polygon(*polygon, p1);
  int pos2 = position_of_point_in_polygon(*polygon, p2);

  Segment to_check_1 = *((*polygon).edges_begin() + pos1);
  Segment to_check_2 = *((*polygon).edges_begin() + pos2);

  std::cout << "Vivaldi Bassoon Concerto... to_check_1 = " << to_check_1 << " to_check_2 = " << to_check_2 << std::endl;


  for(Point point : points) {
    if((point == p1) || (point == p2) || (point == p3) || (point == p4)) continue;

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

    std::cout << "Vivaldi Bassoon Concerto... prev = " << prev << " next = " << next << std::endl;

    Point intersection_point;

    Object result = CGAL::intersection(to_check_1, prev);
    // The intersection is a point.
    if (CGAL::assign(intersection_point, result)) {
      if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
        std::cout << "Intersecting! prev1 " << intersection_point << std::endl;
        return true;
      }
    }
    result = CGAL::intersection(to_check_1, next);
    // The intersection is a point.
    if (CGAL::assign(intersection_point, result)) {
      if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
        std::cout << "Intersecting! next1 " << intersection_point << std::endl;
        return true;
      }
    }
    result = CGAL::intersection(to_check_2, prev);
    // The intersection is a point.
    if (CGAL::assign(intersection_point, result)) {
      if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
        std::cout << "Intersecting! prev2 " << intersection_point << std::endl;
        return true;
      }
    }
    result = CGAL::intersection(to_check_2, next);
    // The intersection is a point.
    if (CGAL::assign(intersection_point, result)) {
      if((!(intersection_point == p1)) && (!(intersection_point == p2)) && (!(intersection_point == p3)) && (!(intersection_point == p4))) {
        std::cout << "Intersecting! next2 " << intersection_point << std::endl;
        return true;
      }
    }

  }

  return false;
}



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

  std::cout << "About to check my box: LowestX = " << LowestX << " LowestY = " << LowestY << " HighestX =  " << HighestX << " HighestY = " << HighestY;
  std::cout << " Corner1 = " << Corner1 << " Corner2 = " << Corner2 << std::endl;

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


  print_point_vector(in_the_box_points);

  if(edges_in_box_intersect(polygon, p1, p2, p3, p4, in_the_box_points))
    return false;


  return true;
}



bool global_step(Polygon* polygon, Point Q = Point(-1,-1), Segment ST = Segment(Point(-1,-1), Point(-2,-2))) {

  Polygon new_polygon = *polygon;
  

  int point_q;
  if(Q == Point(-1,-1)) {
    point_q = rand() % (*polygon).size();
  }
  else {
    point_q = position_of_point_in_polygon(new_polygon, Q);
  }

  
  if(point_q == -1) return false;

  int previous_of_q = point_q - 1;

  if(point_q == 0) {
    previous_of_q = new_polygon.size() - 1;
  }
  
  
  int point_s;
  if(ST == Segment(Point(-1,-1), Point(-2,-2))) {
    point_s = rand() % (*polygon).size();
  }
  else {
    point_s = position_of_segment_in_polygon(new_polygon, ST);
  }

  if(point_s == -1) return false;

  int point_t = point_s + 1;
  if(point_s == new_polygon.size() - 1)
    point_t = 0;


  
  Point PrevQ = *(new_polygon.begin() + previous_of_q);


  std::cout << "\tQ = " << Q << " S = " << ST.source() << " T = " << ST.target() << std::endl;
  std::cout << "\tPrevQ = " << PrevQ << std::endl;

  std::cout << "Προσθέτω το Q = " << Q << " πριν το σημείο T = " << ST.target() << std::endl;
  new_polygon.insert(new_polygon.begin() + point_t, Q);
  int new_point_q = point_t++;

  if(point_t <= point_q) {
    point_q++;
    previous_of_q++;
  }

  std::cout << "Διαγράφω το " << *(new_polygon.begin() + point_q) << std::endl;
  new_polygon.erase(new_polygon.begin() + point_q);

  if(point_q < point_s) {
    point_s--;
    new_point_q--;
    point_t--;
  }

  if(new_polygon.is_simple()) {
    *polygon = new_polygon;
    return true;
  }
  else {
    return false;
  }

}


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

  int next_of_q =  point_q + 1;
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


  std::cout << "\tQ = " << Q << " Previous = " << PrevQ << " Next = " << NextQ << std::endl;

  std::cout << "Διαγράφω το NextQ " << *(new_polygon.begin() + next_of_q) << std::endl;
  new_polygon.erase(new_polygon.begin() + next_of_q);
  print_polygon(new_polygon);


  std::cout << "Προσθέτω το R = " << NextQ << " πριν το σημείο Q = " << Q << std::endl;
  new_polygon.insert(new_polygon.begin() + point_q, NextQ);
  print_polygon(new_polygon);

  // Checking if the new edges are intersecting. 
  Segment edge1(PrevQ, NextQ);
  Segment edge2(Q, SecondAfterQ);

  std::cout << " Edge 1 = " << edge1 << " Edge 2 = " << edge2 << std::endl;

  Point intersection_point;

  Object result = CGAL::intersection(edge1, edge2);

  // The intersection is a point.
  if (CGAL::assign(intersection_point, result)) {
    std::cout << "Intersecting! " << intersection_point << std::endl;
    return false;
  }




  if(step_is_valid(&new_polygon, tree, PrevQ, Q, NextQ, SecondAfterQ)) {
    *polygon = new_polygon;
    return true;
  }
  else {
    return false;
  }

}



int main(int argc, char *argv[]) {


// Tree tree;

// tree.insert(Point(0,0));
// tree.insert(Point(10,10));
// tree.insert(Point(0,10));
// tree.insert(Point(10,0));
// tree.insert(Point(3,3));
// tree.insert(Point(5,6));
// tree.insert(Point(8,9));
// tree.insert(Point(9,2));

// tree.insert(Point(-10,0));
// tree.insert(Point(1,17));
// tree.insert(Point(12,15));
// tree.insert(Point(3,3));
// tree.insert(Point(3,-2));
// tree.insert(Point(5,-6));
// tree.insert(Point(-8,-9));
// tree.insert(Point(9,1));

// // tree.print();

//   // Initialize the search structure, and search all N points
//   Point query(5,5);
//   Neighbor_search search(tree, query, 4);
//    // report the N nearest neighbors and their distance
//   // This should sort all N points by increasing distance from origin
//   for(Neighbor_search::iterator it = search.begin(); it != search.end(); ++it)
//     std::cout << it->first << " "<< std::sqrt(it->second) << std::endl;


//   Point A(0, 0);
//   Point B(10, 10);

//   Box my_box(A, B);

//   if(my_box.contains(Point(3,7))) {
//     std::cout << "Box Contains 3 7!" << std::endl;
//   }
//   else {
//     std::cout << "Box DOES NOT contain 3 7!" << std::endl;
//   }

//   if(my_box.contains(Point(13,2))) {
//     std::cout << "Box Contains 13 2!" << std::endl;
//   }
//   else {
//     std::cout << "Box DOES NOT contain 13 2!" << std::endl;
//   }

//   if(my_box.contains(Point(3,12))) {
//     std::cout << "Box Contains 3 12!" << std::endl;
//   }
//   else {
//     std::cout << "Box DOES NOT contain 3 12!" << std::endl;
//   }

//   if(my_box.contains(Point(-1, 5))) {
//     std::cout << "Box Contains -1 5!" << std::endl;
//   }
//   else {
//     std::cout << "Box DOES NOT contain -1 5!" << std::endl;
//   }

//   if(my_box.contains(Point(0, 5))) {
//     std::cout << "Box Contains 0 5!" << std::endl;
//   }
//   else {
//     std::cout << "Box DOES NOT contain 0 5!" << std::endl;
//   }

//   if(my_box.contains(Point(10, 10))) {
//     std::cout << "Box Contains 10 10!" << std::endl;
//   }
//   else {
//     std::cout << "Box DOES NOT contain 10 10!" << std::endl;
//   }

//   if(my_box.contains(Point(10, 1))) {
//     std::cout << "Box Contains 10 1!" << std::endl;
//   }
//   else {
//     std::cout << "Box DOES NOT contain 10 1!" << std::endl;
//   }

//   if(my_box.contains(Point(7, -1))) {
//     std::cout << "Box Contains 7 -1!" << std::endl;
//   }
//   else {
//     std::cout << "Box DOES NOT contain 7 -1!" << std::endl;
//   }


//   std::filebuf fb;
//   fb.open("mypointstempfile.txt", std::ios::out);
//   std::ostream os(&fb);

//   tree.search(std::ostream_iterator<Point>(os, "\n"), my_box);
//   PointVector in_the_box_points;
//   fb.close();

//   std::ifstream is("mypointstempfile.txt");
//   int x, y;
//   while(is >> x >> y) {
//     in_the_box_points.push_back(Point(x,y));
//   }

//   if(remove("mypointstempfile.txt") != 0)
//     perror("Error deleting file");


//   print_point_vector(in_the_box_points);


// exit(EXIT_SUCCESS);










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

// std::cout << std::endl;
// if(global_step(&polygon, Point(0,0), Segment(Point(2,2), Point(2,4)))) {
//   std::cout << "Κάτι άλλαξεεε!" << std::endl;
// }
// else
//   std::cout << "Τίποτα δεν άλλαξε..." << std::endl;




Tree tree;

for(int i = 0; i < points.size(); i++)
  tree.insert(points[i]);

// Keep convex hull to check "energy".
Polygon convex_hull;
CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(convex_hull));
double ch_area = CGAL::abs(convex_hull.area());

double energy = compute_energy(polygon, ch_area, true);
double energy2 = compute_energy(polygon, ch_area, false);

std::cout << "Convex Hull Area = " << ch_area << " Min energy = " << energy << " Max energy = " << energy2 << std::endl;



// Try global step till a valid step is made.
Polygon old_polygon = polygon;
while(!local_step(&polygon, &tree));
// while(!global_step(&polygon));






std::cout << std::endl;
if(local_step(&polygon, &tree)) {
  std::cout << "Κάτι άλλαξεεε!" << std::endl;
}
else
  std::cout << "Τίποτα δεν άλλαξε..." << std::endl;


// print_polygon(polygon);
























  return EXIT_SUCCESS;
}


