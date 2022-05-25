#include "Queue.h"
#include <stdexcept>


//
// Queue
//
template <typename T>
Queue <T>::Queue(void)
{
	head_ = nullptr;
	tail_ = nullptr;
	size_ = 0;  //not sure how size should be handled considering some kind of inheritance is definitely needed here.
}

//
// ~Queue
// destructor
template <typename T>
Queue <T>::~Queue(void)
{
	clear();
}

//
// Enqueue
//
template <typename T>
void Queue<T>::enqueue(T element, int priority)
{
	Node* temp = new Node;
	temp->element_ = element;
	temp->priority_ = priority;
	temp->next_ = NULL;


	//list may be empty
	if (head_ == NULL) {
		head_ = temp;
		tail_ = temp;
	}
	else //list not empty
	{
		Node* current; //iterator
		current = head_;

		if (priority > current->priority) //new item goes at beginning
		{
			//add to head of the list
			temp->next_ = head_; // new head points to the old head
			head_ = temp;
		}
		else {
			while (current->next_ != NULL) {  //while not at end of list
				if (temp->priority > current->next_->priority) {  //and priority is > next item priority
					temp->next_ = current->next_;
					current->next_ = temp;
					break;
				}
				current = current->next_;
			}//end while
			if (current->next_ == NULL)
			{
				current->next_ = temp;
				tail_ = temp;
			}
		}
	}
	size_++;
}

//
// Dequeue
//
template <typename T>
void Queue<T>::dequeue(void)
{
	if (is_empty()) {
		throw std::underflow_error("Queue is empty. There is nothing to dequeue.");
	}
	int element = head_->element_;  //need to save the element before we get rid of the top
	Node* tempNode = head_;  //save a pointer to the node we are about to dequeue so we can delete it after advancing head
	head_ = head_->next; //advance head to point to next node
	delete tempNode; //delete the old head
	size--; //decrement bc we are dequeueing, removing
	return element;
}

//
// Clear
//
template <typename T>
void Queue<T>::clear(void)
{
	while (!is_empty()) {      //while it's not empty, we are going to go through and get rid of the nodes
		Node* tempNode = head_;  //temp node points to head
		head_ = head_->next_; //advance top
		delete tempNode; //free memory
	}
	tail_ = NULL; //if we have emptied out the list we need to make sure tail also points to NULL
	size_ = 0;
}