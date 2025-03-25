// Copyright Modin, All Rights Reserved.

#pragma once
#include <memory>
#include <stdexcept>

/*
 * 동적 배열
 *	- 배열은 선언과 동시에 크기가 제한된다.
 *	- 그러나 동적 배열은 수용량을 초과할 때, 그 이상을 담을 수 있는 배열을 새로 만들어 기존 배열을 복사한다.
 */

template <typename T>
class MyVector
{
public:
	MyVector(size_t capacity = 16) noexcept;
	MyVector(const MyVector& rhs);
	MyVector(MyVector&& rhs) noexcept;
	~MyVector() noexcept;
	
	MyVector& operator=(const MyVector& rhs);
	MyVector& operator=(MyVector&& rhs);
	T& operator[](size_t index) const;

	T* begin() const noexcept;
	T* end() const noexcept;

	T& front() const noexcept;
	T& back() const noexcept;

	size_t size() const noexcept;
	size_t capacity() const noexcept;
	bool empty() const noexcept;
	void reserve(size_t capacity);

	void push_back(const T& value);
	void pop_back() noexcept;
	void clear() noexcept;

private:
	size_t m_size;
	size_t m_capacity;
	T* m_arr;
};

template<typename T>
inline MyVector<T>::MyVector(size_t capacity) noexcept
	: m_size(0)
	, m_capacity(capacity)
	, m_arr(new T[capacity])
{
	if (capacity == 0)
	{
		m_capacity = 1;
	}

	m_capacity = capacity;
}

template<typename T>
inline MyVector<T>::MyVector(const MyVector& rhs)
	: m_size(rhs.m_size)
	, m_capacity(rhs.m_capacity)
	, m_arr(new T[rhs.m_capacity])
{
	/*
	 * 복사 생성자
	 *	- 깊은 복사를 수행한다.
	 *	- 깊은 복사란 포인터가 참조하고 있는 메모리에 있는 데이터에 대한 사본을 만드는 것이다.
	 */

	for (size_t i = 0; i < m_size; i++)
	{
		m_arr[i] = rhs.m_arr[i];
	}
}

template<typename T>
inline MyVector<T>::MyVector(MyVector&& rhs) noexcept
	: m_size(rhs.m_size)
	, m_capacity(rhs.m_capacity)
	, m_arr(rhs.m_arr)
{
	/*
	 * 이동 생성자
	 *	- 이동 생성자는 rvalue에 대한 사본을 생성한다.
	 *  - rvalue는 임시 객체를 의미한다.
	 */

	rhs.m_size = 0;
	rhs.m_capacity = 0;
	rhs.m_arr = nullptr;
}

template<typename T>
inline MyVector<T>::~MyVector() noexcept
{
	delete[] m_arr;
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(const MyVector& rhs)
{
	/*
	 * 복사 대입	연산자
	 *	- 복사 생성자와 비슷하게 동작한다.
	 *	- 복사 생성자와의 차이점은 이미 메모리가 할당되어 있는 상태에서 동작한다는 것이다.
	 */

	if (this == &rhs)
	{
		return *this;
	}

	if (m_capacity < rhs.m_capacity)
	{
		delete[] m_arr;
		m_arr = new T[rhs.m_capacity];
		m_capacity = rhs.m_capacity;
	}

	memcpy(m_arr, rhs.m_arr, sizeof(T) * rhs.m_size);
	m_size = rhs.m_size;

	return *this;
}

template<typename T>
inline MyVector<T>& MyVector<T>::operator=(MyVector&& rhs)
{
	/*
	 * 이동 대입 연산자
	 *	- 이동 생성자와 비슷하게 동작한다.
	 *  - 이동 생성자와의 차이점은 이미 메모리가 할당되어 있는 상태에서 동작한다는 것이다.
	 */

	if (this == &rhs)
	{
		return *this;
	}

	delete[] m_arr;

	m_arr = rhs.m_arr;
	m_capacity = rhs.m_capacity;
	m_size = rhs.m_size;

	rhs.m_size = 0;
	rhs.m_capacity = 0;
	rhs.m_arr = nullptr;

	return *this;
}

template<typename T>
inline T& MyVector<T>::operator[](size_t index) const
{
	if (m_size <= index)
	{
		throw std::out_of_range("Index out of range");
	}
	
	return m_arr[index];
}

template<typename T>
inline T* MyVector<T>::begin() const noexcept
{
	return m_arr;
}

template<typename T>
inline T* MyVector<T>::end() const noexcept
{
	return m_arr + m_size;
}

template<typename T>
inline T& MyVector<T>::front() const noexcept
{
	return m_arr[0];
}

template<typename T>
inline T& MyVector<T>::back() const noexcept
{
	return m_arr[m_size - 1];
}

template<typename T>
inline size_t MyVector<T>::size() const noexcept
{
	return m_size;
}

template<typename T>
inline size_t MyVector<T>::capacity() const noexcept
{
	return m_capacity;
}

template<typename T>
inline bool MyVector<T>::empty() const noexcept
{
	return m_size == 0;
}

template<typename T>
inline void MyVector<T>::reserve(size_t capacity)
{
	if (capacity <= m_capacity)
	{
		return;
	}

	T* tempArr = new T[capacity];
	memcpy(tempArr, m_arr, sizeof(T) * m_size);
	delete[] m_arr;
	m_arr = tempArr;

	m_capacity = capacity;
}

template<typename T>
inline void MyVector<T>::push_back(const T& value)
{
	/*
	 * 설명
	 *	- 배열 마지막에 원소를 추가한다.
	 *  - 수용량을 초과하면 더 큰 배열을 만들어 기존 배열을 복사한다.
	 */

	if (m_size >= m_capacity)
	{
		if (m_capacity == 0)
		{
			m_capacity = 1;
		}

		reserve(m_capacity * 2);
	}

	int index = m_size;
	m_arr[index] = value;
}

template<typename T>
inline void MyVector<T>::pop_back() noexcept
{
	if (m_size > 0)
	{
		m_size--;
	}
}

template<typename T>
inline void MyVector<T>::clear() noexcept
{
	m_size = 0;
}
