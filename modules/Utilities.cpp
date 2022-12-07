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


void print_output(Polygon polygon_initial, 
                  Polygon polygon, 
                  PointVector points, 
                  std::string filename,
                  std::string algorithm_initial,
                  std::string algorithm,
                  std::string optimization, 
                  std::chrono::duration<double> duration) 
{
  std::ofstream outfile(filename);
  try{
    if(outfile.is_open()) {
      outfile << "Optimal Area Polygonization" << std::endl;

      for(Point point : points) {
        outfile << point << std::endl;
      }

      for(EdgeIterator edge = polygon.edges_begin(); edge != polygon.edges_end(); edge++) {
        outfile << *edge << std::endl;
      }

      outfile << "Algorithm: " << algorithm_initial << "_" << algorithm << "_" << optimization << std::endl;

      long int area_initial = CGAL::abs(polygon_initial.area());
      long int area = CGAL::abs(polygon.area());
      
      Polygon convex_hull;
      CGAL::convex_hull_2(polygon_initial.begin(), polygon_initial.end(), std::back_inserter(convex_hull));
      long int convex_hull_area = CGAL::abs(convex_hull.area());

      long double ratio_initial =(long double)area_initial / convex_hull_area;
      long double ratio =(long double)area / convex_hull_area;

      outfile << "area_initial: " << area_initial << std::endl;
      outfile << "area: " << area << std::endl;
      outfile << "ratio_initial: " <<  ratio_initial << std::endl;
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