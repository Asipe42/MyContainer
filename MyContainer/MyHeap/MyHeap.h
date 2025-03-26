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
    : m_vector(MyVector<T>())
    , m_size(0)
{
}

template <typename T>
MyHeap<T>::MyHeap(const MyHeap& rhs)
    : m_vector(rhs.m_vector)
    , m_size(rhs.m_size)
{
    /*
     * 복사 생성자
     *	- 깊은 복사를 수행한다.
     *	- 깊은 복사란 포인터가 참조하고 있는 메모리에 있는 데이터에 대한 사본을 만드는 것이다.
     */
}

template <typename T>
MyHeap<T>::MyHeap(MyHeap&& rhs) noexcept
    : m_vector(std::move(rhs.m_vector))
    , m_size(rhs.m_size)
{
    /*
     * 이동 생성자
     *	- 이동 생성자는 rvalue에 대한 사본을 생성한다.
     *  - rvalue는 임시 객체를 의미한다.
     */
    
    rhs.m_size = 0;
}

template <typename T>
MyHeap<T>::~MyHeap() noexcept
{
}

template <typename T>
MyHeap<T>& MyHeap<T>::operator=(const MyHeap& rhs)
{
    /*
     * 복사 대입	연산자
     *	- 복사 생성자와 비슷하게 동작한다.
     *	- 복사 생성자와의 차이점은 이미 메모리가 할당되어 있는 상태에서 동작한다는 것이다.
     */
    
    m_vector = rhs.m_vector;
    m_size = rhs.m_size;
}

template <typename T>
MyHeap<T>& MyHeap<T>::operator=(MyHeap&& rhs) noexcept
{
    /*
     * 이동 대입 연산자
     *	- 이동 생성자와 비슷하게 동작한다.
     *  - 이동 생성자와의 차이점은 이미 메모리가 할당되어 있는 상태에서 동작한다는 것이다.
     */

    m_vector = std::move(rhs.m_vector);
    m_size = rhs.m_size;

    rhs.m_size = 0;
}

template <typename T>
bool MyHeap<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
size_t MyHeap<T>::size() const
{
    return m_size;
}

template <typename T>
T MyHeap<T>::top() const
{
    if (empty())
    {
        return T();
    }

    return m_vector.front();
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
