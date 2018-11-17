/*
 * Example usage of enum classes after C++11.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream> // std::cout, std::endl
#include <cstdint> // std::uint8_t
 
 
// old C++98 style enum
// creates global names
// the underlaying type is known : char or int, the compiler will choose
// can be used as ordinary variables in compare and assign operations
enum COLOR {
	WHITE,
	GREEN,
 	RED
};
 
// new type enum classes, after C++11
// creates scoped names
// the underlaying type can be specified
// can be used in statements where only their type is used
typedef std::uint8_t byte;
enum class UNI :  byte {
	FMI = 0, 
	UNSS,
	TU
};

int main() {
	
	std::cout << "size of old enum : " << sizeof(COLOR) << std::endl; // gives 4 with GCC
	std::cout << "size of new enum class : " << sizeof(UNI) << std::endl; // always 1
	
	int i = WHITE; // ok WHITE is global scoped, int or char
	std::cout << "value of WHITE : " << WHITE << std::endl; // ok, cout can handle char or int 
	
	COLOR c = GREEN;
	if (c < 10)
		std::cout << "wow GREEN is less than 10?!" << std::endl;
		
	// uni u = FMI; // error FMI is scoped
	UNI u = UNI::FMI;
	// if (u < 10) std::cout << "this won't compile...";
	if (u != UNI::UNSS)
		std::cout << "it is actually an uni!" << std::endl;
	
	std::cout << "hardcore print of value for FMI " << std::dec << static_cast<int	>(UNI::FMI);
}
