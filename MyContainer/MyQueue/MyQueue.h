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
	MyQueue() noexcept;
	MyQueue(const MyQueue& rhs);
	MyQueue(MyQueue&& rhs) noexcept;
	~MyQueue() noexcept;

	MyQueue<T>& operator=(const MyQueue& rhs);
	MyQueue<T>& operator=(MyQueue&& rhs);

	bool empty() const;
	size_t size() const;
	void enqueue(const T& value);
	void dequeue();
	T peek() const;
	void clear();

	
private:
	MyList<T> m_list;
	size_t m_size;
};

template<typename T>
inline MyQueue<T>::MyQueue() noexcept
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
inline MyQueue<T>::MyQueue(MyQueue&& rhs) noexcept
	: m_list(std::move(rhs.m_list))
	, m_size(rhs.m_size)
{
	/*
	 * 이동 생성자
	 *	- 이동 생성자는 rvalue에 대한 사본을 생성한다.
	 *  - rvalue는 임시 객체를 의미한다.
	 */

	rhs.m_size = 0;
}

template<typename T>
inline MyQueue<T>::~MyQueue() noexcept
{
}

template<typename T>
inline MyQueue<T>& MyQueue<T>::operator=(const MyQueue& rhs)
{
	/*
	 * 복사 대입	연산자
	 *	- 복사 생성자와 비슷하게 동작한다.
	 *	- 복사 생성자와의 차이점은 이미 메모리가 할당되어 있는 상태에서 동작한다는 것이다.
	 */

	m_list = rhs.m_list;
	m_size = rhs.m_size;

	return *this;
}

template<typename T>
inline MyQueue<T>& MyQueue<T>::operator=(MyQueue&& rhs)
{
	/*
	 * 이동 대입 연산자
	 *	- 이동 생성자와 비슷하게 동작한다.
	 *  - 이동 생성자와의 차이점은 이미 메모리가 할당되어 있는 상태에서 동작한다는 것이다.
	 */

	m_list = std::move(rhs.m_list);
	m_size = rhs.m_size;

	rhs.m_size = 0;

	return *this;
}

template<typename T>
inline bool MyQueue<T>::empty() const
{
	return m_size == 0;
}

template<typename T>
inline size_t MyQueue<T>::size() const
{
	return m_size;
}

template<typename T>
inline void MyQueue<T>::enqueue(const T& value)
{
	m_list.push_front(value);
	m_size = m_list.size();
}

template<typename T>
inline void MyQueue<T>::dequeue()
{
	if (empty())
	{
		return;
	}

	m_list.pop_back();
	m_size = m_list.size();
}

template<typename T>
inline T MyQueue<T>::peek() const
{
	return m_list.back();
}

template <typename T>
void MyQueue<T>::clear()
{
	m_list.clear();
	m_size = 0;
}
