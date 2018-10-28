#pragma once

//pretty simple class for use where :
//"whatever" class is the context

//if you don't want the output, just comment this line
#define DEBUG_PRINT

#ifdef DEBUG_PRINT
	#include <iostream>
#endif


class widget {

private:
	
	int val;
	
	void print_text(const char* text) {
		
		#ifdef DEBUG_PRINT
			std::cout << text; 
		#endif
	}

public:

	widget(int v = 11) : val(v) { print_text("object created!\n"); }
	~widget() { print_text("object destroied"); }

	//notice that op= and copy constructor are never called in this example
	widget& operator=(const widget& o) {

		val = o.val;
		print_text("object copied!\n"); 
		return *this;
	}

	widget(const widget& o) : val(o.val) { print_text("object copied!\n"); }

	int get_val() const { return val; }
};
