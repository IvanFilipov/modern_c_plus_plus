/*
 * Example usage of move semantics and RVO ( return value optimization )
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include<iostream>
#include "cstring.h"

// GCC flag to stop the RVO
// -fno-elide-constructors

// creates a cstring object from integer
cstring create_string_from_int(int x) {
	
	static char buff[64];
	sprintf(buff, "%d", x);
	// rand() is used to prevent RVO
	return (rand() % 25) ? cstring(buff) : cstring(nullptr);
}

void RVO_algo() {
	
	// if we have code like this
	cstring c = create_string_from_int(10);
	// the compiler "sees" :
	// cstring c;
	// create_string_from_int(10, c); // where create_string_from_int(int x, cstring& c)
	// is used
}


int main() {
	
	cstring s ("Hello, ");
	cstring t ("world!");
	cstring res = s + t; //without RVO and move ctor, will result in unnecessary copy
	
	cstring from_num;
	from_num = create_string_from_int(1001); // move operator=
	
	std::cout << res;
	std::cout << "\ntotal new calls : " << cstring::new_calls_cnt << '\n';
	//which will be called?
//	res = t + s; // move
//	t = s; // copy
//	t = std::move(s); // move
//	std::cout << s;
	
	return 0;
}
