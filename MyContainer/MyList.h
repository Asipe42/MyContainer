#pragma once
#include <memory>

template <typename T>
class MyList
{
public:
	struct Node; // 전방 선언

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