#pragma once
#include <memory>

template <typename T>
class MyList
{
public:
	struct Node;
	class iterator
	{
	public:
		iterator()
			: m_iter(new Node)
		{
		}

		iterator(Node* node)
			: m_iter(node)
		{
		}

		Node* operator&()
		{
			return m_iter;
		}

	private:
		Node* m_iter;
	};

public:
	MyList() noexcept;
	MyList(const MyList& rhs);
	MyList(MyList&& rhs) noexcept;
	~MyList() noexcept;

	MyList<T>& operator=(const MyList& rhs);
	MyList<T>& operator=(MyList&& rhs);
	T& operator[](size_t index) const;

	bool empty() const;
	size_t size() const;

	iterator begin() const;
	iterator end() const;
	T front() const;
	T back() const;

	void push_front(const T& value);
	void push_back(const T& value);
	void pop_front();
	void pop_back();
	
	void insert(iterator iter, const T& value);
	void erase(iterator iter);

private:
	struct Node
	{
		Node* m_prev;
		Node* m_next;
		T m_data;
	};

	Node* m_head;
	Node* m_tail;
	size_t m_size;
};

template<typename T>
inline MyList<T>::MyList() noexcept
	: m_head(new Node)
	, m_tail(new Node)
	, m_size(0)
{
	m_head->m_prev = nullptr;
	m_head->m_next = m_tail;

	m_tail->m_prev = m_head;
	m_tail->m_next = nullptr;
}

template<typename T>
inline MyList<T>::MyList(const MyList& rhs)
	: m_size(rhs.m_size)
{
	/*
	 * 복사 생성자
	 *	- 깊은 복사를 수행한다.
	 *	- 깊은 복사란 포인터가 참조하고 있는 메모리에 있는 데이터에 대한 사본을 만드는 것이다.
	 */

	if (m_size == 0)
	{
		MyList();
		return;
	}

	Node* nowNode = rhs.m_head;
	for (int i = 0; i < m_size; i++)
	{
		Node* newNode = new Node;
		newNode->m_data = nowNode->m_data;
		newNode->m_prev = nowNode->m_prev;
		newNode->m_next = nowNode->m_next;

		if (i == 0)
		{
			m_head = nowNode;
		}

		if (i == m_size - 1)
		{
			m_tail = nowNode;
		}

		nowNode = nowNode->m_next;
	}
}

template<typename T>
inline MyList<T>::MyList(MyList&& rhs) noexcept
{
	/*
	* 이동 생성자
	*	- 이동 생성자는 rvalue에 대한 사본을 생성한다.
	*  - rvalue는 임시 객체를 의미한다.
	*/

	m_head = rhs.m_head;
	m_tail = rhs.m_tail;
	m_size = rhs.m_size;

	rhs.m_head = nullptr;
	rhs.m_tail = nullptr;
	rhs.m_size = 0;
}

template<typename T>
inline MyList<T>::~MyList() noexcept
{
	Node* nowNode = m_head;
	for (int i = 0; i < m_size; i++)
	{
		Node* nextNode = nowNode->m_next;
		delete nowNode;
		nowNode = nextNode;
	}
}

template<typename T>
inline MyList<T>& MyList<T>::operator=(const MyList& rhs)
{
	// TODO: 여기에 return 문을 삽입합니다.
}

template<typename T>
inline MyList<T>& MyList<T>::operator=(MyList&& rhs)
{
	// TODO: 여기에 return 문을 삽입합니다.
}

template<typename T>
inline T& MyList<T>::operator[](size_t index) const
{
	// TODO: 여기에 return 문을 삽입합니다.
}

template<typename T>
inline bool MyList<T>::empty() const
{
	return false;
}

template<typename T>
inline size_t MyList<T>::size() const
{
	return size_t();
}

template<typename T>
inline typename MyList<T>::iterator MyList<T>::begin() const
{
	return iterator();
}

template<typename T>
inline typename MyList<T>::iterator MyList<T>::end() const
{
	return iterator();
}

template<typename T>
inline T MyList<T>::front() const
{
	return T();
}

template<typename T>
inline T MyList<T>::back() const
{
	return T();
}

template<typename T>
inline void MyList<T>::push_front(const T& value)
{
}

template<typename T>
inline void MyList<T>::push_back(const T& value)
{
}

template<typename T>
inline void MyList<T>::pop_front()
{
}

template<typename T>
inline void MyList<T>::pop_back()
{
}

template<typename T>
inline void MyList<T>::insert(iterator iter, const T& value)
{
}

template<typename T>
inline void MyList<T>::erase(iterator iter)
{
}
