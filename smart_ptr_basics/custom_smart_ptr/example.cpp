#include <iostream>
#include "smart_ptr.hpp"
#include "../widget.hpp"


int main() {

	//old style
	{
		widget* pObj = new widget;
		//....
		delete pObj; //could be easily forgotten
	}


	//following the idea of RAII :
	{
		smart_ptr<widget> smp_obj(new widget);
		
	} //destructor of smp_obj is called, so the memory is freed


	//some tests of our smart pointer functionality 
	{
		smart_ptr<widget> ptr(new widget(42));
		smart_ptr<widget> other;

		other = ptr; //"other" takes the ownership

		std::cout << "the value of pointed object is : " 
			<< (*other).get_val() << std::endl;

		std::cout << "or taken by the pointer : "
			<< other->get_val() << std::endl;

	} //memory for widget(42) is freed 

	return 0;
}
