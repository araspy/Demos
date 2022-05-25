#include "Base_Array.h"
#include <stdexcept>


//
// Base_Array
//
template <typename T>
Base_Array <T>::Base_Array(void)
	: data_(nullptr),
	cur_size_(0),
	max_size_(0) {}


//
// Base_Array (size_t)
//
template <typename T>
Base_Array <T>::Base_Array(size_t length)
	: data_(new T[length]),
	cur_size_(length),
	max_size_(length) {}



//
// ~Base_Array
//
template <typename T>
Base_Array <T>::~Base_Array(void)
{
	delete[] data_;
}


//
// get
//
template <typename T>
T Base_Array <T>::get(size_t index) const
{
	if (index >= cur_size_) {
		throw std::out_of_range("out of bounds");
	}
	return data_[index];
}



//
// set
//
template <typename T>
void Base_Array <T>::set(size_t index, T value)
{
	if (index >= cur_size_) {
		throw std::out_of_range("out of bounds");
	}
	data_[index] = value;
}


//
// fill
//
template <typename T>
void Base_Array <T>::fill(T value)
{
	for (int i = 0; i < cur_size_; i++) {
		data_[i] = value;
	}
}


//
// find (char)
//
template  <typename T>
int Base_Array <T>::find(T value) const
{
	for (int i = 0; i < cur_size_; i++) {
		if (value == data_[i]) {
			return i;
		}
	}
	return -1;
}


//
// find (char, size_t) 
//
template <typename T>
int Base_Array <T>::find(T val, size_t start) const
{
	if (start >= cur_size_) {
		throw std::out_of_range("out of bounds");
	}
	for (int i = start; i < cur_size_; i++) {
		if (val == data_[i]) {
			return i;
		}
	}
	return -1;
}


//
// operator []
//
template <typename T>
T& Base_Array <T>::operator [] (size_t index)
{
	if (index >= cur_size_) {
		throw std::out_of_range("out of bounds");
	}
	return data_[index];
}


//
// operator [] 
//
template <typename T>
const T& Base_Array <T>::operator [] (size_t index) const
{
	if (index >= cur_size_) {
		throw std::out_of_range("out of bounds");
	}
	return data_[index];
}


//
// operator ==
//
template <typename T>
bool Base_Array <T>::operator == (const Base_Array& rhs) const
{
	if (*this == rhs) {
		return 0;
	}
	if (cur_size_ != rhs.size()) {
		return 0;
	}
	for (int i = 0; i < cur_size_; i++) {
		if (data_[i] != rhs[i]) {
			return 0;
		}
	}
	return 1;
}


//
// operator !=
//
template <typename T>
bool Base_Array <T>::operator != (const Base_Array& rhs) const
{
	return !(this == rhs);
}