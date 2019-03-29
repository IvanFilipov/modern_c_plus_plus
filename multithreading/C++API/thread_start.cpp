/*
 * Basic thread creation with C++ API.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <thread>
#include <iostream>

struct fun_obj {
	void operator()() {
		std::cout << "hello from the other side!\n";
	}
}f;

void say_hi() {
	std::cout << "hello from the other side!\n";
}

int main() {
		
	// function pointer
	// std::thread t(say_hi);
	
	// functor object
	// std::thread t(f);
	
	// lambda
	std::thread t([](){
		std::cout << "hello from the other side!\n";
	});
	
	// try to remove this :)
	t.join();
	
	return 0;
}
