/*
 * Playing a bit lambdas in C++14.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream>
#include <vector>
#include <set>
#include <memory>

int generator_init(int seed) { return seed + 11; }

int main() {
	
	int y = 11;
	// polymorphic lambda
	// in C++14 lambdas can have 'auto' parameters
	auto id = [&y] (auto x) { return x; };
	std::cout << id("alabala") << std::endl;
	std::cout << id(11) << std::endl;
	
	auto container_size = [](const auto& con) { return con.size(); };
	std::vector<int> v = { 1, 2, 3, 4, 5 };
	std::set<int> s = { 5, 1, 21, 23, 11, 18 };
	std::cout << container_size(v) << std::endl;
	std::cout << container_size(s) << std::endl;
	
	// Lambda capture initializers
	// in C++14 lambdas can initialize variables that with values
	// that are out of the current scope. The init expression is evaluated
	// when the lambda is created
	auto generator = [x = generator_init(10)]() mutable {
		return ++x; // x is created one with value from generator_init,
		// mutable is used, because x is changed on each call
	};
	
	for (int i = 0; i < 10; i++)
		std::cout << generator() << ", ";
	std::cout << std::endl;
	
	
	// also solves the problem with not copyable objects
	auto p = std::make_unique<int>(1);
	// auto task1 = [=] { *p = 5; }; // ERROR: std::unique_ptr cannot be copied
	// vs.
	auto task2 = [p = std::move(p)] { *p = 5; }; // OK: p is move-constructed into the closure object
	// the original p is empty after task2 is created
	
	return 0;
}
