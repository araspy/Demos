// $Id: Array.cpp 827 2011-02-07 14:20:53Z hillj $

// Honor Pledge:
//
// I pledge that I have neither given nor receieved any help
// on this assignment.

#include "Array.h"
#include <stdexcept>         // for std::out_of_bounds exception

//
// Array
//
template <typename T>
Array <T>::Array(void)
	: data_(nullptr),
	cur_size_(0),
	max_size_(0) {}

//
// Array (size_t)
//
template <typename T>
Array <T>::Array(size_t length)
	: data_(new T[length]),
	cur_size_(length),
	max_size_(length) {}

//
// Array (size_t, char)
//
template <typename T>
Array <T>::Array(size_t length, T fill)
	: data_(new T[length]),
	cur_size_(length),
	max_size_(length)
{
	for (int i = 0; i < length; i++) {
		data_[i] = fill;
	}
}

//
// Array (const Array &) copy consturctor
// add -1 to all for loops that deal with arrays for indexing.
template <typename T>
Array <T>::Array(const Array& array)
	:cur_size_(array.size()),
	max_size_(array.max_size())
{
	if (cur_size_ != 0) {
		data_ = new T[cur_size_];
		for (int i = 0; i < cur_size_ - 1; i++) {
			data_[i] = array[i];
		}
	}
	else {
		data_ = NULL;
	}
}

//
// ~Array
//
template <typename T>
Array <T>::~Array(void)
{
	delete[] data_;
}

//
// operator =
//
template <typename T>
const Array <T>& Array <T>::operator = (const Array& rhs)
{
	if (this == rhs) {
		return 0;
	} 
	if (max_size_ <= rhs.size()) {
		cur_size_ = rhs.size();
	}
	else {
		delete[] data_;
		cur_size_ = rhs.size();
		max_size_ = cur_size_;
		if (cur_size_ == 0) {
			data_ = NULL;
		}
		else {
			data_ = new T[cur_size_];
			for (int i = 0; i < cur_size_; i++) {
				data_[i] = rhs[i];
			}
		}
	}
}

//
// resize
//
template <typename T>
void Array <T>::resize(size_t new_size)
{
	char* tempBuffer;


	if (new_size == max_size_) {
		return;
	}
	if (new_size == 0) {
		cur_size_ = 0;
		max_size_ = 0;
		delete[] data_;
		data_ = NULL;
	}
	else {
		tempBuffer = new T[new_size];  //create new buffer of correct size

		if (new_size <= cur_size_) {  //truncate old array to newsize
			for (int i = 0; i < new_size; i++) {
				tempBuffer[i] = data_[i];
			}
		}
		else { //here we know newsize > cursize, copy into bigger buffer
			for (int i = 0; i < cur_size_; i++) {
				tempBuffer[i] = data_[i];
			}
		}
		delete[] data_;
		data_ = tempBuffer;
		cur_size_ = new_size;
		max_size_ = new_size;
	}
}


