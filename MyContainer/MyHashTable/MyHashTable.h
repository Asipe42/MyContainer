// Copyright Modin, All Rights Reserved.

#pragma once
#include <memory>
#include "../MyList/MyList.h"
#include "../MyVector/MyVector.h"

/*
 * 해시 테이블
 *	- 룩업 테이블의 일종으로, 키를 통해 데이터를 룩업한다. 
 *	- 키를 저장하기 위해 인덱스가 필요하며 키를 인덱스로 변환하는 과정은 해쉬 함수가 처리한다.
 *	- 물리적인 한계로 키는 다르나 인덱스가 같은 현상이 생긴다. 이를 충돌이라고 한다.
 *	- 충돌은 '체이닝(Chaining)' 방식으로 처리한다.
 */

template <typename T1, typename T2>
class MyHashTable
{
public:
	MyHashTable() noexcept;
	MyHashTable(const MyHashTable& rhs);
	MyHashTable(MyHashTable&& rhs) noexcept;
	~MyHashTable() noexcept;

	MyHashTable<T1, T2>& operator=(const MyHashTable& rhs);
	MyHashTable<T1, T2>& operator=(MyHashTable&& rhs);

	bool empty() const;
	size_t size() const;

	T2 find(T1 key) const;
	size_t count() const;

	void emplace(T1 key, T2 value);
	void insert(T1 key, T2 value);
	void erase(T1 key);
	void clear();

private:
	size_t hash_function() const;

	MyVector<MyList<std::tuple<T1, T2>>> m_buckets;
	size_t m_size;
};

template<typename T1, typename T2>
inline MyHashTable<T1, T2>::MyHashTable() noexcept
	: m_buckets(MyVector<MyList<std::tuple<T1, T2>>>())
	, m_size(0)
{
}

template<typename T1, typename T2>
inline MyHashTable<T1, T2>::MyHashTable(const MyHashTable& rhs)
	: m_buckets(rhs.m_buckets)
	, m_size(rhs.m_size)
{
	/*
	 * 복사 생성자
	 *	- 깊은 복사를 수행한다.
	 *	- 깊은 복사란 포인터가 참조하고 있는 메모리에 있는 데이터에 대한 사본을 만드는 것이다.
	 */
}

template<typename T1, typename T2>
inline MyHashTable<T1, T2>::MyHashTable(MyHashTable&& rhs) noexcept
	: m_buckets(std::move(rhs.m_buckets))
	, m_size(rhs.m_size)
{
	/*
	 * 이동 생성자
	 *	- 이동 생성자는 rvalue에 대한 사본을 생성한다.
	 *  - rvalue는 임시 객체를 의미한다.
	 */

	m_size = 0;
}

template<typename T1, typename T2>
inline MyHashTable<T1, T2>::~MyHashTable() noexcept
{
}

template<typename T1, typename T2>
inline MyHashTable<T1, T2>& MyHashTable<T1, T2>::operator=(const MyHashTable& rhs)
{
	/*
	 * 복사 대입	연산자
	 *	- 복사 생성자와 비슷하게 동작한다.
	 *	- 복사 생성자와의 차이점은 이미 메모리가 할당되어 있는 상태에서 동작한다는 것이다.
	 */

	m_buckets = rhs.m_buckets;
	m_size = rhs.m_size;
}

template<typename T1, typename T2>
inline MyHashTable<T1, T2>& MyHashTable<T1, T2>::operator=(MyHashTable&& rhs)
{
	/*
	 * 이동 대입 연산자
	 *	- 이동 생성자와 비슷하게 동작한다.
	 *  - 이동 생성자와의 차이점은 이미 메모리가 할당되어 있는 상태에서 동작한다는 것이다.
	 */

	m_buckets = std::move(rhs.m_buckets);
	m_size = rhs.m_size;

	rhs.m_size = 0;
}

template<typename T1, typename T2>
inline bool MyHashTable<T1, T2>::empty() const
{
	return false;
}

template<typename T1, typename T2>
inline size_t MyHashTable<T1, T2>::size() const
{
	return size_t();
}

template<typename T1, typename T2>
inline T2 MyHashTable<T1, T2>::find(T1 key) const
{
	return T2();
}

template<typename T1, typename T2>
inline size_t MyHashTable<T1, T2>::count() const
{
	return size_t();
}

template<typename T1, typename T2>
inline void MyHashTable<T1, T2>::emplace(T1 key, T2 value)
{
}

template<typename T1, typename T2>
inline void MyHashTable<T1, T2>::insert(T1 key, T2 value)
{
}

template<typename T1, typename T2>
inline void MyHashTable<T1, T2>::erase(T1 key)
{
}

template<typename T1, typename T2>
inline void MyHashTable<T1, T2>::clear()
{
}

template<typename T1, typename T2>
inline size_t MyHashTable<T1, T2>::hash_function() const
{
	return size_t();
}
