// Purpose: Provides set and unordered_set classes.
// header guards
#ifndef __set_hh__
#define __set_hh__
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <iostream>

template <typename T>
class o_set
{
public:
    std::set<T> set;
    int size();
    bool find(T x);
    void insert(T x);
    void remove(T x);
    bool empty();
    void del();
    void out();
    ~o_set();
    o_set();
    o_set(std::vector<T>);
};

template <typename T>
class u_set
{
public:
    std::unordered_set<T> set;
    int size();
    bool find(T x);
    void insert(T x);
    void remove(T x);
    bool empty();
    void del();
    void out();
    ~u_set();
    u_set();
    u_set(std::vector<T>);
};

template <typename T>
o_set<T>::o_set()
{
    this->set = std::set<T>();
}

template <typename T>
o_set<T>::o_set(std::vector<T> elements)
{
    this->set = std::set<T>();
    for (auto element : elements)
    {
        this->set.insert(element);
    }
}

template <typename T>
int o_set<T>::size()
{
    return this->set.size();
}

template <typename T>
bool o_set<T>::find(T element)
{
    return this->set.find(element) != this->set.end();
}

template <typename T>
void o_set<T>::insert(T element)
{
    this->set.insert(element);
}

template <typename T>
void o_set<T>::remove(T element)
{
    this->set.erase(element);
}

template <typename T>
bool o_set<T>::empty()
{
    return this->set.empty();
}

template <typename T>
void o_set<T>::out()
{
    for (auto element : this->set)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void o_set<T>::del()
{
    this->set.clear();
}

template <typename T>
o_set<T>::~o_set()
{
    this->set.clear();
}

template <typename T>
u_set<T>::u_set()
{
    this->set = std::unordered_set<T>();
}

template <typename T>
u_set<T>::u_set(std::vector<T> elements)
{
    this->set = std::unordered_set<T>();
    for (auto element : elements)
    {
        this->set.insert(element);
    }
}

template <typename T>
int u_set<T>::size()
{
    return this->set.size();
}

template <typename T>
bool u_set<T>::find(T element)
{
    return this->set.find(element) != this->set.end();
}

template <typename T>
void u_set<T>::insert(T element)
{
    this->set.insert(element);
}

template <typename T>
void u_set<T>::remove(T element)
{
    this->set.erase(element);
}

template <typename T>
bool u_set<T>::empty()
{
    return this->set.empty();
}

template <typename T>
void u_set<T>::out()
{
    for (auto element : this->set)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void u_set<T>::del()
{
    this->set.clear();
}

template <typename T>
u_set<T>::~u_set()
{
    this->set.clear();
}
#endif