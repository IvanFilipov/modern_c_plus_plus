/*
 * Example for usage of modern smart pointers ( std::unique, std::shared, std::weak )
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */
 
#include <memory> // std::unique, std::shared, std::weak
#include "widget.hpp"

int main() {
	
	/// ----------------- UNIQUE -----------------
	// some tests of unique_ptr functionality 
	// ADVICE : use unique_ptr where you have used raw pointer
	{	
		std::cout << "basic UNIQUE ptr :\n";
		//std::unique_ptr<widget> ptr = (new widget(42)); // NOT preferred
		std::unique_ptr<widget> ptr = std::make_unique<widget>(42); // after c++ 14
		std::unique_ptr<widget> other;

		// other = ptr; //copy if forbidden
		other = std::move(ptr); // "other" takes the ownership

		std::cout << "the value of pointed object is : " 
			<< (*other).get_val() << std::endl;

		std::cout << "or taken by the pointer : "
			<< other->get_val() << std::endl;

	} // memory for widget(42) is freed
	
	{
		
		std::cout << "\n\nUNIQUE ptr arrays :\n";
		//std::unique_ptr<widget> arr_ptr(new widget[2]); // WRONG!!!
		std::unique_ptr<widget[]> arr_ptr(new widget[2]);
		std::cout << "value taken from array : "
				<< arr_ptr[1].get_val() << std::endl;
	
	}
	
	/// ----------------- SHARED -----------------
	
	{
		std::cout << "\n\nbasic SHARED ptr :\n";
		std::shared_ptr<widget> outside = std::make_shared<widget>(55);
		std::cout << "object is pointed by : " 
			<< outside.use_count() << " shared pointers\n";
		{
			std::shared_ptr<widget> inside = outside; // reference count + 1, copied pointer
			std::cout << "object is pointed by : " 
				<< outside.use_count() << " shared pointers\n";
			std::cout << "leaving inside\n";
		}
		std::cout << "object is pointed by : " 
			<< outside.use_count() << " shared pointers\n";
	}
	std::cout << "left outside\n";
	
	{
		std::cout << "\n\nSHARED ptr from UNIQUE :\n";
		std::unique_ptr<widget> ptr = std::make_unique<widget>(42); // after c++ 14
		std::shared_ptr<widget> s_ptr = std::move(ptr); // it's okay to convert unique to shared, but NOT in the opposite way
	}
	
	/// ----------------- WEAK -----------------
	{
		std::cout << "\n\nbasic WEAK ptr :\n";
		std::weak_ptr<int> w;
		{
			std::shared_ptr<int> s = std::make_shared<int>(42);
			w = s;
			if (!w.expired()) { 
				std::cout << "the weak one still points to the resource!\n"
					<< "the resource is pointed by " << w.use_count() << "shared pointers\n";
			}
		}
		
		if (w.expired()) std::cout << "the weak one is dangling!\n";
	}
	
	return 0;
}
