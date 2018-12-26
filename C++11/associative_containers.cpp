/*
 * Example usage of STL's associative containers and template aliases.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream>
#include <algorithm>

#include <array>
#include <vector>
#include <string> 

#include <set>
#include <unordered_set>

#include <map>
#include <unordered_map>

using st_info = std::pair<int, std::string>;

// a custom hash function,
// because there is not default
// for hashing std::pair
// we "inject" it into std:: namespace
namespace std {
	template<>
	struct hash<st_info> {
		
		size_t operator()(const st_info& st) const {
		
			using std::size_t;
			using std::hash;
			using std::string;
			
			string str = to_string(st.first);
			str += '|'; //adding a non digit character
			str += st.second;
			return hash<string>{}(str);
		}
	};
}

template<typename Set>
void test_set(Set& s_set) {
	
	s_set.insert(std::make_pair(45489, "Sashko"));
	s_set.insert(std::make_pair(12345, "Hacker"));
	s_set.insert(std::make_pair(46123, "Clang_master"));
	s_set.insert(std::make_pair(41234, "Sbndio"));
	s_set.insert(std::make_pair(45289, "Misho"));
	s_set.insert(std::make_pair(45255, "Dakomir"));
	s_set.insert(std::make_pair(47123, "Kriskchakis"));
	s_set.insert(std::make_pair(41234, "Sandio"));
	
	for (const auto& s : s_set) {
		
		std::cout << "{ " << s.first << ", "
				  << s.second << " }" << std::endl;
	}
	std::cout << std::endl;
	auto it = s_set.find(std::make_pair(45255, "Dakomir"));
	
	if (it != s_set.end()) {
		
		std::cout << "removing : { " << it->first << ", "
				  << it->second << " }" << std::endl;
		s_set.erase(it);
	}
	
	std::cout << "\ntrying to insert { 47123, Java Lover }..." << std::endl;
	// insert returns a pair of iterator and boolean
	auto res = s_set.insert(std::make_pair(47123, "Java Lover"));
	// res.second will be false if we already have this key
	if (!res.second)
		std::cout << "Sorry, Java Lover, there is no room for you here!" << std::endl;
	
	std::cout << std::endl;
	for (const auto& s : s_set) {
		std::cout << "{ " << s.first << ", "
				  << s.second << " }" << std::endl;
	}
}

template<typename Map>
void test_map(Map& s_map) {
	
	s_map[46489] = "Sashko";
	s_map[12345] = "Hacker";
	s_map[46123] = "Clang_master";
	s_map[41234] = "Sbndio";
	s_map[46289] = "Misho";
	s_map[46123] = "Dakomir";
	s_map[47123] = "Kriskchakis";
	s_map[48234] = "Sandio";
	
	for (const auto& s : s_map) {
		
		std::cout << "{ key: " << s.first << ", value: "
				  << s.second << " }" << std::endl;
	}
	
	std::cout << "\nchanging data for key 12345:" << std::endl;
	// will insert if not present
	s_map[12345] = "Semeshko";
	std::cout << "new data: " << s_map[12345];
	std::cout << std::endl;
	
	std::cout << std::endl;
	auto it = s_map.find(45255);
	
	if (it != s_map.end()) {
		
		std::cout << "removing : { " << it->first << ", "
				  << it->second << " }" << std::endl;
		s_map.erase(it);
	}
	
	std::cout << "\ntrying to insert { 47123, Java Lover }..." << std::endl;
	// insert returns a pair of iterator and boolean
	auto res = s_map.insert(std::make_pair(47123, "Java Lover"));
	// res.second will be false if we already have this key
	if (!res.second)
		std::cout << "Sorry, Java Lover, there is no room for you here!" << std::endl;
	
	std::cout << std::endl;
	for (const auto& s : s_map) {
		std::cout << "{ " << s.first << ", "
				  << s.second << " }" << std::endl;
	}
}

// a template alias to std::array
template<typename T>
using arr_of_ten = std::array<T, 10>;

int main() {
	
	std::cout << "#### std::SET ####\n\n";
	std::set<st_info> s_set;
	test_set(s_set);
	std::cout << "--------------------\n\n";
	
	std::cout << "#### std::UNORDERED_SET ####\n\n";
	std::unordered_set<st_info> un_s_set;
	test_set(un_s_set);
	std::cout << "--------------------\n\n";
	
	std::cout << "#### std::MAP ####\n\n";
	std::map<int, std::string> s_map;
	test_map(s_map);
	std::cout << "--------------------\n\n";
	
	std::cout << "#### std::UNORDERED_MAP ####\n\n";
	std::unordered_map<int, std::string> s_un_map;
	test_map(s_un_map);
	std::cout << "--------------------\n\n";
	
	std::cout << "#### std::map with template alias ####\n\n";
	std::map<std::string, arr_of_ten<int>> st_fav_numbers;
	
	st_fav_numbers["pesho"] = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	st_fav_numbers["ivancho"] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	st_fav_numbers["mariika"] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	
	for (auto sfn : st_fav_numbers) {
		std::cout << sfn.first << "favorite numbers :\n";
		for (auto n : sfn.second)
			std::cout << n << ' ';
		std::cout << std::endl;
	}
	std::cout << "--------------------\n\n";
	
	// Right angle Brackets
	// in C++ before C++11, the right brackets should be written with
	// white spaces
	std::map<int, std::map<int, std::vector<std::string> > > old_map;
	// after C++11 there is no such rule anymore
	std::map<int, std::map<int, std::vector<std::string>>> new_map;
	
	
	return 0;
}
