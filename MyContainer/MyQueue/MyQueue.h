// Copyright Modin, All Rights Reserved.

#pragma once
#include "../MyList/MyList.h"
#include <memory>

/*
 * 큐
 *	- 먼저 들어온 데이터가 먼저 나가는 선입선출 구조이다.
 */

template <typename T>
class MyQueue
{
public:
	MyQueue();
	MyQueue(const MyQueue& rhs);
	MyQueue(MyQueue&& rhs);
	~MyQueue();

	MyQueue<T>& operator=(const MyQueue& rhs);
	MyQueue<T>& operator=(MyQueue&& rhs);

	bool empty();
	size_t size();
	void enqueue(const T& value);
	void dequeue();
	T peek();

private:
	MyList<T> m_list;
	size_t m_size;
};

template<typename T>
inline MyQueue<T>::MyQueue()
{
}

template<typename T>
inline MyQueue<T>::MyQueue(const MyQueue& rhs)
{
}

template<typename T>
inline MyQueue<T>::MyQueue(MyQueue&& rhs)
{
}

template<typename T>
inline MyQueue<T>::~MyQueue()
{
}

template<typename T>
inline MyQueue<T>& MyQueue<T>::operator=(const MyQueue& rhs)
{
	// TODO: 여기에 return 문을 삽입합니다.
}

template<typename T>
inline MyQueue<T>& MyQueue<T>::operator=(MyQueue&& rhs)
{
	// TODO: 여기에 return 문을 삽입합니다.
}

template<typename T>
inline bool MyQueue<T>::empty()
{
	return false;
}

template<typename T>
inline size_t MyQueue<T>::size()
{
	return size_t();
}

template<typename T>
inline void MyQueue<T>::enqueue(const T& value)
{
}

template<typename T>
inline void MyQueue<T>::dequeue()
{
}

template<typename T>
inline T MyQueue<T>::peek()
{
	return T();
}
