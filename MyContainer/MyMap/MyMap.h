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

    Node* copyTree(Node* node);
    void clearTree(Node* node);
    
    void fixViolation(Node* z);
    void rotateLeft(Node* x);
    void rotateRight(Node* y);

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

template <typename K, typename V>
void MyMap<K, V>::fixViolation(Node* z)
{
    /*
     * Red-Black Tree 규칙
     *  1. 루트는 항상 블랙이다.
     *  2. 레드 노드는 레드 노드를 가질 수 없다.
     *  3. 모든 경로는 같은 수의 블랙 노드를 가져야 한다.
     *  4. 모든 리프 노드는 블랙이다.
     *  5. 리프 노드는 nullptr이다.
     */

    /*
     * 경우의 수
     *  A. Z가 Root
     *      - Z를 Black으로 바꾼다.
     *  B. Uncle이 Red
     *      - Z의 부모와 Uncle을 Black으로 바꾸고, 조부모를 Red로 바꾼다.
     *  C. Uncle이 Black, 내부 삼각형
     *      - Rotate Left 하여 Case D로 이동
     *  D. Uncle이 Black, 일직선
     *      - Z의 부모를 Black으로, 조부모를 Red로 바꾸고 Rotate Right 한다.
     */

    // 1, 2번 위반 검사
    while (z != root && z->parent->color == Red)
    {
        Node* gp = z->parent->parent;
        if (z->parent == gp->left)
        {
            // Uncle이 오른쪽
            Node* uncle = gp->right;

            // Case B
            if (uncle && uncle->color == Red)
            {
                z->parent->color = Black;
                uncle->color = Black;
                gp->color = Red;
                z = gp; // 조부모로 이동하여 재귀적 적용
            }
            else
            {
                // Case C
                if (z == z->parent->right)
                {
                    z = z->parent;
                    rotateLeft(z);
                }

                // Case D
                z->parent->color = Black;
                gp->color = Red;
                rotateRight(gp);
            }
        }
        else
        {
            // Uncle이 왼쪽
            Node* uncle = gp->left;

            // Case B
            if (uncle && uncle->color == Red)
            {
                z->parent->color = Black;
                uncle->color = Black;
                gp->color = Red;
                z = gp; // 조부모로 이동하여 재귀적 적용
            }
            else
            {
                // Case C
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rotateLeft(z);
                }

                // Case D
                z->parent->color = Black;
                gp->color = Red;
                rotateRight(gp);
            }
        }
    }

    // Case A
    root->Color = Black;
}

template <typename K, typename V>
void MyMap<K, V>::rotateLeft(Node* x)
{
    /*
     * 회전
     *  - 레드 블랙 이진 트리의 Violation을 해결하기 위해 동작이다.
     *  - 자식을 부모에 위치로 올리고, 부모가 반대편 자식이 된다.
     *  - x는 부모, y는 오른쪽 자식이다.
     */

    /*
     * 알고리즘
     *  1. x의 오른쪽 자식을 y의 왼쪽 자식으로 교체한다.
     *  2. y를 x의 부모와 연결한다. (승격)
     *  3. y와 x를 연결한다.
     */

    Node* y = x->right;

    // Algorithm 1
    x->right = y->left;
    if (y->left != nullptr)
    {
        y->left->parent = x;
    }

    /*
     * Algorithm 2
     * 경우의 수
     *  1. x가 루트이다.
     *  2. x가 부모의 왼쪽 자식이다.
     *  3. x가 부모의 오른쪽 자식이다.
     */
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
        root = y;
    }
    else if (x->parent->left == x)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

    // Algorithm 3
    y->left = x;
    x->parent = y;
}

template <typename K, typename V>
void MyMap<K, V>::rotateRight(Node* y)
{
    /*
     * 회전
     *  - 레드 블랙 이진 트리의 Violation을 해결하기 위해 동작이다.
     *  - 자식을 부모에 위치로 올리고, 부모가 반대편 자식이 된다.
     *  - y는 부모, x는 왼쪽 자식이다.
     */

    /*
     * 알고리즘
     *  1. y의 왼쪽 자식을 x의 오른쪽 자식으로 교체한다.
     *  2. x를 y의 부모와 연결한다. (승격)
     *  3. x와 y를 연결한다.
     */
    
    Node* x = y->left;

    // Algorithm 1
    y->left = x->right;
    if (x->right != nullptr)
    {
        x->right->parent = y;
    }
    
    /*
     * Algorithm 2
     * 경우의 수
     *  1. y가 루트이다.
     *  2. y가 부모의 왼쪽 자식이다.
     *  3. y가 부모의 오른쪽 자식이다.
     */
    x->parent = y->parent;
    if (y->parent == nullptr)
    {
        root = x;
    }
    else if (y->parent->left == y)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    // Algorithm 3
    x->right = y;
    y->parent = x;
}
