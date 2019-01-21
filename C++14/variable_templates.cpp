/*
 * Variable templates in C++14.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream>
#include <iomanip>
#include <limits>

// math constant with precision dictated by actual type
template<typename T> constexpr T pi = T(3.14159265358979323846L);

// lambda from C++14
auto area_of_circle_with_radius = [](auto r) { return pi<decltype(r)> * r * r; };
// normal function
//template<class T> T area_of_circle_with_radius(T r) { return pi<T> * r * r; }

int main() {
	
	long double r1 = 1.0;
	std::cout.precision(std::numeric_limits<long double>::max_digits10 - 1);
	
	std::cout << area_of_circle_with_radius(r1) // returns long double
	          << std::endl; 
	
	double r2 = 1.0;
	std::cout << area_of_circle_with_radius(r2) // returns double
	          << std::endl; 
	
	float r3 = 1.0;
	std::cout << area_of_circle_with_radius(r3); // returns float
	
	return 0;
}
