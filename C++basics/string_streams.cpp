/*
 * Playing a bit with std::string and std::stringstream
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <string> // std::string, std::to_string
#include <iostream> // std::cout, std::endl
#include <sstream>  // std::stringstream
#include <cstring> // strlen 
#include <iomanip> // std::fixed, std::setprecision, std::quoted

struct car {
	
	std::string model;
	int pr;
	double cc;
};

std::string concat(const std::string& s1,
				   const std::string& s2) {
	return s1 + s2;
}

int main() {

	std::string s = "abvgd";
	auto s1 = "alpha, beta" + s; 
	s1.append("dako iska oshte");
	
	decltype(s1) s2 = s1;
	
	std::cout << s2 << std::endl;

	
	std::string str = "Hello world";
	str[4] = 'u';
	str += "abasbas";
	std::cout << str << ' ' << strlen(str.c_str()) 
			  << ' ' << str.size() << std::endl;
	
	
	std::string num = std::to_string(10);
	
	std::cout << num << std::endl;
	
	std::string input;
	std::cin >> input;
	
	std::cout << concat(str, input) << std::endl;
	
	car c = { .model = "Audi", .pr = 300, .cc = 1.896 };
	
	// "{ "model": "Audi", "pr": 300, "cc": 1.9 }"
	
	std::cout << "\nJSON car : \n";
	std::stringstream ss;
	
	ss << "\n{\n"
	   << std::quoted("model") << ": " << c.model << ",\n"
	   << std::quoted("pr") << ": " << c.pr << ",\n"
	   << std::quoted("cc") << ": " << std::fixed << std::setprecision(1) << c.cc << '\n'
	   << "}\n";
	   
	std::cout << ss.str();
	
	std::cout << "string by string reading from string stream :\n";
	std::string sl;
	while (ss) {
		
		ss >> sl;
		if(ss) std::cout << sl << std::endl;
	}
	
	return 0;
}
