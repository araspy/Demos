#include <stdexcept>
//
// size
// size_ should hold the size of the queue.
template <typename T>
inline
size_t Queue <T>::size(void) const
{
	return size_;
}

//
// clear
// there shouldn't be a value held in the head pointer if the queue is empty.
template <typename T>
bool Queue <T>::is_empty(void) const
{
	return (head_ == NULL);
}