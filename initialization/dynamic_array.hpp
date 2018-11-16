/*
 * Example implementation of custom dynamic array (focus on move semantics, ways of initialization).
 * This file is part of the "Modern c plus plus" course. FMI 2018/19
 *
 * Author : Ivan Filipov	
 */

#include <utility>           // std::swap
#include <stdexcept>        //standard exceptions
#include <iosfwd>           //forward declarations of ostreams
#include <initializer_list> //initializer_list

template<typename T>
class dynamic_array {

private :

	T* data_ptr;
	size_t cur_size;
	size_t capacity;

	bool is_sorted;

public:

	//THE BIG SIX
	dynamic_array();
	
	dynamic_array(const dynamic_array& rhs);
	dynamic_array& operator=(const dynamic_array& rhs);
	
	dynamic_array(dynamic_array&& rhs);
	dynamic_array& operator=(dynamic_array&& rhs);
	
	~dynamic_array();
	
	//ctor with one argument, allocates memory for n elements
	dynamic_array(size_t size);
	//ctor with two arguments - size and default value
	dynamic_array(size_t size, const T& default_value);
	//ctor from initializer list
	dynamic_array(std::initializer_list<T> ilist);

	//helpers
private:

	void copy_from(const dynamic_array& rhs);
   
	void resize(size_t new_cap);
	void to_zero();
	
	//returns the index of the searched element, -1 if there is no such element
	int binary_search(const T& el, int left, int right) const;
	int linear_search(const T& el) const;
	
public:

	//frees the allocated memory
	void clear();
	//add a new elem in the end
	void push_back(const T& new_el);
	//removes the last elem
	void pop_back();//both with amortized O(1) complexity,
					//because memory reallocations


	//new elem on random position
	void insert_at(size_t index , const T& new_el);

	//removes an elem on random position
	void remove_at(size_t index);

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	size_t get_size() const;
	size_t get_capacity() const;

	//searches for an element and returns it's index if founded  , -1 else
	int search(const T& el) const;

	//sorts the vector using the simple insertion sort algorithm
	void sort();

	//simple print functions
	void print_info(std::ostream& os) const;
	void print_elems(std::ostream& os) const; 
};

template<typename T>
dynamic_array<T>::dynamic_array() : data_ptr(nullptr), cur_size(0), capacity(0) {

	/*...*/
}

template<typename T>
dynamic_array<T>::~dynamic_array() {

	clear();
}

template<typename T>
dynamic_array<T>::dynamic_array(dynamic_array<T>&& rhs) : 
	data_ptr(rhs.data_ptr), cur_size(rhs.cur_size), capacity(rhs.capacity), is_sorted(rhs.is_sorted) {
	
	rhs.to_zero();
}

template<typename T>
dynamic_array<T>& dynamic_array<T>::operator=(dynamic_array<T>&& rhs) {
	
	std::swap(data_ptr, rhs.data_ptr);
	std::swap(cur_size, rhs.cur_size);
	std::swap(capacity, rhs.capacity);
	std::swap(is_sorted, rhs.is_sorted);
}
	
template<typename T>
dynamic_array<T>::dynamic_array(size_t size) : 
	data_ptr(new T[size]), cur_size(0), capacity(size), is_sorted(false) {
		//...
}

template<typename T>
dynamic_array<T>::dynamic_array(size_t size, const T& default_value) : dynamic_array(size) {
	
	for (size_t i = 0; i < size; i++)
		data_ptr[i] = default_value;
	cur_size = size;
}

template<typename T>
dynamic_array<T>::dynamic_array(std::initializer_list<T> ilist) : dynamic_array(ilist.size()) {
	
	is_sorted = true;
	size_t i = 0;
	for (const T& el : ilist) {
		data_ptr[i] = el;
		if (i > 0 && data_ptr[i] > data_ptr[i - 1])
			is_sorted = false;
		++i;
	}
	cur_size = i;
}

template<typename T>
void dynamic_array<T>::clear() {
	
	delete[] data_ptr;

	to_zero();
}

template<typename T>
void dynamic_array<T>::to_zero() {
	
	data_ptr = nullptr;
	cur_size = 0;
	capacity = 0;
	is_sorted = false;
}

template<typename T>
void dynamic_array<T>::copy_from(const dynamic_array<T>& rhs) {

	data_ptr = new T[rhs.capacity];

	//memcpy(data, other.data, sizeof(T)*other.CurSize);
	//will not do the trick, because it will make a shallow copy of
	//our objects
	for (size_t i = 0; i < rhs.cur_size; i++)
		data_ptr[i] = rhs.data_ptr[i];

	cur_size = rhs.cur_size;
	capacity = rhs.capacity;
	is_sorted = rhs.is_sorted;
}

template<typename T>
dynamic_array<T>::dynamic_array(const dynamic_array<T>& rhs) : data_ptr(nullptr), cur_size(0), capacity(0) {

	copy_from(rhs);
}

template<typename T>
dynamic_array<T>& dynamic_array<T>::operator=(const dynamic_array<T>& other) { 

	if (this != &other) {

		clear();
		copy_from(other);
	}
	
	return *this;
}

