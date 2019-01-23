/*
 * Constant expression "ïf" and lambdas in C++17.
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <iostream>

auto identity = [](int n) constexpr { return n; };

int main() {
	
	static_assert(identity(123) == 123, "LOL");
	
	if constexpr (identity(123) == 123)
		std::cout << "I got compiled :)";
	else
		std::cout << "I didn't :(";
	
	
	constexpr auto add = [](int x, int y) {
		auto L = [=] { return x; };
		auto R = [=] { return y; };
		return [=] { return L() + R(); };
	};

	static_assert(add(1, 2)() == 3);
	
	// lambda *this* capture
	struct foo {
		int value {123};
		auto get_val_copy() {
			return [*this] { return value; };
		}
		auto get_val_ref() {
			return [this] { return value; };
		}
	};
	
    foo mo;
    auto vcopy = mo.get_val_copy();
    auto vref = mo.get_val_ref();
    mo.value = 321;
    std::cout << vcopy(); // 123
    std::cout << vref(); // 321
}
