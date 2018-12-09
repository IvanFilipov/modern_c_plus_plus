/*
 * Playing with some C++14 features - binary literals and integer sequences.
 * This file is part of the "Data structures and algorithms" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream> // std::cout
#include <iomanip>  // std::hex, std::bin
#include <tuple>    // std::tuple
#include <array>    // std::array
#include <utility>  // std::integer_sequence, std::make_index_sequence

// Convert array into a tuple
template<typename Array, std::size_t... I>
decltype(auto) a2t_impl(const Array& a, std::integer_sequence<std::size_t, I...>) {
	// for each argument of parameter pack
	// append the elem on that index from the array into the tuples
	return std::make_tuple(a[I]...);
}

template<typename T, std::size_t N, typename Indices = std::make_index_sequence<N>>
decltype(auto) a2t(const std::array<T, N>& a) {
	// takes and array and returns the result for that array
	// and all of it's indexes
	return a2t_impl(a, Indices());
}

int main() {
	
	int b = 0b10001;
	std::cout << "number 0b10001 as decimal : " << b << std::endl;
	
	std::array<int, 4> arr = {1, 2, 3, 4};
	
	auto tuple = a2t(arr);
	std::cout << std::get<0>(tuple) << std::endl;;
	std::cout << std::get<1>(tuple) << std::endl;;
	std::cout << std::get<2>(tuple) << std::endl;;
	std::cout << std::get<3>(tuple) << std::endl;;
	
	return 0;
}
