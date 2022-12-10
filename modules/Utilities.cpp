/////////////////////////////////////////////////////////////////////////////////
//
//
//                                  Utilities  
//
//
/////////////////////////////////////////////////////////////////////////////////


#include "Utilities.hpp"


//________________________________Printing functions______________________________________


void print_point(Point point) {
  std::cout << point.x() << ", " << point.y() << std::endl;
}


void print_segment(Segment segment) {
  std::cout << segment.source().x() << "," << segment.source().y() <<  " - " << segment.target().x() << "," << segment.target().y() << std::endl;
}


void print_polygon(Polygon polygon) {
  for (EdgeIterator edge_itr = polygon.edges_begin(); edge_itr != polygon.edges_end(); ++edge_itr) 
    print_segment(*edge_itr);
}


void print_point_vector(PointVector points) {
  for(Point point : points) {
    print_point(point);
  }
}


void print_segment_vector(SegmentVector segments) {
  for(Segment segment : segments) {
    print_segment(segment);
  }
}


//______________________________Input/Output functions___________________________________


PointVector parse_file(std::string filename) {
  std::ifstream infile(filename);

  std::string line;
  std::getline(infile, line);
  std::getline(infile, line);

PointVector points;

  while (std::getline(infile, line))
  {
    std::istringstream iss(line);
    unsigned int count, x, y;
    if (!(iss >> count >> x >> y)) { break; } // error

        Point point(x, y);
        points.push_back(point);
  }

return points;
}


void print_output(Polygon polygon, PointVector points, std::string filename, std::string algorithm, int edge_selection, std::string initialization, std::chrono::duration<double> duration) {
  std::ofstream outfile(filename);
  try{
    if(outfile.is_open()) {
      outfile << "Polygonization" << std::endl;

      for(Point point : points) {
        outfile << point << std::endl;
      }

      for(EdgeIterator edge = polygon.edges_begin(); edge != polygon.edges_end(); edge++) {
        outfile << *edge << std::endl;
      }


      if(algorithm == "incremental") {
        outfile << "Algorithm: " << algorithm << "_edge_selection" << edge_selection << "_initialization" << initialization << std::endl;
      }
      else {
        outfile << "Algorithm: " << algorithm << "_edge_selection" << edge_selection << std::endl;
      }

      long int polygon_area = CGAL::abs(polygon.area());
      
      Polygon convex_hull;
      CGAL::convex_hull_2(polygon.begin(), polygon.end(), std::back_inserter(convex_hull));

      long double convex_hull_area = CGAL::abs(convex_hull.area());

      long double ratio =(long double)polygon_area / convex_hull_area;

      outfile << "area: " << polygon_area << std::endl;
      outfile << "ratio: " <<  ratio << std::endl;
      outfile << "construction time: " << duration.count();

      outfile.close();

    }
    else throw "Output file could not open.\n";
  }
  catch(String error_msg)
  {
    std::cerr << error_msg << std::endl;
  }  

  
}




// Returns index of point in polygon.
// Returns -1 if point doesn't exist in polygon.
int position_of_point_in_polygon(Polygon polygon, Point point) {
  int position = 0;
  bool found = false;
  for(VertexIterator i = polygon.begin(); i != polygon.end(); i++) {
    if(point == *i) {
      found = true;
      break;
    }
    position++;
  }

  if(found) return position;
  else return -1;
}


// Returns index of segment in polygon.
// Returns -1 if point doesn't exist in polygon.
int position_of_segment_in_polygon(Polygon polygon, Segment segment) {
  int position = 0;
  bool found = false;
  for(EdgeIterator i = polygon.edges_begin(); i != polygon.edges_end(); i++) {
    if((segment == *i) || (segment.opposite() == *i)) {
      found = true;
      break;
    }
    position++;
  }

  if(found) return position;
  else return -1;

}


// Compare Function for sorting point vectors.
bool comparePoints(Point a, Point b) {
  if(a.x() < b.x()) return true;
  else if(a.x() > b.x()) return false;
  else {
    if(a.y() < b.y()) return true;
    else return false;
  }
}


//////////////////// ENERGY ////////////////////


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
