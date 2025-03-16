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

		iterator& operator++()
		{
			m_iter = m_iter->m_next;
			return *this;
		}

		iterator& operator--()
		{
			m_iter = m_iter->m_prev;
			return *this;
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

	if (m_head == nullptr)
	{
		MyList();
		return;
	}

	Node* nowNode = rhs.m_head;
	Node* newNode = new Node;

	while(nowNode != nullptr)
	{
		newNode->m_data = nowNode->m_data;
		newNode->m_prev = nowNode->m_prev;
		newNode->m_next = nowNode->m_next;

		if (m_head == nullptr)
		{
			m_head = new Node();
			m_head->m_prev = nullptr;
			m_head->m_next = newNode;
		}

		nowNode = nowNode->m_next;
	}

	m_tail->m_prev = newNode;
	m_tail->m_next = nullptr;
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
	
}

template<typename T>
inline MyList<T>& MyList<T>::operator=(MyList&& rhs)
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
	while (nowNode != nullptr)
	{
		Node* nextNode = nowNode->m_next;
		delete nowNode;
		nowNode = nextNode;
	}

	nowNode = rhs.m_head;
	Node* newNode = new Node;

	while (nowNode != nullptr)
	{
		newNode->m_data = nowNode->m_data;
		newNode->m_prev = nowNode->m_prev;
		newNode->m_next = nowNode->m_next;

		if (m_head == nullptr)
		{
			m_head = new Node();
			m_head->m_prev = nullptr;
			m_head->m_next = newNode;
		}
	}

	m_tail->m_prev = newNode;
	m_tail->m_next = nullptr;
	m_size = rhs.m_size;

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
	lastNode->m_prev->m_prev = m_tail;

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
