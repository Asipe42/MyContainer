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

/*
 * 완전 이진 트리
 *  - 아래의 두 가지 조건을 충족하는 이진 트리이다.
 *      1. 마지막 레벨을 제외한 나머지 레벨에서 모든 노드가 채워져 있을 것
 *      2. 노드의 추가는 왼쪽에서 오른쪽으로 이루어질 것
 */

/*
 * 이진 트리
 *  - 부모가 최대 2개의 자식을 가질 수 있는 트리이다.
 */

/*
 * 트리
 *  - 노드 간의 연결이 계층적으로 이루어진 그래프
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
    void push(T value);
    void pop();
    
private:
    void heapify_up(size_t index);
    void heapify_down(size_t index);

    /*
     * 인덱스 추론
     *  - 부모 노드: (자식 노드의 인덱스 - 1) / 2
     *  - 왼쪽 자식 노드: (부모 노드의 인덱스 * 2) + 1
     *  - 오른쪽 자식 노드: (부모 노드의 인덱스 * 2) + 2
     */
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
void MyHeap<T>::push(T value)
{
    /*
     * 설명
     *  - 노드를 생성하고(push_back), 힙 속성을 유지하기 위해 부모 방향으로 버블링한다.
     */
    
    m_vector.push_back(value);
    m_size = m_vector.size();
    
    heapify_up(m_vector.size() - 1);
}

template <typename T>
void MyHeap<T>::pop()
{
    /*
     * 설명
     *  - 리프 노드를 루트에 두고, 힙 속성을 유지하기 위해 자식 방향으로 버블링 한다.
     */
    
    m_vector[0] = m_vector.back();
    m_vector.pop_back();
    m_size = m_vector.size();
    
    heapify_down(0);
}

template <typename T>
void MyHeap<T>::heapify_up(size_t index)
{
    /*
     * 설명
     *  - 자신과 부모를 비교하여 버블링한다.
     */

    if (index == 0)
    {
        return;
    }
    
    size_t parent = (index - 1) / 2;
    if (m_vector[parent] < m_vector[index])
    {
        std::swap(m_vector[index], m_vector[parent]);
        heapify_up(parent);
    }
}

template <typename T>
void MyHeap<T>::heapify_down(size_t index)
{
    /*
     * 설명
     *  - 자신과 자식들을 비교해, 우선순위가 높은 쪽으로 버블링한다.
     */
    
    size_t left = index * 2 + 1;
    size_t right = index * 2 + 2;
    size_t largest = index;

    if (left < m_size && m_vector[left] > m_vector[largest])
    {
        largest = left;
    }

    if (right < m_size && m_vector[right] > m_vector[largest])
    {
        largest = right;
    }

    if (largest != index)
    {
        std::swap(m_vector[index], m_vector[largest]);
        heapify_down(largest);
    }
}
