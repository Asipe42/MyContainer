// Copyright Modin, All Rights Reserved.

#pragma once
#include "MyList/MyList.h"
#include <memory>

template<typename T>
class MyStack
{
public:
	MyStack();
	MyStack(const MyStack& rhs);
	MyStack(MyStack&& rhs) noexcept;
	~MyStack() noexcept;

	MyStack<T>& operator=(const MyStack& rhs);
	MyStack<T>& operator=(MyStack&& rhs);

	bool empty() const;
	size_t size() const;
	T& top() const;
	void push(const T& value);
	void pop();

private:
	MyList<T> m_list;
	size_t m_size;
};

template<typename T>
inline MyStack<T>::MyStack()
	: m_size(0)
{
	m_list = MyList<T>;
}

template<typename T>
inline MyStack<T>::MyStack(const MyStack& rhs)
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
inline MyStack<T>::MyStack(MyStack&& rhs) noexcept
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
inline MyStack<T>::~MyStack() noexcept
{
	
}

template<typename T>
inline MyStack<T>& MyStack<T>::operator=(const MyStack& rhs)
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
inline MyStack<T>& MyStack<T>::operator=(MyStack&& rhs)
{

}

template<typename T>
inline bool MyStack<T>::empty() const
{
	return false;
}

template<typename T>
inline size_t MyStack<T>::size() const
{
	return size_t();
}

template<typename T>
inline T& MyStack<T>::top() const
{
	// TODO: 여기에 return 문을 삽입합니다.
}

template<typename T>
inline void MyStack<T>::push(const T& value)
{
}

template<typename T>
inline void MyStack<T>::pop()
{
}
