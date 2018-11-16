/*
 * Example usage of a custom dynamic array initializations.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream> // std::cout
#include "dynamic_array.hpp"

//for basic usage and tests see : https://github.com/IvanFilipov/FMI-DSA/blob/master/data_structures/dynamic_array/example.cpp

void init_tests () {
	
	// those are equal for built-in types
	int x = 0;
	int y(0);
	int z{0};
	int q = {0};
	
	std::cout << "x = " << x << std::endl
		<< "y = " << y << std::endl
		<< "z = " << z << std::endl
		<< "q = " << q << std::endl;
	std::cout << "----------------" << std::endl;
}

void test_different_constructors() {
	
	std::cout << "dynamic_array<int> darr; | default constructor :\n";
	dynamic_array<int> darr;
	darr.print_info(std::cout);
	darr.print_elems(std::cout);
	
	std::cout << "\ndynamic_array<int> darr = {}; | default constructor with {} :\n";
	dynamic_array<int> darr1 = {}; //same as darr1{}
	darr1.print_info(std::cout);
	darr1.print_elems(std::cout);

	std::cout << "\ndynamic_array<int> darr = { 11 }; | always initialize list is over constructors with same parameters?\n";
	dynamic_array<int> darr2 = { 11 }; //same as darr { 11 }
	darr2.print_info(std::cout);
	darr2.print_elems(std::cout);
	
	std::cout << "\ndynamic_array<int> darr{ 11 }; | always initialize list is over constructors with same parameters?\n";
	dynamic_array<int> darr3{ 11 }; //same as darr { 11 }
	darr3.print_info(std::cout);
	darr3.print_elems(std::cout);
	
	std::cout << "\ndynamic_array<int> darr( 11 );\n";
	dynamic_array<int> darr4( 11 );
	darr4.print_info(std::cout);
	darr4.print_elems(std::cout);
	
	std::cout << "\ndynamic_array<int> darr{ 11, 42 };\n";
	dynamic_array<int> darr5{ 11, 42 };
	darr5.print_info(std::cout);
	darr5.print_elems(std::cout);
	
	std::cout << "\ndynamic_array<int> darr( 11, 42 );\n";
	dynamic_array<int> darr6( 11, 42 );
	darr6.print_info(std::cout);
	darr6.print_elems(std::cout);

	std::cout << "\ndynamic_array<int> darr = { 1, 2, 3, 4, 5 }; [ initialize list ]\n";
	dynamic_array<int> darr7 = { 1, 2, 3, 4, 5 };
	darr7.print_info(std::cout);
	darr7.print_elems(std::cout);
	
	std::cout << "\ndynamic_array<int> darr = darr0; [ copy ]\n";
	dynamic_array<int> darr9 = darr7;
	darr9.print_info(std::cout);
	darr9.print_elems(std::cout);
		
	std::cout << "\ndynamic_array<int> darr1 = std::move(darr); [ move ]\n";
	dynamic_array<int> darr8 = std::move(darr9);
	std::cout << "\ndarr1 :\n";
	darr8.print_info(std::cout);
	darr8.print_elems(std::cout);
	std::cout << "\ndarr ( the moved one )  :\n";
	darr9.print_info(std::cout);
	darr9.print_elems(std::cout);
}


int main() {
	
	/* testing different methods of initializing a variable */
	init_tests();
	
	/* testing different methods of initializing our custom dynamic array */
	test_different_constructors();
	
	return 0;
}
