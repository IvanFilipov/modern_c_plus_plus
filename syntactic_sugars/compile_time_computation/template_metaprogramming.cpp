/*
 * Example of template metaprogramming - calculate n! = ? during compile time. 
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
 
#include <iostream>

// recursive template declaration of fact<N>
template<unsigned int N>
struct fact {
	enum { enum_value = N * fact<N-1>::enum_value };
	// or 
	static const unsigned int value = N * fact<N-1>::value;
};
// recursion's bottom
template<>
struct fact<0> {
	enum { enum_value = 1 };
	// or
	static const unsigned int value = 1;
};

int main() {
	
	std::cout << "with enum 5! = " << fact<5>::enum_value << " | "
	          << "with static const 5! = " << fact<5>::value
	          << std::endl;
	std::cout << "10! = " << fact<10>::value << std::endl;
	std::cout << "20! = " << fact<20>::value << std::endl;
	
	return 0;
}
