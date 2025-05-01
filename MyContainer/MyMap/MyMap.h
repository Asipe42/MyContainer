#pragma once

class MyMap
{
public:
    MyMap() noexcept;
    MyMap(const MyMap& rhs);
    MyMap(MyMap&& rhs) noexcept;
    ~MyMap() noexcept;

    MyMap& operator=(const MyMap& rhs);
    MyMap& operator=(MyMap&& rhs) noexcept;
};

inline MyMap::MyMap() noexcept
{
}

inline MyMap::MyMap(const MyMap& rhs)
{
}

inline MyMap::MyMap(MyMap&& rhs) noexcept
{
}

inline MyMap::~MyMap() noexcept
{
}

inline MyMap& MyMap::operator=(const MyMap& rhs)
{
}

inline MyMap& MyMap::operator=(MyMap&& rhs) noexcept
{
}
