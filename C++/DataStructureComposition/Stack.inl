// -*- C++ -*-
// $Id: Stack.inl 827 2011-02-07 14:20:53Z hillj $

// Honor Pledge:
//
// I pledge that I have neither given nor received any help on
// this assignment.

#include <stdexcept>

//
// size
// the value held in top_ +1 should be == the size of the stack, I think.
template <typename T>
inline
size_t Stack <T>::size(void) const
{
	return (top_ + 1);
}

//
// top
// simply check if the stack is empty for underflow error,
template <typename T>
inline
T Stack <T>::top(void) const
{
	if (top_ == 0) {  // could I just call is_empty in this if statement? pretty sure I can
		throw std::underflow_error("Stack is empty. Cannot return top element.");
	}
	return stackptr_[top_ - 1];
}

//
// is_empty
// if top_ == 0 then the stack is empty. 
template <typename T>
inline
bool Stack <T>::is_empty(void) const
{
	return top_ == 0;
}
