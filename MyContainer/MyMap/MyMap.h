// Copyright Modin, All Rights Reserved.

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

    struct Node;
    class MyIterator
    {
    public:
        MyIterator() : current(NIL) { }
        MyIterator(Node* node) : current(node) { }
        Node& operator*() const { return *current; }

    private:
        Node* current;
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
    
    Node* find(K key);

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

        Node(K k, V v, const NodeColor c = NodeColor::Red)
            : key(k), value(v), color(c), left(nullptr), right(nullptr), parent(nullptr) { }
    };
    
    Node* copyTree(Node* node);
    void clearTree(Node* node);
    
    void insertBinaryTree(Node* z);
    void fixViolation_insert(Node* z);
    void fixViolation_erase(Node* x);
    void rotateLeft(Node* x);
    void rotateRight(Node* y);

    Node* minimum(Node* node);
    void transplant(Node* x, Node* y);
    
    Node* m_root;
    size_t m_size;

    static Node* NIL;
};

template <typename K, typename V>
typename MyMap<K, V>::Node* MyMap<K, V>::NIL = new Node(K(), V(), NodeColor::Black);

template <typename K, typename V>
MyMap<K, V>::MyMap() noexcept
    : m_root(NIL)
{
}

template <typename K, typename V>
MyMap<K, V>::MyMap(const MyMap& rhs)
    : m_root(NIL)
{
    /*
     * 복사 생성자
     *	- 깊은 복사를 수행한다.
     *	- 깊은 복사란 포인터가 참조하고 있는 메모리에 있는 데이터에 대한 사본을 만드는 것이다.
     */
    
    if (rhs.m_root == NIL)
    {
        return;
    }

    m_root = copyTree(rhs.m_root);
}

template <typename K, typename V>
MyMap<K, V>::MyMap(MyMap&& rhs) noexcept
    : m_root(NIL)
{
    /*
     * 이동 생성자
     *	- 이동 생성자는 rvalue에 대한 사본을 생성한다.
     *  - rvalue는 임시 객체를 의미한다.
     */
    
    rhs.m_root = NIL; // 소유권 이전을 명확히 한다.
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

    if (this != *rhs)
    {
        clear();
        
        if (rhs.m_root != NIL)
        {
            m_root = copyTree(rhs.m_root); // 깊은 복사 수행
        }
        else
        {
            m_root = NIL;
        }
    }
    
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

    if (this == &rhs)
    {
        return *this;
    }

    clear(); 

    m_root = rhs.m_root;
    rhs.m_root = nullptr;

    return *this;
}

template <typename K, typename V>
V& MyMap<K, V>::operator[](const K& key)
{
    Node* node = find(key);
    if (node == NIL)
    {
        insert(key, V());
        node = find(key);
    }

    return node->value;
}

template <typename K, typename V>
void MyMap<K, V>::insert(K key, V value)
{
    Node* newNode = new Node(key, value);
    insertBinaryTree(newNode);
    fixViolation_insert(newNode);

    m_size++;
}

template <typename K, typename V>
void MyMap<K, V>::erase(K key)
{
    Node* target = find(key);
    if (target == NIL)
    {
        return;
    }

    /*
     * 단계
     *  1. target의 경우의 수를 판단한다.
     *  2. 부모/자식 간 연결을 끊거나 대체한다.
     *  3. dobule black 상황을 판단하고 해결한다.
     */
    
    Node* replacement;
    NodeColor cacheColor = target->color;

    /*
     * 경우의 수
     *  A. target의 자식이 없는 경우
     *  B. target이 왼쪽 자식만 있는 경우
     *  C. target이 오른쪽 자식만 있는 경우
     *  D. target의 자식이 두 개인 경우
     *      - 후계자를 찾아 대체한다.
     *      - 후계자는 오른쪽 서브 트리에서 가장 작은 노드이다.
     *      - 후계자를 오른쪽 서브 트리에서 가장 작은 노드로 하는 이유는 중위 순회를 유지하기 위함이다.
     */
    
    if (target->right == NIL)
    {
        // Case A, B
        replacement = target->left;
        transplant(target, target->left);
    }
    else if (target->left == NIL)
    {
        // Case A, C
        replacement = target->right;
        transplant(target, target->right);
    }
    else
    {
        // Case D
        Node* successor = minimum(target->right);
        replacement = successor;
        
        // successor target을 대체하기 전에, successor의 자식을 successor의 부모와 연결한다.
        if (successor->parent != target)
        {
            transplant(successor, successor->right); // 왼쪽 자식은 가질 수 없음으로 무시

            successor->left = target->left;
            successor->right = target->right;
            target->left->parent = successor;
            target->right->parent = successor;
        }
        
        transplant(target, successor);
    }

    delete target;
    
    if (cacheColor == Black)
    {
        fixViolation_erase(replacement);
        if (replacement == NIL)
        {
            replacement->parent = nullptr;
        }
    }

    m_size--;
}

