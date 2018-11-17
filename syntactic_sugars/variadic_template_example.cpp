/*
 * Example usage of variadic templates syntax.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
#include <iostream>
#include <string>

// recursion's bottom, adding with one argument
template<typename T>
T adder(const T& v) {
	
	return v;
}
// recursive variadic template, ... syntax is used
// for many arguments or zero from same type
template<typename T, typename... Args>
T adder(const T& first,const Args&... args) { // Args... is called parameter pack
	// sizeof... operator gives the count of arguments
	std::cout << "at the pack : " << sizeof...(Args) << std::endl;
	return first + adder(args...); // calling the same function with one parameter less
}

int main() {
	
	int sum = adder(1, 2, 3, 4, 5);
	std::cout << "sum = " << sum << std::endl;
	
	std::string s1 = "Obi ", s2 = "Wan ", s3 = "Kenobi :", s4 = "\"Hello there!\"";
	std::string ssum = adder(s1, s2, s3, s4);
	std::cout << "string sum = " << ssum << std::endl;
	
	return 0;
}
