#pragma once
#include <memory>

/*
 * 동적 배열
 * - 배열은 선언과 동시에 크기가 제한된다.
 * - 그러나 동적 배열은 수용량을 초과할 때, 그 이상을 담을 수 있는 배열을 새로 만들어 기존 배열을 복사한다.
 */

template <typename T>
class MyVector
{
public:
	MyVector(size_t capacity = 16);
	MyVector(const MyVector& rhs);
	MyVector(MyVector&& rhs);
	~MyVector();

	T* begin();
	T* end();

	T& front();
	T& back();

	size_t size();
	size_t capacity();
	bool empty();
	void reserve(size_t capacity);

	void push_back(const T& value);
	void pop_back();
	void clear();

private:
	size_t m_size;
	size_t m_capacity;
	T* m_arr;
};

template<typename T>
inline MyVector<T>::MyVector(size_t capacity)
{
}

template<typename T>
inline MyVector<T>::MyVector(const MyVector& rhs)
{
}

template<typename T>
inline MyVector<T>::MyVector(MyVector&& rhs)
{
}

template<typename T>
inline MyVector<T>::~MyVector()
{
}

template<typename T>
inline T* MyVector<T>::begin()
{
	return nullptr;
}

template<typename T>
inline T* MyVector<T>::end()
{
	return nullptr;
}

template<typename T>
inline T& MyVector<T>::front()
{
	// TODO: 여기에 return 문을 삽입합니다.
}

template<typename T>
inline T& MyVector<T>::back()
{
	// TODO: 여기에 return 문을 삽입합니다.
}

template<typename T>
inline size_t MyVector<T>::size()
{
	return size_t();
}

template<typename T>
inline size_t MyVector<T>::capacity()
{
	return size_t();
}

template<typename T>
inline bool MyVector<T>::empty()
{
	return false;
}

template<typename T>
inline void MyVector<T>::reserve(size_t capacity)
{
}

template<typename T>
inline void MyVector<T>::push_back(const T& value)
{
}

template<typename T>
inline void MyVector<T>::pop_back()
{
}

template<typename T>
inline void MyVector<T>::clear()
{
}
