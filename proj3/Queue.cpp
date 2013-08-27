#include <iostream>
#include <list>
#include "Queue.h"

using namespace std;
using namespace cop4530;

template <typename T>
Queue<T>::Queue() : array( 0 ) {}

template <typename T>
Queue<T>::~Queue()
{
	//delete array;
}

template <typename T>
Queue<T>::Queue( const Queue &rhs )
{
	operator=( rhs );
}

template <typename T> 
Queue<T>& Queue<T>::operator=( const Queue<T> &rhs )
{

	array = rhs.array;

	return *this;
}

template <typename T>
T& Queue<T>::back()
{
	return array.back();	
}

template <typename T>
const T& Queue<T>::back() const 
{
	return array.back();
}

template <typename T>
bool Queue<T>::empty() const 
{
	return array.empty();
}

template <typename T>
T& Queue<T>::front()
{
	return array.front();
}

template <typename T>
const T& Queue<T>::front() const
{
	return array.front();
}

template <typename T>
void Queue<T>::pop()
{
	array.pop_front();
}

template <typename T>
void Queue<T>::push( const T& val )
{
	array.push_back( val );
}

template <typename T>
int Queue<T>::size()
{
  return array.size();
}




