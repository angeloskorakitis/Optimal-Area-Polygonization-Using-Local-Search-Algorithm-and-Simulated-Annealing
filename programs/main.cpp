#include "../include/Polygonization_Using_Incremental_Algorithm.hpp"
#include "../include/Polygonization_Using_Convex_Hull_Algorithm.hpp"
#include <iostream>
#include <ctime>

#pragma one;

bool global_step(Polygon* polygon, Point Q, Segment ST) {

  Polygon new_polygon = *polygon;
  
  int point_q = position_of_point_in_polygon(new_polygon, Q);

  if(point_q == -1) return false;

  int previous_of_q = point_q - 1;

  if(point_q == 0) {
    previous_of_q = new_polygon.size() - 1;
  }
  
  int point_s = position_of_segment_in_polygon(new_polygon, ST);
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


bool local_step(Polygon* polygon, Point Q) {

  Polygon new_polygon = *polygon;
  
  int point_q = position_of_point_in_polygon(new_polygon, Q);

  if(point_q == -1) return false;

  int previous_of_q = point_q - 1;

  if(point_q == 0) {
    previous_of_q = new_polygon.size() - 1;
  }

  int next_of_q =  point_q + 1;
  if(point_q == new_polygon.size() - 1) {
    next_of_q = 0;
  }

  
  Point PrevQ = *(new_polygon.begin() + previous_of_q);
  Point NextQ = *(new_polygon.begin() + next_of_q);


  std::cout << "\tQ = " << Q << " Previous = " << PrevQ << " Next = " << NextQ << std::endl;

  std::cout << "Διαγράφω το NextQ " << *(new_polygon.begin() + next_of_q) << std::endl;
  new_polygon.erase(new_polygon.begin() + next_of_q);
  print_polygon(new_polygon);


  std::cout << "Προσθέτω το R = " << NextQ << " πριν το σημείο Q = " << Q << std::endl;
  new_polygon.insert(new_polygon.begin() + point_q, NextQ);
  print_polygon(new_polygon);

  if(new_polygon.is_simple()) {
    *polygon = new_polygon;
    return true;
  }
  else {
    return false;
  }

}



int main(int argc, char *argv[]) {


Tree tree;

tree.insert(Point(0,0));
tree.insert(Point(10,10));
tree.insert(Point(0,10));
tree.insert(Point(10,0));
tree.insert(Point(3,3));
tree.insert(Point(5,6));
tree.insert(Point(8,9));
tree.insert(Point(9,2));

tree.insert(Point(-10,0));
tree.insert(Point(1,17));
tree.insert(Point(12,15));
tree.insert(Point(3,3));
tree.insert(Point(3,-2));
tree.insert(Point(5,-6));
tree.insert(Point(-8,-9));
tree.insert(Point(9,1));

// tree.print();

  // // Initialize the search structure, and search all N points
  // Point query(5,5);
  // Neighbor_search search(tree, query, 4);
  //  // report the N nearest neighbors and their distance
  // // This should sort all N points by increasing distance from origin
  // for(Neighbor_search::iterator it = search.begin(); it != search.end(); ++it)
  //   std::cout << it->first << " "<< std::sqrt(it->second) << std::endl;


  Point A(0, 0);
  Point B(10, 10);

  Box my_box(A, B);

  if(my_box.contains(Point(3,7))) {
    std::cout << "Box Contains 3 7!" << std::endl;
  }
  else {
    std::cout << "Box DOES NOT contain 3 7!" << std::endl;
  }

  if(my_box.contains(Point(13,2))) {
    std::cout << "Box Contains 13 2!" << std::endl;
  }
  else {
    std::cout << "Box DOES NOT contain 13 2!" << std::endl;
  }

  if(my_box.contains(Point(3,12))) {
    std::cout << "Box Contains 3 12!" << std::endl;
  }
  else {
    std::cout << "Box DOES NOT contain 3 12!" << std::endl;
  }

  if(my_box.contains(Point(-1, 5))) {
    std::cout << "Box Contains -1 5!" << std::endl;
  }
  else {
    std::cout << "Box DOES NOT contain -1 5!" << std::endl;
  }

  if(my_box.contains(Point(0, 5))) {
    std::cout << "Box Contains 0 5!" << std::endl;
  }
  else {
    std::cout << "Box DOES NOT contain 0 5!" << std::endl;
  }

  if(my_box.contains(Point(10, 10))) {
    std::cout << "Box Contains 10 10!" << std::endl;
  }
  else {
    std::cout << "Box DOES NOT contain 10 10!" << std::endl;
  }

  if(my_box.contains(Point(10, 1))) {
    std::cout << "Box Contains 10 1!" << std::endl;
  }
  else {
    std::cout << "Box DOES NOT contain 10 1!" << std::endl;
  }

  if(my_box.contains(Point(7, -1))) {
    std::cout << "Box Contains 7 -1!" << std::endl;
  }
  else {
    std::cout << "Box DOES NOT contain 7 -1!" << std::endl;
  }



  // tree.search(std::ostream_iterator<Point>(std::cout, "\n"), my_box);
  tree.search(std::ostream_iterator<Point>(std::cout, "\n"), my_box);

exit(EXIT_SUCCESS);










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

std::cout << std::endl;
if(local_step(&polygon, Point(0,0))) {
  std::cout << "Κάτι άλλαξεεε!" << std::endl;
}
else
  std::cout << "Τίποτα δεν άλλαξε..." << std::endl;


print_polygon(polygon);
























  return EXIT_SUCCESS;
}


