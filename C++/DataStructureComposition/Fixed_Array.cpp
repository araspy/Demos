// $Id: Fixed_Array.cpp 827 2011-02-07 14:20:53Z hillj $

// Honor Pledge:
//
// I pledge that I have neither given nor received any help
// on this assignment.

#include "Fixed_Array.h"

//
// Fixed_Array
//
//default constructor from Array should automatically be called, no?
template <typename T, size_t N>
Fixed_Array <T, N>::Fixed_Array(void)
{
	data_ = nullptr;
	cur_size_ = 0;
}

//
// Fixed_Array
// copy constructor, if not equal, copy what you have then leave the rest\
//HANDLING: it will automaticall call line 43 if size or type is different.
template <typename T, size_t N>
Fixed_Array <T, N>::Fixed_Array(const Fixed_Array <T, N>& arr)
{
	cur_size_ = arr.size();
	if (cur_size_ != 0) {
		data_ = new T[cur_size_];
		for (int i = 0; i < cur_size_; i++) {
			data_[i] = arr[i];
		}
	}
	else {
		data_ = NULL;
	}

}

//
// Fixed_Array
//initializing constructor - source array can be any size as long as same type
//fixed array of size N, handle the cases where N > M, N >= M, etc. 
template <typename T, size_t N>
template <size_t M>
Fixed_Array <T, N>::Fixed_Array(const Fixed_Array <T, M>& arr)
{
	cur_size_ = N;
	int minLength;
	// could this be done with .min()? check documentation on size_t. which is more efficient?
	if (M >= N) {
		minLength = N;
	}
	else {
		minLength = M;
	}

	if (cur_size_ != 0) {
		data_ = new T[cur_size_];
		for (int i = 0; i < (minLength - 1); i++) {
			data_[i] = arr[i];
		}
	}
	else {
		data_ = NULL;
	}
}

//
// Fixed_Array
// initializing constructor - fills contents with specified value
template <typename T, size_t N>
Fixed_Array <T, N>::Fixed_Array(T fill)
{
	cur_size_ = N;
	data_ = new T[];
	for (int i = 0; i < cur_size_; i++) {
		data_[i] = fill;
	}
}

//
// ~Fixed_Array
// destructor, look at []. possibly just 'delete'. does the parent destructor get called anyway? that would mean Array destructor gets called as well.
template <typename T, size_t N>
Fixed_Array <T, N>::~Fixed_Array(void)
{
	delete[] data_;
}

//
// operator =
// assignment operator N 
//NOTE : copying one to the other, overloading assignment not compare
// delete yourself, then replace with rhs
// are we assigning values or pointers? 
template <typename T, size_t N>
const Fixed_Array <T, N>& Fixed_Array <T, N>::operator = (const Fixed_Array <T, N>& rhs)
{
	if (cur_size_ != 0) {
		for (int i = 0; i < (cur_size_ - 1); i++) {
			data_[i] = rhs[i];
		}
	}
	else {
		data_ = NULL;
	}
}

//
// operator =
// assignment operator M
// NOTE: assigning one array to the other, but they are not of equal size
// sets the object that calls it = to M.
template <typename T, size_t N>
template <size_t M> //must indicate the second array, 
const Fixed_Array <T, N>& Fixed_Array <T, N>::operator = (const Fixed_Array <T, M>& rhs)
{
	int minLength;

	if (M >= N) {
		minLength = N;
	}
	else {
		minLength = M;
	}

	if (cur_size_ != 0) {
		for (int i = 0; i < (minLength - 1); i++) {
			data_[i] = rhs[i];
		}
	}
	else {
		data_ = NULL;
	}
}