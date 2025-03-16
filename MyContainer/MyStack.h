// Copyright Modin, All Rights Reserved.

#pragma once
#include "MyList.h"
#include <memory>

template<typename T>
class MyStack
{
public:
	MyStack();
	MyStack(const MyStack& rhs);
	MyStack(MyStack&& rhs);
	~MyStack();

	MyStack<T>& operator=(const MyStack& rhs);
	MyStack<T>& operator=(MyStack&& rhs);

	bool empty();
	size_t size();
	T& top();
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
{
}

template<typename T>
inline MyStack<T>::MyStack(MyStack&& rhs)
{
}

template<typename T>
inline MyStack<T>::~MyStack()
{
}

template<typename T>
inline MyStack<T>& MyStack<T>::operator=(const MyStack& rhs)
{
	// TODO: 여기에 return 문을 삽입합니다.
}

template<typename T>
inline MyStack<T>& MyStack<T>::operator=(MyStack&& rhs)
{
	// TODO: 여기에 return 문을 삽입합니다.
}

template<typename T>
inline bool MyStack<T>::empty()
{
	return false;
}

template<typename T>
inline size_t MyStack<T>::size()
{
	return size_t();
}

template<typename T>
inline T& MyStack<T>::top()
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
