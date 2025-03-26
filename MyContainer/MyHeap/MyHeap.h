// Copyright Modin, All Rights Reserved.

#pragma once
#include "../MyVector/MyVector.h"

/*
 * 힙
 *	- 아래의 두 가지 조건을 충족하는 완전 이진 트리이다.
 *	    1. 루트 노드에 항상 우선순위가 가장 높은 값이 있다.
 *	    2. 언제나 부모 노드가 자식 노드보다 우선순위가 높다.
 *	- 구현은 [Max Heap]으로 한다.
 */

template <typename T>
class MyHeap
{
public:
    MyHeap() noexcept;
    MyHeap(const MyHeap& rhs);
    MyHeap(MyHeap&& rhs) noexcept;
    ~MyHeap() noexcept;

    MyHeap& operator=(const MyHeap& rhs);
    MyHeap& operator=(MyHeap&& rhs) noexcept;

    bool empty() const;
    size_t size() const;
    T top() const;
    void push();
    void pop();
    
private:
    void heapify_up(size_t index);
    void heapify_down(size_t index);
    
    MyVector<T> m_vector;
    size_t m_size;
};

template <typename T>
MyHeap<T>::MyHeap() noexcept
{
}

template <typename T>
MyHeap<T>::MyHeap(const MyHeap& rhs)
{
}

template <typename T>
MyHeap<T>::MyHeap(MyHeap&& rhs) noexcept
{
}

template <typename T>
MyHeap<T>::~MyHeap() noexcept
{
}

template <typename T>
MyHeap<T>& MyHeap<T>::operator=(const MyHeap& rhs)
{
}

template <typename T>
MyHeap<T>& MyHeap<T>::operator=(MyHeap&& rhs)
{
}

template <typename T>
bool MyHeap<T>::empty() const
{
}

template <typename T>
size_t MyHeap<T>::size() const
{
}

template <typename T>
T MyHeap<T>::top() const
{
}

template <typename T>
void MyHeap<T>::push()
{
}

template <typename T>
void MyHeap<T>::pop()
{
}

template <typename T>
void MyHeap<T>::heapify_up(size_t index)
{
}

template <typename T>
void MyHeap<T>::heapify_down(size_t index)
{
}
