// $Id: Stack.cpp 827 2011-02-07 14:20:53Z hillj $

// Honor Pledge:
//
// I pledge that I have neither given nor received any help
// on this assignment.

#include "Stack.h"
#include <stdexcept>

//
// Stack
// default constructor
template <typename T>
Stack <T>::Stack(void)
	: top_(-1),
	stackptr_(nullptr){}

//
// Stack
// copy constructor
template <typename T>
Stack <T>::Stack(const Stack& stack)
{
	if (top_ != 0) {
		stackptr_ = new T[top_];
		for (int i = 0; i < top_ - 1; i++) {
			top_[i] = T[i];
		}
	}
	else {
		stackptr_ = NULL;
	}
}

//
// ~Stack
// destructor
template <typename T>
Stack <T>::~Stack(void)
{
	clear();
}

//
// push
// simply add an element. There needs to be some handling for max. This boils down to 
// my lack of understanding of poly/aggregate and whether I need a max value that's
// local to Stack or if I just need to be concerned with the Array max_size_.
// Best guess, I'd use poly to make the max_size_ getter something I can call/handle here.
template <typename T>
void Stack <T>::push(T element)
{
	stackptr_[top_++] = element; //before this, ask if top == max; 
}

//
// pop
// checking to make sure the stack is empty. I'm sure there's a better way to do this exeption handling.
// specifically because of the stuff Dr.Hill has in the header file. I'm sure there's more to this.
template <typename T>
void Stack <T>::pop(void)
{
	if (is_empty) {
		throw std::underflow_error("Stack is empty. No elements remaining, nothing to pop.");
	}
	top_--;
	return stackptr_[top_];
}

//
// operator =
//
template <typename T>
const Stack <T>& Stack <T>::operator = (const Stack& rhs)
{
	if (this == rhs) {
		return 0;
	}
	else {
		clear();
		top_ = rhs.size();
		if (top_ == 0) {
			stackptr_ = NULL;
		}
		else {
			stackptr_ = new T[top_];
			for (int i = 0; i < top_ - 1; i++) {
				stackptr_[i] = rhs[i];
			}
		}
	}
}

//
// clear
// does setting top = 0 clear the stack? or does this leave memory floating around?
// or if I am using inheritance, couldn't I set top_ = 0 and THEN ALSO call the 
// Array deconstructor? (or it would be auto-called when it went out of scope)
template <typename T>
void Stack <T>::clear(void)
{
	top_ = 0;
}