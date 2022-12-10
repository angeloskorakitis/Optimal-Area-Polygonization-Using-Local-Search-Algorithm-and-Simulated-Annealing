#include "../include/Polygonization_Using_Incremental_Algorithm.hpp"
#include "../include/Polygonization_Using_Convex_Hull_Algorithm.hpp"
#include <iostream>
#include <ctime>

#pragma one;




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



//// Μια περιγραφή της main:
//
//
//  Check arguments.
//
//
//  Αν ζητείται spatial subdivision:
//  Καλώ τη συνάρτηση spatial_subdivision με το point vector της
//  εισόδου δηλαδή τα αρχικά σημεία.
//  *δεν καλώ ποτέ τους αλγόριθμους της πρώτης εργασίας*   <-------------------------  ΣΗΜΑΝΤΙΚΟ!!!
//  Η συνάρτηση θα επιστρέψει το τελικό πολύγωνο και όλα τελείωσαν.
//
//
//  Αν δεν ζητείται spatial subdivision και ζητείται απλώς simulated annealing:
//  Καλώ κάποιον αλγόριθμο της πρώτης εργασίας να παράξει ένα πολύγωνο.
//  Αυτό το πολύγωνο το δίνω στη συνάρτηση simulated_annealing η οποία μου επιστρέφει 
//  το τελικό πολύγωνο και όλα τελείωσαν.
//
//
//  Και στις δύο αυτές συναρτήσεις (simulated_annealing και spatial_subdivision) υπάρχει όρισμα goal.
//  Αυτό αφορά το αν θέλω μεγιστοποίηση ή ελαχιστοποίηση του εμβαδού.
//  Ανάλογα με το τι δίνει ο χρήστης περνάω την κατάλληλη σταθερά
//  MAXIMALIZATION ή MINIMALIZATION που είναι σταθερές που έχουν
//  οριστεί σε κάποιο enum σε κάποιο .hpp κάπου.
//
//
//  Στη συνάρτηση simulated_annealing υπάρχει όρισμα step. 
//  Αυτό αφορά το αν θέλω να πραγματοποιείται global step ή local step.
//  Πάλι ανάλογα με το τι θέλει ο χρήστης περνάω τις σταθερές
//  GLOBAL ή LOCAL που είναι ορισμένες σε κάποιο enum σε κάποιο
//  .hpp.
//
//
//