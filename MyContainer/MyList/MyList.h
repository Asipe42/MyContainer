// Copyright Modin, All Rights Reserved.

#pragma once
#include <tuple>

/*
 * 연결 리스트
 *	- 동적 배열은 메모리가 물리적으로 연속된 형태를 가지지만, 연결 리스트는 논리적으로 연속된 형태를 갖는다.
 *	- 데이터를 관리하기 위해 각각을 [노드]라는 구조체로 만들어 연결한다.
 *	- 필요할 때마다 메모리를 할당하고, 필요 없을 때는 메모리를 해제한다.
 */

template <typename T>
class MyList
{
public:
	struct Node;
    class iterator
    {
		/*
		 * iterator
		 *	- 특정한 노드를 가리키는 포인터이다.
		 */

    public:
		iterator()
			: m_iter(new Node)
		{
		}

		iterator(Node* node)
			: m_iter(node)
		{
		}

		T& operator*()
		{
			return m_iter->m_data;
		}

		Node* operator&()
		{
			return m_iter;
		}

		iterator& operator++()
		{
			m_iter = m_iter->m_next;
			return *this;
		}

		iterator operator++(int)
		{
			iterator temp = *this;
			this->m_iter = this->m_iter->m_next;
			return temp;
		}

		iterator& operator--()
		{
			m_iter = m_iter->m_prev;
			return *this;
		}

		iterator operator--(int)
		{
			iterator* temp = *this;
			this->m_iter = this->m_iter->m_prev;
			return temp;
		}

		bool operator!=(const iterator& other) const
		{
			return this->m_iter != other.m_iter;
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
	iterator find(T value);
	void clear();

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

	if (rhs.m_head == nullptr)
	{
		MyList();
		return;
	}

	m_head = new Node;
	m_head->m_prev = nullptr;

	m_tail = new Node;
	m_tail->m_next = nullptr;

	Node* temp = m_head;
	Node* nowNode = rhs.m_head->m_next;
	while (nowNode->m_next != nullptr)
	{
		Node* newNode = new Node;
		newNode->m_data = nowNode->m_data;
		
		temp->m_next = newNode;
		newNode->m_prev = temp;
		temp = newNode;

		nowNode = nowNode->m_next;
	}

	temp->m_next = m_tail;
	m_tail->m_prev = temp;
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
	if (m_head == nullptr)
	{
		return;
	}
	
	Node* nowNode = m_head;
	while (nowNode->m_next != nullptr)
	{
		Node* nextNode = nowNode->m_next;
		delete nowNode;
		nowNode = nextNode;
	}
}

template<typename T>
inline MyList<T>& MyList<T>::operator=(const MyList& rhs)
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

	Node* nowNode = m_head;
	while (nowNode->m_next != nullptr)
	{
		Node* nextNode = nowNode->m_next;
		delete nowNode;
		nowNode = nextNode;
	}

	m_head = new Node();
	m_tail = new Node();
	
	nowNode = rhs.m_head;
	Node* newNode = new Node;

	while (nowNode->m_next != nullptr)
	{
		newNode->m_data = nowNode->m_data;
		newNode->m_prev = nowNode->m_prev;
		newNode->m_next = nowNode->m_next;

		if (m_head->m_next == nullptr)
		{
			m_head->m_prev = nullptr;
			m_head->m_next = newNode;
		}

		nowNode = nowNode->m_next;
	}

	m_tail->m_prev = newNode;
	m_tail->m_next = nullptr;
	m_size = rhs.m_size;

	return *this;
}

template<typename T>
inline MyList<T>& MyList<T>::operator=(MyList&& rhs)
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

	Node* nowNode = m_head;
	while (nowNode != nullptr)
	{
		Node* nextNode = nowNode->m_next;
		delete nowNode;
		nowNode = nextNode;
	}

	m_head = rhs.m_head;
	m_tail = rhs.m_tail;
	m_size = rhs.m_size;

	rhs.m_head = nullptr;
	rhs.m_tail = nullptr;
	rhs.m_size = 0;

	return *this;
}

template<typename T>
inline T& MyList<T>::operator[](size_t index) const
{
	Node* temp = m_head;

	for (size_t i = 0; i <= index; i++)
	{
		temp = temp->m_next;
	}

	return temp->m_data;
}

template<typename T>
inline bool MyList<T>::empty() const
{
	return m_size == 0;
}

template<typename T>
inline size_t MyList<T>::size() const
{
	return m_size;
}

template<typename T>
inline typename MyList<T>::iterator MyList<T>::begin() const
{
	return iterator(m_head->m_next);
}

template<typename T>
inline typename MyList<T>::iterator MyList<T>::end() const
{
	return iterator(m_tail);
}

template<typename T>
inline T MyList<T>::front() const
{
	Node* nextNode = m_head->m_next;
	if (nextNode == nullptr)
	{
		return T();
	}

	return nextNode->m_data;
}

template<typename T>
inline T MyList<T>::back() const
{
	Node* prevNode = m_tail->m_prev;
	if (prevNode == nullptr)
	{
		return T();
	}

	return prevNode->m_data;
}

template<typename T>
inline void MyList<T>::push_front(const T& value)
{
	Node* newNode = new Node();
	Node* firstNode = m_head->m_next;

	newNode->m_data = value;
	newNode->m_prev = m_head;
	newNode->m_next = firstNode;

	firstNode->m_prev = newNode;
	m_head->m_next = newNode;

	m_size++;
}

template<typename T>
inline void MyList<T>::push_back(const T& value)
{
	Node* newNode = new Node();
	Node* lastNode = m_tail->m_prev;

	newNode->m_data = value;
	newNode->m_prev = lastNode;
	newNode->m_next = m_tail;

	lastNode->m_next = newNode;
	m_tail->m_prev = newNode;

	m_size++;
}

template<typename T>
inline void MyList<T>::pop_front()
{
	if (empty())
	{
		return;
	}

	Node* firstNode = m_head->m_next;

	m_head->m_next = firstNode->m_next;
	firstNode->m_next->m_prev = m_head;

	delete firstNode;

	m_size--;
}

template<typename T>
inline void MyList<T>::pop_back()
{
	if (empty())
	{
		return;
	}

	Node* lastNode = m_tail->m_prev;

	m_tail->m_prev = lastNode->m_prev;
	lastNode->m_prev->m_next = m_tail;

	delete lastNode;

	m_size--;
}

template<typename T>
inline void MyList<T>::insert(iterator iter, const T& value)
{
	Node* newNode = new Node();
	Node* target = &iter;
	Node* prevNode = target->m_prev;

	newNode->m_data = value;
	newNode->m_prev = prevNode;
	newNode->m_next = target;

	prevNode->m_next = newNode;
	target->m_prev = newNode;

	m_size++;
}

template<typename T>
inline void MyList<T>::erase(iterator iter)
{
	Node* target = &iter;
	Node* prevNode = target->m_prev;
	Node* nextNode = target->m_next;

	prevNode->m_next = nextNode;
	nextNode->m_prev = prevNode;

	delete target;

	m_size--;
}

template<typename T>
inline typename MyList<T>::iterator MyList<T>::find(T value)
{
	MyList<T>::iterator it = begin();
	while (it != end())
	{
		Node* node = &it;
		if (node->m_data == value)
		{
			return it;
		}

		it++;
	}

	return nullptr;
}

template <typename T>
void MyList<T>::clear()
{
	MyList<T>::iterator it = begin();
	while (it != end())
	{
		erase(it);
	}
	
	m_head->m_next = nullptr;
	m_tail->m_prev = nullptr;
	m_size = 0;
}
