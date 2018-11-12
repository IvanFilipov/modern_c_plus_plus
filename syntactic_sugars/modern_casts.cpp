/*
 * Example usage of modern C++ casts
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

// sources : 
// http://www.cplusplus.com/doc/tutorial/typecasting/
// Effective C++ Scott Mayers

/// remember that in general case casting is a bad thing

#include <iostream>

void print(char* str) {

	std::cout << str << std::endl;
}

class Base { virtual void dummy() {} };

class Derived : public Base { int a; };

int main() {
		
	/* const_cast can be used to remove the constance */ 

	const char* str = "const_cast<>()?";

	// print(myStr); :(
	print(const_cast<char*>(str));

	/* static_cast is similar to C - style casts, but save - gives compile time errors */
	char c = 10;

	int* p = (int*)&c; // unsafe
	*p = 10; // OK
	// *p = 15000; // run - time error stack around c is corrupted 

	// int *p1 = static_cast<int*>(&c); //invalid type converse COMPILATION time error 
	int x = 10, y = 3;

	double res = static_cast<double>(x) / y;
	std::cout << "res = " << res << std::endl;
	
	/* dynamic_cast can be used for both upcasts and downcasts on polymorphic hierarchy */
	// on errors :
	// when pointers used -> nullptr 
	// when references    -> exception
	try {

		Base * pba = new Derived;
		Base * pbb = new Base;
		Derived * pd;

		pd = dynamic_cast<Derived*>(pba);
		if (pd == nullptr) 
			std::cout << "Null pointer on first type-cast.\n";

		pd = dynamic_cast<Derived*>(pbb);
		if (pd == nullptr) 
			std::cout << "Null pointer on second type-cast.\n";
	} catch (std::exception& e) {

		std::cout << "Exception: " << e.what(); 
	}

	/* reinterpret_cast all to all , casting bits , so can be very unsafe */
	// usage : casting between pointer to functions
	class A { /* ... */ };
	class B { /* ... */ };
	A* a = new A;
	B* b = reinterpret_cast<B*>(a);
	
	return 0;
}
