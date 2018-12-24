/*
 * A simple usage of regular expressions in C++11.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <regex>
#include <set>

int main() {
	
	std::string input = "device/0011, device/0017, device/0004, device/0021";
	
	int a;
	int i = sscanf("device/0011", "device/%d", &a);
	if (i > 0) {
		printf("old C is gold! value of a = %d\n\n", a);
	} else {
		printf("wrong input!\n");
	}
	
	std::string search_word = "device/";
	std::regex word_regex((search_word + "([0-9]{3,9})").c_str());
	
    auto words_begin = 
        std::sregex_iterator(input.begin(), input.end(), word_regex);
    auto words_end = std::sregex_iterator();
    
    std::cout << "Found "
              << std::distance(words_begin, words_end)
              << " devices\n";
	
	std::set<int> dev;
	
	for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        
        std::string match_str = match[1].str(); //get the parsed group of the number
		std::cout << "match was: " << match.str() << std::endl;
		dev.insert(std::stoi(match_str));
    }	
	
	for (int i : dev)
		std::cout << i << ", ";
	std::cout << std::endl;
	
	return 0;
}
