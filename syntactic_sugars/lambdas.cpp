/*
 * Playing a bit lambdas. For advanced usage see STL algorithms examples. 
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream>

int global_var = 23;

int main() {
	
	int y = 11;
	std::cout << "value of y before lambda : " << y << std::endl;
	// y is captured by ref
	[&y] () {
		
		std::cout << "global val into lambda : " << global_var << std::endl;
		// changing the value of y
		++y;
	} (); // instant call of the lambda
	
	std::cout << "value of y after lambda : " << y << std::endl;
	
	auto lambda = [] (int x, int y) -> int {
		// lambda in lambda with capture all objects by value
		[=] () {
			std::cout << "going to sum : " << x << ' ' 
			          <<  y << std::endl;
		}(); // run it
		
		return x + y;
	};
	// call with 10 and 20 parameters
	std::cout << lambda(10, 20) << std::endl;
	
	return 0;
}
