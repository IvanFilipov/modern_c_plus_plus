/*
 * Simple class representing a string, with move semantics
 * This file is part of the "Modern c plus plus" course. FMI 2018
 *
 * Author : Ivan Filipov	
 */

#include <iomanip> // std::setw
#include <iostream> // std::cout
#include <string.h> // strcpy, strcat
#include <stdlib.h> // rand

#include "cstring.h"

int cstring::new_calls_cnt = 0;

//solves the problem with nullptr checks everywhere
cstring::cstring() {

	str_ptr = new char[1];
	++new_calls_cnt;
	*str_ptr = '\0';
	std::cout << "constructor working!\n";
}

cstring::cstring(const char *src) {
	
	std::cout << "constructor with parameter working!\n";
	
	if (src != nullptr) {

		str_ptr = new char[strlen(src) + 1];
		++new_calls_cnt;
		strcpy(str_ptr, src);
	} else {

		str_ptr = new char[1];
		++new_calls_cnt;
		*str_ptr = '\0';
	}
}

cstring::cstring(const cstring &rhs) {
	
	std::cout << "copy constructor working!\n";
	str_ptr = new char[strlen(rhs.str_ptr) + 1];
	++new_calls_cnt;
	strcpy(str_ptr, rhs.str_ptr);
}

cstring::cstring(cstring&& rhs) : str_ptr(rhs.str_ptr) {

	std::cout << "move constructor working!\n";
	rhs.str_ptr = nullptr; 
}

cstring& cstring::operator=(const cstring& rhs) {
	
	std::cout << "operator= working!\n";
	if (this != &rhs) {

		delete[]str_ptr;

		str_ptr = new char[strlen(rhs.str_ptr) + 1];
		++new_calls_cnt;
		strcpy(str_ptr, rhs.str_ptr);
	}

	return *this;
}

cstring& cstring::operator=(cstring&& rhs) {
	
	std::cout << "move operator= working!\n";
	
	if (this != &rhs) {

		delete[] str_ptr;

		str_ptr = rhs.str_ptr;
		rhs.str_ptr = nullptr;
	}
	//or just std::swap(str_ptr, rhs.str_ptr)
	
	return *this;
}


cstring::~cstring() {
	
	std::cout << "destructor working!\n";
	delete[] str_ptr;
}

std::ostream& operator<<(std::ostream& os, const cstring &obj) {

	return os << obj.str_ptr;
}

std::istream& operator>>(std::istream& is, cstring &obj) {

	static char buff[1024];

	//reads up to 1024 or until space / new line
	is >> std::setw(1024) >> buff; 

	delete[] obj.str_ptr; // clears the old data !!!

	obj.str_ptr = new char[strlen(buff) + 1];

	strcpy(obj.str_ptr, buff);

	return is;
}

cstring operator+(const cstring &lhs, const cstring &rhs) {
	
	cstring res;
	delete[] res.str_ptr;
	res.str_ptr = new char[strlen(lhs.str_ptr) + strlen(rhs.str_ptr) + 1];

	strcpy(res.str_ptr, lhs.str_ptr);
	strcat(res.str_ptr, rhs.str_ptr);
	
	//uncomment to fake the RVO 
	//return rand() % 4 ? res : cstring(nullptr);
	return res;
}
