/*
 * Simple class representing a string, with move semantics
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#pragma once
#include <iosfwd>

class cstring {

private:
	// raw pointer to the data
	char* str_ptr;

public:
	// a static variable to calculate 
	// how many times a memory allocation has been made
	static int new_calls_cnt;
	//constructors
	cstring();
	cstring(const char* str);
	//copy constructor
	cstring(const cstring& rhs);
	//assignment operator 
	cstring& operator=(const cstring& rhs);
	//move constructor
	cstring(cstring&& rhs);
	//move assignment operator
	cstring& operator=(cstring&& rhs);
	//destructor
	~cstring();
	//input output operators
	friend std::ostream& operator<<(std::ostream& os, const cstring& rhs);
	friend std::istream& operator>>(std::istream& is, cstring& rhs);
	//friend only because we don't have operator+=, return type is not constant!
	friend cstring operator+(const cstring& lhs, const cstring& rhs);
};

