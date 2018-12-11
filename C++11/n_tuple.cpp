/*
 * Playing a bit with n-tuples from C++11.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream>// std::cout
#include <string>  // std::string
#include <utility> // std::pair
#include <tuple>   // std::tuple, std::tie

using st_info = std::pair<int, std::string>;

int main() {
	
	st_info info;
	
	info.first = 45;
	info.second = "Pesho";
	
	std::cout << info.first << " "
			  << info.second << std::endl;
	
	st_info s = std::make_pair(50, "Vasko");
	
	std::cout << s.first << " "
			  << s.second << std::endl;	  
			  
	std::string name_only;
	
	std::tie(std::ignore, name_only) = s;		  
	
	std::cout << "name only :" << name_only << std::endl;
	
	auto mega_info = std::make_tuple(145, "bla", 20, 30);
	
	std::cout << std::get<0>(mega_info) << std::endl;
	
	std::tie(std::ignore, name_only, std::ignore, std::ignore) = mega_info;
	
	std::cout << "name only :" << name_only << std::endl;		  

	return 0;
}
