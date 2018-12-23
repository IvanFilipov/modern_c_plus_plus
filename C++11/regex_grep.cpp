/*
 * A simple grep-like program to show how regular expressions work in C++11.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Nikolay Babulkov	
 */

#include <iostream> // std::cerr
#include <regex>    // std::regex, std::regex_match
#include <string>   // std::string
#include <fstream>  // std::ifstream

const std::string USAGE = " <regex_pattern> <filename>";

int main(int argc, char *argv[]) {
	
	if (argc != 3) {
		std::cerr << argv[0] + USAGE << std::endl;
		return 1;
	}

	std::string pattern(argv[1]);
	pattern = ".*" + pattern + ".*";

	std::regex rg;
	try {
		rg.assign(pattern);
	} catch (std::regex_error& e) {
		std::cerr << "Invalid regex pattern: " << e.what() << std::endl;
		return 1;
	}

	const std::string filename(argv[2]);
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Invalid filename: " << filename << std::endl;
		return 1;
	}

	std::string line;
	while (getline(file, line)) {
	  	if (std::regex_match(line, rg))
			std::cout << line << std::endl;
	}
	file.close();

	return 0;
}
