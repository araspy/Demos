

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <exception>
#include "Array.h"

/**
 * @class Queue
 *
 * Basic queue for abitrary elements.
 */

template <typename T>
class Queue : public Array <T>
{
private:

    struct Node {
        T element_;
        int priority_;
        Node* next_;
    };
    Node* head_;
    Node* tail_;
    // int max_;  again, just not sure how to handle the max situation. this seems like the part where inheritance from Array comes in.
    // I've tried refactoring this entire assignment twice, aggregation and virtual/poly. I need to stop by office hours and get some 
    //clarification so I can meet the inheritance requirements by second submission.
    int size_;



public:
    //Type definition of the type.
    typedef T type;


    /// Default constructor.
    Queue(void);


    /// Destructor.
    ~Queue(void);



    /**
    * Number of elements in the queue.
    *
    * @return         Size of the stack.
    */
    size_t size(void) const;


    /**
    * Test if the queue is empty
    *
    * @retval         true          The queue is empty
    * @retval         false         The queue is not empty
    */
    bool is_empty(void) const;


    /**
     * Enqueue a new element into the queue.
     *
     * @param[in]      payload       Element to add to the queue
     * @param[in]      priority      Position of element
    */
    void Queue<T>::enqueue(T element, int priority);


    /**
     * Dequeue tail element from the queue.
     *
     * @return         Reference to self
    */
    void Queue<T>::dequeue(void);





    /**
     * Queue is structured similar to a linked list. Remove all elements with this method to release memory.
    */
    void Queue<T>::clear(void);





};















#include "Queue.inl"
#endif  // !defined _QUEUE_H_