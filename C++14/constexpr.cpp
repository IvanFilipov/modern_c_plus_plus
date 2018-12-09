/*
 * Playing a bit with constant expressions in C++11 and 14.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
 #include <iostream>
 // constexpr object => compile time known constant
// constexpr function => returns a constexpr result if called
//                       with constexpr params, acts like normal function else
 // noexcept means "this function doesn't throws an exception", this can be helpful
// for the compiler
constexpr bool is_prime_recursive(size_t number, size_t c) noexcept {
	
  return (c*c > number) ? true : 
           (number % c == 0) ? false : 
              is_prime_recursive(number, c+1);
}
 constexpr bool is_prime_func(size_t number) noexcept {
	
  return (number <= 1) ? false : is_prime_recursive(number, 2);
}
 // C++11 style -> only return statement
constexpr int pow11(int base, int exp) noexcept {
	
	return ((exp == 0) ? 1 : base * pow11(base, exp - 1));
}
 // C++14 style
constexpr int pow14(int base, int exp) noexcept {
	
	auto res = 1;
	for(int i = 0; i < exp; i++)
		res *= base;
	
	return res;
}
// self-explanatory 
int dummy_fnc() {
	
	return 42;
}
 int main() {
	
	int foo = 10;
	// constexpr int cexpr_foo = foo; // error foo is not a constant
 	const int cfoo = 10;
 	constexpr int cexpr_foo = cfoo; // OK cfoo is a constant
 	constexpr int cexpr_foo_number = 10; // OK 10 is compile time known
 	
 	// const int dummy = foo; // OK a constant
 	// constexpr int cexpr_dummy = dummy; // error dummy is not known compile time
	
	size_t num;
	std::cin >> num;
	//constexpr size_t res = is_prime_func(num); // error not known during compiling
	std::cout << "number " << num << ' ' 
			  << ((is_prime_func(num)) ? "is prime!" : "is compose!") // run time
			  << std::endl;
	
	std::cout << "number " << 23 << ' ' 
			  << ((is_prime_func(23)) ? "is prime!" : "is compose!") // compile time
			  << std::endl;
 	constexpr int b = 2, e11 = 11, e14 = 14;
	constexpr int pow11res = pow11(b, e11); // ok known during compile time
	std::cout << "pow11( " << b << ", " << e11 << " ) = "
			  << pow11res << std::endl;
	
	std::cout << "pow14( " << b << ", " << e14 << " ) = "
			  << pow14(b, e14) << std::endl; // using compile time version
			  
	int b_run = 2, e_run = 13;
	std::cout << "pow14( " << b_run << ", " << e_run << " ) = "
			  << pow14(b_run, e_run); // using run time version
	
	return 0;
}
