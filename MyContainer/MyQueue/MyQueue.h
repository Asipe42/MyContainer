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
	: m_list(MyList<T>())
	, m_size(0)
{

}

template<typename T>
inline MyQueue<T>::MyQueue(const MyQueue& rhs)
	: m_list(rhs.m_list)
	, m_size(rhs.m_size)
{
	/*
	 * 복사 생성자
	 *	- 깊은 복사를 수행한다.
	 *	- 깊은 복사란 포인터가 참조하고 있는 메모리에 있는 데이터에 대한 사본을 만드는 것이다.
	 */
}

template<typename T>
inline MyQueue<T>::MyQueue(MyQueue&& rhs)
	: m_list(std::move(rhs.m_list))
	, m_size(rhs.m_size)
{
	/*
	 * 이동 생성자
	 *	- 이동 생성자는 rvalue에 대한 사본을 생성한다.
	 *  - rvalue는 임시 객체를 의미한다.
	 */

	rhs.m_list = nullptr;
	rhs.m_size = 0;
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
