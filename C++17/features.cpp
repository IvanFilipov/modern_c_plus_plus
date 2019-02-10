/*
 * Example for some new features of C++17.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <string>
#include <utility>
#include <cstddef> // std::byte

/* printing stuff */
#include <iostream>
#include <iomanip>
#include <locale>
#include <cstdio>

#include <fcntl.h>
#include <io.h>

#include <Windows.h>

/// Template argument deduction for class templates
template <typename T = float>
struct Box {
  T foo;
  Box() : foo() {}
  Box(T v) : foo(v) {}
};
// type of foo can be deduced
Box b1 { 1 }; // OK Box<int>
Box b2;     // OK Box<float>

/// new rules for auto deduction from braced-init-list
void deduce_from_init_list() {
	// auto x1 {1, 2, 3};   // error: not a single element
	auto x2 = { 1, 2, 3 }; // decltype(x2) is std::initializer_list<int>
	auto x3 { 3 };   // decltype(x3) is int || until C++17 used to be std::initializer_list<int>
	auto x1 = { 3 }; // decltype(x1) is int || until C++17 used to be std::initializer_list<int>
	auto x4 { 3.0 }; // decltype(x4) is double
}

/// inline variables
// same semantic as with inlined functions,
// cannot be scoped
inline int x = 42;

/// playing with encoding, U8 string literals are added to C++17
void encode_play() {
	
	/* some windows stuff */
	// _setmode(_fileno(stdout), _O_U8TEXT);
	// setlocale(LC_ALL, "bulgarian.UTF-8");
	//SetConsoleOutputCP(CP_UTF8);
	//system("chcp 1251>0");
	// std::cout << u8"ала бала";
	// SetConsoleOutputCP(CP_UTF8);

	//std::cout << x;
	
	/// UTF-8 characters
	std::string text = u8"Привет";
	wchar_t c = u8'ъ';
	// std::cout << text << std::endl;
	/// UNICODE
	_setmode(_fileno(stdout), _O_U16TEXT);
    wprintf(L"Но какво, по дяволите, е това?\n");
    // std::wcout << L"Но какво, по дяволите, е това?\n";
    //printf("Ванака е хакер!\n");
}

void test_std_byte() {
	
	std::byte b { 0x11 };
	//int y = b; // error
	b |= std::byte(0x02);
	b <<= 2;
	std::cout << std::hex << std::to_integer<int>(b);
}

void test_structured_bindings() {
	
	std::pair<std::string, int> person = std::make_pair("vanaka", 11);
	auto [ name, _] = person;
	std::cout << name << std::endl;
	std::cout << _ << std::endl;
	
	auto t = std::make_tuple(1, 10.1, "tuple");
    const auto [ a, b, c] = t;
    
    std::cout << a << c << std::endl;
	
}

#include <variant>
/// std::variant is type safe union
void test_vairant() {
	std::variant<int, double> v {12};
	std::get<int>(v); // == 12
	std::get<0>(v); // == 12
	v = 12.0;
	std::get<double>(v); // == 12.0
	std::get<1>(v); // == 12.0
}


#include <optional>
/// std::optional - usage: could contain a value, on error will be empty
std::optional<std::string> create(bool b)
{
    if (b)
		return "modernC++";
    else
		return {};
}

void test_optional()
{
    std::cout << create(false).value_or("empty"); // == "empty"
    create(true).value(); // == "modernC++"
	// optional-returning factory functions are usable as conditions of while and if
    if (auto str = create(true)) {
        // ..
        std::cout << str.value();
    }
}

int main() {
	
	std::cout << "inlined x :" << x << std::endl;
	
	test_structured_bindings();
	
	encode_play();
	
	test_vairant();
	
	test_optional();
	
	test_std_byte();
	
 	return 0;
}
