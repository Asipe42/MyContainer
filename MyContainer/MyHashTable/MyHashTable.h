// Copyright Modin, All Rights Reserved.

#pragma once
#include <memory>
#include "../MyList/MyList.h"

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

	MyList<std::tuple<T1, T2>>[] m_buckets;
	size_t m_size;
};

template<typename T1, typename T2>
inline MyHashTable<T1, T2>::MyHashTable() noexcept
{
}

template<typename T1, typename T2>
inline MyHashTable<T1, T2>::MyHashTable(const MyHashTable& rhs)
{
}

template<typename T1, typename T2>
inline MyHashTable<T1, T2>::MyHashTable(MyHashTable&& rhs) noexcept
{
}

template<typename T1, typename T2>
inline MyHashTable<T1, T2>::~MyHashTable() noexcept
{
}

template<typename T1, typename T2>
inline MyHashTable<T1, T2>& MyHashTable<T1, T2>::operator=(const MyHashTable& rhs)
{
	// TODO: 여기에 return 문을 삽입합니다.
}

template<typename T1, typename T2>
inline MyHashTable<T1, T2>& MyHashTable<T1, T2>::operator=(MyHashTable&& rhs)
{
	// TODO: 여기에 return 문을 삽입합니다.
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
