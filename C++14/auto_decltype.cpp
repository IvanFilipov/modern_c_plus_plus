/*
 * Example usage of auto and decltype
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
 
 /// meaning : auto -> tell the compiler to deduce the type from the rhs
 /// meaning : decltype(expression) -> get the type of this expression

#include <iostream>
 
struct A { double x; };
const A* a;
 
decltype(a->x) y;       // type of y is double (declared type)
decltype((a->x)) z = y; // type of z is const double& (lvalue expression)
 
template<typename T, typename U>        // return type depends on template parameters
auto add(T t, U u) -> decltype(t + u) { // return type can be deduced since C++14
                                      
    return t + u;
}
 
int main() {
	
	// auto basics
	int a = 5;
	auto k = a + 10; // well a -> int, 10 -> int => k -> int
	std::string s = "string";
	auto res = s + "abv"; // s -> string, create string from "abv" -> result is op+ from two strings
	
    int i = 33;
    decltype(i) j = i * 2;
 
    std::cout << "i = " << i << ", "
              << "j = " << j << '\n';
	int x = 10;
	double y = 20.1;
	auto sum = add(x, y); // deduced type is double
	std::cout << sum << std::endl;
	
	// we can hold a lambda into auto variable
    auto f = [](int a, int b) -> int {
        return a * b;
    };
 
    decltype(f) g = f; // the type of a lambda function is unique and unnamed
    i = f(2, 2);
    j = g(3, 3);
 
    std::cout << "i = " << i << ", "
              << "j = " << j << std::endl;;
}
