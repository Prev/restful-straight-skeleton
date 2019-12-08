#include<boost/shared_ptr.hpp>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Polygon_2.h>
#include<CGAL/create_straight_skeleton_2.h>
#include "print.h"
typedef CGAL::Exact_predicates_inexact_constructions_kernel K ;
typedef K::Point_2 Point ;
typedef CGAL::Polygon_2<K> Polygon_2 ;
typedef CGAL::Straight_skeleton_2<K> Ss ;
typedef boost::shared_ptr<Ss> SsPtr ;

int main(int argc, char* argv[])
{
	Polygon_2 poly ;
	
	if (argc == 1 || argc % 2 == 0) {
		std::cout << "Usage: cgal_api <point1.x> <point1.y> [<point2.x> <point2.y> ...]";
		return -1;
	}

	int num_points = (argc - 1) / 2;
	for (int i = 0; i < num_points; i++) {
		double x = std::stod(argv[2 * i + 1]);
		double y = std::stod(argv[2 * i + 2]);

		poly.push_back( Point(x, y) );
	}

	// poly.push_back( Point(-1,-1) ) ;
	// poly.push_back( Point(0,-12) ) ;
	// poly.push_back( Point(1,-1) ) ;
	// poly.push_back( Point(12,0) ) ;
	// poly.push_back( Point(1,1) ) ;
	// poly.push_back( Point(0,12) ) ;
	// poly.push_back( Point(-1,1) ) ;
	// poly.push_back( Point(-12,0) ) ;

	// You can pass the polygon via an iterator pair
	SsPtr iss = CGAL::create_interior_straight_skeleton_2(poly.vertices_begin(), poly.vertices_end());
	// Or you can pass the polygon directly, as below.

	// To create an exterior straight skeleton you need to specify a maximum offset.
	double lMaxOffset = 5 ;
	SsPtr oss = CGAL::create_exterior_straight_skeleton_2(lMaxOffset, poly);

	print_straight_skeleton(*iss);
	std::cout << "\n\n";

	print_straight_skeleton(*oss);

	return 0;
}
