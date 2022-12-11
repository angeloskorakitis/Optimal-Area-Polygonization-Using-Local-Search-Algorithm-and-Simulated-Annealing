#include "Polygonization_Using_Incremental_Algorithm.hpp"
#include "Polygonization_Using_Convex_Hull_Algorithm.hpp"
#include "Area-Optimal_Polygonization_Using_Simulated_Annealing.hpp"
#include "Area-Optimal_Polygonization_Using_Local_Search.hpp"
#include "Area-Optimal_Polygonization_Using_Spatial_Division.hpp"
#include <iostream>
#include <ctime>

#pragma one;

enum { GLOBAL = false, LOCAL = true };
enum { MINIMALIZATION = true, MAXIMALIZATION = false };

int main(int argc, char *argv[])
{

  // Input parameters.
  String error_msg = "Unable to run the program.\nUsage: ./optimal_polygon –i <point set input file> –o <output file> -algorithm_initial <incremental or convex_hull> –algorithm <local_search or simulated_annealing> -L [L parameter according to algorithm] –max [maximal area polygonization] –min [minimal area polygonization] –threshold <double> [in local search] –annealing <\"local\" or \"global\" or \"subdivision\" in simulated annealing> \n";
  String input_file = "-1";
  String output_file = "-1";
  String algorithm = "-1";
  String algorithm_initial = "-1";
  int L = -1;
  double threshold = -1.0;
  String optimization = "-1";
  String annealing = "-1";

  // // Arguments count check.
  if((argc != 14) && (argc != 12)) 
  {
    std::cout << error_msg;
    return EXIT_FAILURE;
  }

  // Argument pass.
  for(int i = 1; i < argc; i++) {
    if(strcmp(argv[i], "-i") == 0) {
      input_file = argv[i+1];
    }
    else if(strcmp(argv[i], "-o") == 0) {
      output_file = argv[i+1];
    }
    else if(strcmp(argv[i], "-algorithm_initial") == 0) {
      algorithm_initial = argv[i+1];
    }
    else if(strcmp(argv[i], "-algorithm") == 0) {
      algorithm = argv[i+1];
    }
    if(algorithm=="local_search"){
      if(strcmp(argv[i], "-L") == 0) {
        L = atoi(argv[i+1]);
      }
      else if(strcmp(argv[i], "-threshold") == 0) {
        threshold = std::stod(argv[i+1]);
      }
      else if(strcmp(argv[i], "-max") == 0) {
        optimization = "max";
      }
      else if(strcmp(argv[i], "-min") == 0) {
        optimization = "min";
      }
    }
    else if(algorithm=="simulated_annealing"){
      if(strcmp(argv[i], "-max") == 0) {
        optimization = "max";
      }
      else if(strcmp(argv[i], "-min") == 0) {
        optimization = "min";
      }
      else if(strcmp(argv[i], "-annealing") == 0) {
        annealing = argv[i+1];
      }
    }
  }

  // Argument content check.
  try
  {
    if(input_file == "-1")  throw error_msg;
    if(output_file == "-1") throw error_msg;
    if(algorithm_initial == "-1")   throw error_msg;
    if(algorithm == "-1")   throw error_msg;
    if(optimization == "-1")   throw error_msg;
    if(threshold == -1.0) if(algorithm == "local_search")  throw error_msg;
    // Simulated annealing algorithm needs initialization according to documentation
    if(annealing == "-1") if(algorithm == "simulated_annealing") throw error_msg;
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

  Polygon polygon_initial;
  Polygon polygon;


  
  if(annealing!="subdivision"){
    // Calling the algorihm_initial function.
    if(algorithm_initial == "incremental") 
    {
      int edge_selection;
      String initialization = "1a";

      // If optimization is max the run incremental with min edge selection, else with max edge selection...
      if(optimization=="max") 
      {
        edge_selection = 3;
        polygon_initial = incremental_algorithm(points, edge_selection, initialization);
      }
      else{
        edge_selection = 2;
        polygon_initial = incremental_algorithm(points, edge_selection, initialization);
      } 
    }
    else if(algorithm_initial == "convex_hull") {
      //
      polygon_initial = convex_hull_algorithm(points, 1);
      //
    }
    else {
      std::cout << "Use a valid algorithm_initial name!" << std::endl;
      std::cerr << error_msg;
      return EXIT_FAILURE;
    }
  }

  // Calling the algorihm function.
  if(algorithm == "local_search") {
    polygon = local_search(polygon_initial, threshold, L, optimization);
  }
  else if(algorithm == "simulated_annealing") 
  {
    if(points.size() >= 1000)
    {
      if(optimization=="min") polygon = spatial_subdivision(points, MINIMALIZATION);
      else  polygon = spatial_subdivision(points, MAXIMALIZATION);
    }
    else if(annealing=="subdivision")
    {
      // spatial division is initialized with points, not with a polygon
      if(optimization=="min") polygon = spatial_subdivision(points, MINIMALIZATION);
      else  polygon = spatial_subdivision(points, MAXIMALIZATION);
    }
    else if(annealing=="local")
    {
      if(optimization=="min") polygon = simulated_annealing(polygon_initial, points, MINIMALIZATION, LOCAL);
      else polygon = simulated_annealing(polygon_initial, points, MAXIMALIZATION, LOCAL);
    }
    else
      if(optimization=="min") polygon = simulated_annealing(polygon_initial, points, MINIMALIZATION, GLOBAL);
      else polygon = simulated_annealing(polygon_initial, points, MAXIMALIZATION, GLOBAL);

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
  print_output(polygon_initial, 
                  polygon, 
                  points, 
                  output_file,
                  algorithm_initial,
                  algorithm,
                  optimization, 
                  duration);


  // If the polygon is not simple then failure
  if(!polygon_initial.is_simple()) return EXIT_FAILURE;

  // If the polygon is not simple then failure
  if(!polygon.is_simple()) return EXIT_FAILURE;
  
  return EXIT_SUCCESS;
}