template<typename T>
void dynamic_array<T>::resize(size_t new_cap) {

	T *temp = data_ptr;

	data_ptr = new T[new_cap];

	for (size_t i = 0; i < cur_size; i++)
		data_ptr[i] = temp[i];
	
	capacity = new_cap;

	delete[] temp;
}

template<typename T>
void dynamic_array<T>::push_back(const T& new_el) {

	if (cur_size >= capacity) {

		size_t new_cap = (capacity == 0 ? 2 : capacity * 2);
		resize(new_cap);
	}

	data_ptr[cur_size++] = new_el;

	if (cur_size == 1) {

		is_sorted = true;
		return;
	}

	if (data_ptr[cur_size - 2] > data_ptr[cur_size - 1])
		is_sorted = false;
}

template<typename T>
void dynamic_array<T>::pop_back() {

	if (cur_size)
		cur_size--;
	else
		throw std::length_error("already empty!");

	if (cur_size * 2 <= capacity) {

		size_t new_cap = ((cur_size == 0) ? 0 : capacity / 2);
		resize(new_cap);
	}
}

template<typename T>
void dynamic_array<T>::insert_at(size_t index, const T& new_el) {
	
	bool sorted_before = is_sorted;

	push_back(new_el); //will take care of the memory 

	if (index >= cur_size) //the element should be the last one
		return;

	if (sorted_before)
		is_sorted = true; //maybe our elem will go to its sorted position

	//now we should 'roll' our element back to the wanted position 
	for (size_t i = cur_size - 1; i > index; i--) {

		if (data_ptr[i] > data_ptr[i - 1])
			is_sorted = false;

		std::swap(data_ptr[i], data_ptr[i - 1]);
	}
}

template<typename T>
void dynamic_array<T>::remove_at(size_t index) {

	if (index >= cur_size || cur_size == 1) { //just removes the last elem
		
		pop_back();
		return;
	}

	if (!is_sorted) { //faster version O(1), but can be unexpected
		
		std::swap(data_ptr[cur_size - 1], data_ptr[index]);	 //from the class' client
		pop_back();
		return;
	}

	//else ..
	for (size_t i = index; i < cur_size - 1; i++)
		std::swap(data_ptr[i], data_ptr[i+1]);

	pop_back();
}

template<typename T>
const T& dynamic_array<T>::operator[](size_t index) const {

	if (index >= cur_size)
		throw std::out_of_range("out of range!!!");

	return data_ptr[index];
}

template<typename T>
T& dynamic_array<T>::operator[](size_t index) {

	//casting is a bad idea in general, but
	//code duplication is even worse
	return const_cast<T&>(
			static_cast<const dynamic_array&>(*this)[index]
	);
}

template<typename T>
inline
size_t dynamic_array<T>::get_size() const {

	return cur_size;
}

template<typename T>
inline
size_t dynamic_array<T>::get_capacity() const {

	return capacity;
}

template<typename T>
void dynamic_array<T>::sort() {

	if (is_sorted)
		return;

	//complexity O(n^2)
	for (size_t i = 1; i < cur_size; i++)
		for (size_t j = i ; j > 0 && data_ptr[j] < data_ptr[j-1]; j--)
			std::swap(data_ptr[j], data_ptr[j-1]);

	is_sorted = true;
}

template<typename T>
int dynamic_array<T>::search(const T& el) const {

	if (is_sorted)
		return binary_search(el, 0, cur_size); // O(logN)
	
	return linear_search(el); // O(N)
}

template<typename T>
int dynamic_array<T>::binary_search(const T& el, int left, int right) const {

	//there is no such element
	if (left > right)
		return -1;

	int med = (left + right) / 2;

	if (data_ptr[med] == el)
		return med;

	if (data_ptr[med] > el)
		return binary_search(el, left, med - 1);

	if (data_ptr[med] < el)
		return binary_search(el, med + 1, right);
		
	//won't reach this line, but added just to stop compiler's complaining
	return -1;
}

template<typename T>
int dynamic_array<T>::linear_search(const T& el) const {

	for (size_t i = 0; i < cur_size; i++)
		if (data_ptr[i] == el)
			return i;

	return -1;
}

template<typename T>
void dynamic_array<T>::print_info(std::ostream& os) const {

	os  << "obj at : Ox" << this
		<< " buffer starts at : Ox" << data_ptr
		<< " length : " << cur_size
		<< " capacity : " << capacity << std::endl;
} 


template<typename T>
void dynamic_array<T>::print_elems(std::ostream& os) const {
	
	os << "content : ";
	
	if (cur_size == 0) {
		
		os << "{}" << std::endl;	
		return;
	}
	
	if (cur_size == 1) {
		
		os << '{' << data_ptr[0] << '}' << std::endl;
		return;
	}
	
	os << "{ ";
	for (size_t i = 0; i < cur_size - 1; i++)
		os << data_ptr[i] << ", ";
		
	os << data_ptr[cur_size - 1] << " }" << std::endl;
}
