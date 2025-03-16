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
{
}

template<typename T>
inline MyList<T>::MyList(MyList&& rhs) noexcept
{
}

template<typename T>
inline MyList<T>::~MyList() noexcept
{
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
