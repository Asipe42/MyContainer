#pragma once
#include "MyList/MyList.h"

template <typename K, typename V>
class MyMap
{
public:
    enum NodeColor : uint8_t
    {
        Red = 0,
        Black = 1,
    };

    class MyIterator
    {
        
    };
    
    MyMap() noexcept;
    MyMap(const MyMap& rhs);
    MyMap(MyMap&& rhs) noexcept;
    ~MyMap() noexcept;

    MyMap& operator=(const MyMap& rhs);
    MyMap& operator=(MyMap&& rhs) noexcept;

    V& operator[](const K& key);
    void insert(K key, V value);
    void erase(K key);
    void erase(MyIterator it);
    
    MyIterator find(K key);
    bool count(K key) const;

    void clear();
    size_t size() const;
    bool empty() const;

    MyIterator begin();
    MyIterator end();

private:
    struct Node
    {
        K key;
        V value;
        NodeColor color;
        Node* left;
        Node* right;
        Node* parent;

        Node(K k, V v)
            : key(k), value(v), color(NodeColor::Red), left(nullptr), right(nullptr), parent(nullptr) { } 
    };

    Node* copyTree(Node* node);
    void clearTree(Node* node);

    Node* root;
};

template <typename K, typename V>
MyMap<K, V>::MyMap() noexcept
    : root(nullptr)
{
}

template <typename K, typename V>
MyMap<K, V>::MyMap(const MyMap& rhs)
    : root(nullptr)
{
    /*
     * 복사 생성자
     *	- 깊은 복사를 수행한다.
     *	- 깊은 복사란 포인터가 참조하고 있는 메모리에 있는 데이터에 대한 사본을 만드는 것이다.
     */
    
    if (rhs.root == nullptr)
    {
        return;
    }

    root = copyTree(rhs.root);
}

template <typename K, typename V>
MyMap<K, V>::MyMap(MyMap&& rhs) noexcept
    : root(rhs.root)
{
    /*
     * 이동 생성자
     *	- 이동 생성자는 rvalue에 대한 사본을 생성한다.
     *  - rvalue는 임시 객체를 의미한다.
     */
    
    rhs.root = nullptr; // 소유권 이전을 명확히 한다.
}

template <typename K, typename V>
MyMap<K, V>::~MyMap() noexcept
{
    clear();
}

template <typename K, typename V>
MyMap<K, V>& MyMap<K, V>::operator=(const MyMap& rhs)
{
    /*
     * 복사 대입	연산자
     *	- 복사 생성자와 비슷하게 동작한다.
     *	- 복사 생성자와의 차이점은 이미 메모리가 할당되어 있는 상태에서 동작한다는 것이다.
     */

    if (rhs.root == nullptr)
    {
        return *this;
    }

    root = copyTree(rhs.root);
    return *this;
}

template <typename K, typename V>
MyMap<K, V>& MyMap<K, V>::operator=(MyMap&& rhs) noexcept
{
    /*
     * 이동 대입 연산자
     *	- 이동 생성자와 비슷하게 동작한다.
     *  - 이동 생성자와의 차이점은 이미 메모리가 할당되어 있는 상태에서 동작한다는 것이다.
     */

    if (rhs.root == nullptr)
    {
        return *this;
    }

    root = rhs.root;
    return *this;
}

template <typename K, typename V>
V& MyMap<K, V>::operator[](const K& key)
{
}

template <typename K, typename V>
void MyMap<K, V>::insert(K key, V value)
{
}

template <typename K, typename V>
void MyMap<K, V>::erase(K key)
{
}

template <typename K, typename V>
void MyMap<K, V>::erase(MyIterator it)
{
}

template <typename K, typename V>
typename MyMap<K, V>::MyIterator MyMap<K, V>::find(K key)
{
}

template <typename K, typename V>
bool MyMap<K, V>::count(K key) const
{
}

template <typename K, typename V>
void MyMap<K, V>::clear()
{
    clearTree(root);
}

template <typename K, typename V>
size_t MyMap<K, V>::size() const
{
}

template <typename K, typename V>
bool MyMap<K, V>::empty() const
{
}

template <typename K, typename V>
typename MyMap<K, V>::MyIterator MyMap<K, V>::begin()
{
}

template <typename K, typename V>
typename MyMap<K, V>::MyIterator MyMap<K, V>::end()
{
}

template <typename K, typename V>
typename MyMap<K, V>::Node* MyMap<K, V>::copyTree(Node* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    Node* newNode = new Node(node->key, node->value);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);

    if (newNode->left)
    {
        newNode->left->parent = newNode;
    }

    if (newNode->right)
    {
        newNode->right->parent = newNode;
    }

    return newNode;
}

template <typename K, typename V>
void MyMap<K, V>::clearTree(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    
    clearTree(node->left);
    clearTree(node->right);
    
    delete node;
}