template <typename K, typename V>
typename MyMap<K, V>::Node* MyMap<K, V>::find(K key)
{
    Node* x = m_root;
    while (x != NIL && x->key != key)
    {
        if (key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    return x; // 암시적 형변환 주의
}

template <typename K, typename V>
void MyMap<K, V>::clear()
{
    clearTree(m_root);
}

template <typename K, typename V>
size_t MyMap<K, V>::size() const
{
    return m_size;
}

template <typename K, typename V>
bool MyMap<K, V>::empty() const
{
    return m_size == 0;
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
    if (node == NIL)
    {
        return;
    }
    
    clearTree(node->left);
    clearTree(node->right);
    
    delete node;
}

template <typename K, typename V>
void MyMap<K, V>::insertBinaryTree(Node* z)
{
    /*
     * 이진 트리 삽입
     *  - key를 기준으로 왼쪽 자식은 key가 작고, 오른쪽 자식은 key가 크다.
     */

    z->left = NIL;
    z->right = NIL;
    
    Node* y = nullptr;  // 삽입 노드의 부모 후보
    Node* x = m_root;     // 탐색 중인 노드

    /*
     * 경우의 수
     *  A. x가 nullptr
     *  B. x의 key가 z의 key보다 작다.
     *  C. x의 key가 z의 key보다 크다.
     *  D. x의 key가 z의 key와 같다. (중복 허용 X)
     */
    
    while (x != NIL)
    {
        y = x;
        if (z->key < x->key)
        {
            // Case B
            x = x->left;
        }
        else if (z->key > x->key)
        {
            // Case C
            x = x->right;
        }
        else
        {
            // Case D
            delete z;
            return;
        }
    }

    z->parent = y;
    if (y == nullptr) 
    {
        // Case A
        m_root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
}

template <typename K, typename V>
void MyMap<K, V>::fixViolation_insert(Node* z)
{
    /*
     * Red-Black Tree 규칙
     *  1. 루트는 항상 블랙이다.
     *  2. 레드 노드는 레드 노드를 가질 수 없다.
     *  3. 모든 경로는 같은 수의 블랙 노드(Black Height)를 가져야 한다.
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
    while (z != m_root && z->parent->color == Red)
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
                    rotateRight(z);
                }

                // Case D
                z->parent->color = Black;
                gp->color = Red;
                rotateLeft(gp);
            }
        }
    }

    // Case A
    m_root->color = Black;
}

template <typename K, typename V>
void MyMap<K, V>::fixViolation_erase(Node* x)
{
    /*
     * Red-Black Tree 규칙
     *  1. 루트는 항상 블랙이다.
     *  2. 레드 노드는 레드 노드를 가질 수 없다.
     *  3. 모든 경로는 같은 수의 블랙 노드(Black Height)를 가져야 한다.
     *  4. 모든 리프 노드는 블랙이다.
     *  5. 리프 노드는 nullptr이다.
     */

    /*
     * Double Black
     *  - 삭제된 노드가 Black일 때 발생한다.
     *  - Black Height를 유지하기 위해 추가적인 처리가 필요하다.
     *  - Double Black은 Black Height를 1 감소시킨 것과 같다.
     *  - Double Black을 해결하기 위해서는 다음과 같은 경우를 고려해야 한다.
     *      - Case A: 삭제된 노드가 루트인 경우
     *          - double black 해소
     *      - Case B: 삭제된 노드의 형제 노드가 Red인 경우
     *          - 형제 노드를 Black으로 바꾸고, 부모를 Red로 바꾸고 회전한 다음 Case C~F로 간다.
     *      - Case C: 삭제된 노드의 형제 노드가 Black이고, 두 자식이 Black인 경우
     *          - 형제 노드를 Red로 바꾸고, Double Black을 부모로 올린다.
     *      - Case D: 삭제된 노드의 형제 노드가 Black이고, 왼쪽 자식이 Red, 오른쪽 자식이 Black인 경우
     *          - 형제 노드를 Red로 바꾸고, 왼쪽 자식을 Black으로 바꾸고 회전한 다음 Case F로 간다.
     *      - Case E: 삭제된 노드의 형제 노드가 Black이고, 오른쪽 자식이 Red인 경우
     *          - 형제 노드를 부모와 같은 색으로 바꾸고, 부모를 Black으로 바꾸고 오른쪽 자식을 Black으로 바꾸고 회전한다.
     */
    
    while (x != m_root && x->color == Black)
    {
        // 왼쪽 노드인 경우
        if (x == x->parent->left)
        {
            Node* s = x->parent->right;

            // Case B
            if (s->color == Red)
            {
                s->color = Black;
                x->parent->color = Red;
                rotateLeft(x->parent);
                s = x->parent->right; // 회전 후 형제노드
            }

            // Case C: 이전 s가 red였음으로, 현재 s는 black이 보장된다
            if (s->left->color == Black && s->right->color == Black)
            {
                s->color = Red;
                x = x->parent; // 부모로 이동
            }
            else
            {
                // Case D
                if (s->right->color == Black)
                {
                    s->left->color = Black;
                    s->color = Red;
                    rotateRight(s);
                    s = x->parent->right;
                }

                // Case E: CaseC와 D에 의해 왼쪽 자식이 Black, 오른쪽 자식이 Red임이 보장된다.
                s->color = x->parent->color;
                x->parent->color = Black;
                s->right->color = Black;
                rotateLeft(x->parent);
                x = m_root;
            }
        }
        // 오른쪽 노드인 경우 (대칭 처리)
        else
        {
            Node* s = x->parent->left;

            // Case B
            if (s->color == Red)
            {
                s->color = Black;
                x->parent->color = Red;
                rotateRight(x->parent); 
                s = x->parent->left; // 회전 후 형제노드. s가 red이므로, s의 자식은 black이다.
            }

            // Case C
            if (s->left->color == Black && s->right->color == Black)
            {
                s->color = Red;
                x = x->parent; // 부모로 이동
            }
            else
            {
                // Case D
                if (s->left->color == Black)
                {
                    s->right->color = Black;
                    s->color = Red;
                    rotateLeft(s);
                    s = x->parent->left;
                }
                
                // Case E: CaseC와 D에 의해 왼쪽 자식이 Black, 오른쪽 자식이 Red임이 보장된다.
                s->color = x->parent->color;
                x->parent->color = Black;
                s->left->color = Black;
                rotateRight(x->parent);
                x = m_root;
            }
        }
    }

    x->color = Black;
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
    if (y->left != NIL)
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
        m_root = y;
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
        m_root = x;
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

template <typename K, typename V>
typename MyMap<K, V>::Node* MyMap<K, V>::minimum(Node* node)
{
    while (node->left != NIL)
    {
        node = node->left;
    }

    return node;
}

template <typename K, typename V>
void MyMap<K, V>::transplant(Node* x, Node* y)
{
    /*
     * 경우의 수
     *  A. x가 루트이다.
     *  B. x가 부모의 왼쪽 자식이다.
     *  C. x가 부모의 오른쪽 자식이다.
     */

    if (x->parent == nullptr)
    {
        // Case A
        m_root = y;
    }
    else if (x == x->parent->left)
    {
        // Case B
        x->parent->left = y;
    }
    else
    {
        // Case C
        x->parent->right = y;
    }
    
    y->parent = x->parent;
}