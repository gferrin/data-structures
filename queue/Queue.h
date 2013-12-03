#ifndef COP4530_QUEUE_H
#define COP4530_QUEUE_H

#include <iostream>
#include <stdexcept>
#include <list>

namespace cop4530 {

template <typename T>
class Queue {
public:
	
	Queue(); // zero parameter constructor. Create an empty queue.
	~Queue(); // destructor. De-allocate memory if necessary.
	Queue(const Queue &rhs); // copy constructor. Create the new queue with the elements of an existing queue rhs.
	Queue& operator=(const Queue &rhs); // copy assignment operator.
	T& back(); // return a reference to the last element in the queue.
	const T& back() const; // constant version of the above member function.
	bool empty() const; // return true if there is no element in the queue; return false otherwise.
	T& front(); // return a reference to the first element in the queue.
	const T& front() const; // constant version of the above member function.
	void pop(); // remove the first element in the queue and discard it.
	void push(const T& val); // add a new element val into the end of the current queue.
	int size(); // return the number of elements in the current queue.

private:

	std::list<T> array;

};

#include "Queue.cpp"

} // end of namespace COP4530
#endif