#pragma once

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
};

template <typename K, typename V>
MyMap<K, V>::MyMap() noexcept
{
}

template <typename K, typename V>
MyMap<K, V>::MyMap(const MyMap& rhs)
{
}

template <typename K, typename V>
MyMap<K, V>::MyMap(MyMap&& rhs) noexcept
{
}

template <typename K, typename V>
MyMap<K, V>::~MyMap() noexcept
{
}

template <typename K, typename V>
MyMap<K, V>& MyMap<K, V>::operator=(const MyMap& rhs)
{
}

template <typename K, typename V>
MyMap<K, V>& MyMap<K, V>::operator=(MyMap&& rhs) noexcept
{
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
