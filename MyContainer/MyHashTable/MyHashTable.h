// Copyright Modin, All Rights Reserved.

#pragma once
#include <memory>
#include <tuple>
#include "../MyList/MyList.h"
#include "../MyVector/MyVector.h"

/*
 * 해시 테이블
 *	- 룩업 테이블의 일종으로, 키를 통해 데이터를 룩업한다. 
 *	- 키를 저장하기 위해 인덱스가 필요하며 키를 인덱스로 변환하는 과정은 해쉬 함수가 처리한다.
 *	- 물리적인 한계로 키는 다르나 인덱스가 같은 현상이 생긴다. 이를 충돌이라고 한다.
 *	- 충돌은 '체이닝(Chaining)' 방식으로 처리한다.
 */



template <typename key_type, typename value_type>
class MyHashTable
{
public:
	static const size_t capacity = 10;
	
	MyHashTable() noexcept;
	MyHashTable(const MyHashTable& rhs);
	MyHashTable(MyHashTable&& rhs) noexcept;
	~MyHashTable() noexcept;

	MyHashTable<key_type, value_type>& operator=(const MyHashTable& rhs);
	MyHashTable<key_type, value_type>& operator=(MyHashTable&& rhs);

	bool empty() const;
	size_t size() const;

	value_type find(key_type key) const;
	size_t count(key_type key) const;

	void insert(key_type key, value_type value);
	void erase(key_type key);
	void clear();

private:
	size_t hash_function(key_type Key) const;
	MyList<std::tuple<key_type, value_type>> m_buckets[capacity];
	size_t m_size;
};

template<typename key_type, typename value_type>
inline MyHashTable<key_type, value_type>::MyHashTable() noexcept
	: m_size(0)
{
	for (int i = 0; i < capacity; i++)
	{
		m_buckets[i] = MyList<std::tuple<key_type, value_type>>();
	}
}

template<typename key_type, typename value_type>
inline MyHashTable<key_type, value_type>::MyHashTable(const MyHashTable& rhs)
	: m_size(rhs.m_size)
{
	/*
	 * 복사 생성자
	 *	- 깊은 복사를 수행한다.
	 *	- 깊은 복사란 포인터가 참조하고 있는 메모리에 있는 데이터에 대한 사본을 만드는 것이다.
	 */

	for (size_t i = 0; i < capacity; ++i)
	{
		m_buckets[i] = rhs.m_buckets[i];
	}
}

template<typename key_type, typename value_type>
inline MyHashTable<key_type, value_type>::MyHashTable(MyHashTable&& rhs) noexcept
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

template<typename key_type, typename value_type>
inline MyHashTable<key_type, value_type>::~MyHashTable() noexcept
{
}

template<typename key_type, typename value_type>
inline MyHashTable<key_type, value_type>& MyHashTable<key_type, value_type>::operator=(const MyHashTable& rhs)
{
	/*
	 * 복사 대입	연산자
	 *	- 복사 생성자와 비슷하게 동작한다.
	 *	- 복사 생성자와의 차이점은 이미 메모리가 할당되어 있는 상태에서 동작한다는 것이다.
	 */

	m_buckets = rhs.m_buckets;
	m_size = rhs.m_size;
}

template<typename key_type, typename value_type>
inline MyHashTable<key_type, value_type>& MyHashTable<key_type, value_type>::operator=(MyHashTable&& rhs)
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

template<typename key_type, typename value_type>
inline bool MyHashTable<key_type, value_type>::empty() const
{
	return m_size == 0;
}

template<typename key_type, typename value_type>
inline size_t MyHashTable<key_type, value_type>::size() const
{
	return m_size;
}

template<typename key_type, typename value_type>
inline value_type MyHashTable<key_type, value_type>::find(key_type key) const
{
	size_t index = hash_function(key);

	if (capacity <= index)
	{
		return value_type();
	}

	/*
	 * 시나리오
	 *	A. 리스트가 비어있는 경우
	 *		- 기본 값 반환
	 *	B. A가 아니면서 탐색에 성공한 경우
	 *	C. A가 아니면서 탐색에 실패한 경우
	 */

	if (m_buckets[index].empty())
	{
		// Case A
		return value_type();
	}
	
	typename MyList<std::tuple<key_type, value_type>>::iterator it = m_buckets[index].begin();
	while (it != m_buckets[index].end())
	{
		std::tuple<key_type, value_type> data = *it;
		if (std::get<0>(data) == key)
		{
			// Case B
			return std::get<1>(data);
		}
		it++;
	}

	// Case C
	return value_type();
}

template<typename key_type, typename value_type>
inline size_t MyHashTable<key_type, value_type>::count(key_type key) const
{
	size_t index = hash_function(key);

	if (capacity <= index)
	{
		return size_t();
	}

	return m_buckets[index].size();
}

template<typename key_type, typename value_type>
inline void MyHashTable<key_type, value_type>::insert(key_type key, value_type value)
{
	size_t index = hash_function(key);

	if (capacity <= index)
	{
		throw std::out_of_range("Index out of range");
	}

	/*
	 * 시나리오
	 *	A. 리스트가 비어있는 경우
	 *		- 노드 추가
	 *	B. A가 아니면서 이미 동일한 키 값이 존재하는 경우
	 *		- 노드를 찾아서 값을 갱신
	 *	C. A가 아니면서 키가 존재하지 않는 경우
	 *		- 노드 추가
	 */
	
	if (m_buckets[index].empty() == false)
	{
		typename MyList<std::tuple<key_type, value_type>>::iterator it = m_buckets[index].begin();
		while (it != m_buckets[index].end())
		{
			if (std::get<0>(*it) == key)
			{
				// Case B
				*it = std::make_tuple(key, value);
				return;
			}
			it++;
		}
	}
	
	// Case A, C
	m_buckets[index].push_back(std::make_tuple(key, value));
	m_size++;
}

template<typename key_type, typename value_type>
inline void MyHashTable<key_type, value_type>::erase(key_type key)
{
}

template<typename key_type, typename value_type>
inline void MyHashTable<key_type, value_type>::clear()
{
}

template<typename key_type, typename value_type>
inline size_t MyHashTable<key_type, value_type>::hash_function(key_type Key) const
{
	return size_t();
}
