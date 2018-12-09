/*
 * Some syntax related to OOP.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
 
 #include <iostream> // std::cout
 #include <string>   // std::string
 
 /* explicit virtual overrides */
class base {
public :	
	virtual void do_work() = 0;
	void foo() {};
 	virtual ~base() {};
};
 
class derived : base {
public :
	void do_work() override {} ; // explicitly tells the that this method is an override
	// could save the day some time, when some method's name is mistyped.
	// void foo() override {}; // error foo is not virtual method
};
 
 /* final specifier */
class f_class final {};
// class d_class : f_class {}; // error final class cannot be derived

class A {
  virtual void foo();
};

class B : A {
  virtual void foo() final; // final method - won't be override more
};

struct C : B {
  // virtual void foo(); // error -- declaration of 'foo' overrides a 'final' function
};
 
 /* default special class functions */
class util {
public :
	int box;
	// we are OK with compiler generated special members
	// we can tell that implicitly
	util()                       = default;
	util(const util&)            = default;
	util(util&&)                 = default;
	util& operator=(const util&) = default;
	util& operator=(util&&)      = default;
	~util()                      = default;
};
 
 /* deleted special class functions */
 class nc_util {
public :
	int* box;
	
	nc_util(int b) : box(new int(b)) {};
	~nc_util() { delete box; }
	// we what to forbid compiler's generated special members:
	nc_util(const nc_util&)            = delete;
	nc_util(nc_util&&)                 = delete;
	nc_util& operator=(const nc_util&) = delete;
	nc_util& operator=(nc_util&&)      = delete;
	
};
 
 /* explicit conversion functions */
struct as_int {
	as_int(int) {} // converting constructor implicit constructor
};

struct not_as_int {
	explicit not_as_int(int) {} //cannot be used for converting 
};

void obj_int(const as_int& a) {}
void obj_not_int(const B& b) {}


struct as_bool {
  operator bool() const { return true; }
};

struct not_same_as_bool {
  explicit operator bool() const { return true; }
};

void convert() {
	
	as_int a1 = 1;    // OK: copy-initialization selects A::A(int)
	as_int a2(2);     // OK: direct-initialization selects A::A(int)
	as_int a5 = (as_int)1; // OK: explicit cast performs static_cast
	obj_int(5);       // OK: the function parameter is created using 5
	
//  not_as_int b1 = 1;  error: copy-initialization does not consider B::B(int)
	not_as_int b2(2);              // OK: direct-initialization selects B::B(int)
	not_as_int b5 = (not_as_int)1; // OK: explicit cast performs static_cast
	//obj_not_int(5); error: there is no constructor for converting from int to B
	
	// bool stuff //
	
	as_bool a{};
	if (a); // OK calls A::operator bool()
	bool ba = a; // OK copy-initialization selects A::operator bool()

	not_same_as_bool b{};
	if (b); // OK calls B::operator bool()
//	bool bb = b; // error copy-initialization does not consider B::operator bool()
}
 /* inline namespaces */

namespace program {
	namespace version1 {
		int get_version() { return 1; }
		bool is_first_version() { return true; }
	}
	inline namespace version2 {
		int get_version() { return 2; }
	}
}
 
 /* non-static data member initializers */

// all non-static data members can be initialized
// where declared, which helps when default constructor
// can be skipped
struct car {
 	int pr = 0;
 	double cl = 0.0;
 	std::string model = "";
 	// older syntax:
 	// car() : pr(0), cl(0), model("") {}
 };
 
int main() {
	
	// lets call some constructors
	// just for prove of concept
	nc_util nc(5);
	// test implicit/explicit constructors/operators
	convert();
	// test namespaces
	int version     = program::get_version();              // Uses getVersion() from Version2
	int old_version = program::version1::get_version();    // Uses getVersion() from Version1
//	bool first_version = program::is_first_version();      // Does not compile when Version2 is added
}
 
