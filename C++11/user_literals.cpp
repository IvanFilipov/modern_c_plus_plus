/*
 * Example usage of user defined literals.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream> // std::cout, std::endl
#include <cmath>    // std::llround

// `unsigned long long` parameter required for integer literal.
long long operator "" _celsius_to_farenheit(unsigned long long tempCelsius) {
  return std::llround(tempCelsius * 1.8 + 32);
}

int operator "" _int(const char* str, std::size_t) {
  return std::stoi(str);
}

int main() {
	
	std::cout << "24 Celsius equals to " 
	          << 24_celsius_to_farenheit
	          << " Farenheit"
	          << std::endl;
	
	int x = "123"_int;
	std::cout << "\"123\" as int : " << x << std::endl;
		
	return 0;
}
