/*
 * A simple version of the old C++ smart pointer ( auto_ptr )
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#pragma once

// !!! auto_ptr is deprecated since C++11 
// and fully removed after C++17

//originally there wasn't standard support of arrays
//for example new [] ...

//nowadays std::unique_ptr, std::shared_ptr and 
//std::weak_ptr are used, see more in the next example
template<typename T>
class smart_ptr {

private:

	T* raw_ptr;
	
public:

	explicit smart_ptr(T* p = nullptr);
	smart_ptr(smart_ptr& rhs); //notice not constant, because we will take the ownership
	smart_ptr& operator=(smart_ptr& rhs);
	~smart_ptr();

public :
	// remove ownership
	T* release();
	// set new ownership, or nullptr
	void reset(T* p = nullptr);
	// access operators
	T& operator*() const;
	T* operator->() const;
};

template<typename T>
smart_ptr<T>::smart_ptr(T* p) : raw_ptr(p) {

}

template<typename T>
smart_ptr<T>::smart_ptr(smart_ptr<T>& other) : raw_ptr(other.release()) {
	
	// gets the ownership of the resource from the other object
}

template<typename T>
smart_ptr<T>::~smart_ptr() {

	delete raw_ptr;
}

template<typename T>
smart_ptr<T>& smart_ptr<T>::operator=(smart_ptr<T>& other) {

	if (this != &other)
		reset(other.release()); // frees our resource and gets other's

	return *this;
}

template<typename T>
T& smart_ptr<T>::operator*() const {

	return *raw_ptr;
}

template<typename T>
T* smart_ptr<T>::operator->() const {

	return raw_ptr;
}

template<typename T>
T* smart_ptr<T>::release() {

	// transfer the ownership
	T* old = raw_ptr;
	raw_ptr = nullptr;
	
	return old;
}

template<typename T>
void smart_ptr<T>::reset(T* p) {
	// free the resource and get the new one
	if (p != raw_ptr) {
	
		delete raw_ptr;
		raw_ptr = p;
	}
}
