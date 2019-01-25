/*
 * Some functional programming features of C++17.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream>

// Binary folding.
// takes many arguments calculates left to right
template<typename... Args>
bool logical_and(Args... args) {
    return (true && ... && args);
}

// Unary folding.
template<typename... Args>
auto sum(Args... args) {
    return (... + args);
}

int main() {
	
	bool b = true;
	bool& b2 = b;
	if (logical_and(b, b2, true, false))
		std::cout << "true" << std::endl;

	std::cout << sum(1.0, 2.2f, 3); // == 6.2
}
