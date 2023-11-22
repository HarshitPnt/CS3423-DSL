#include "../../includes/lang_headers/set.hh"
#include <iostream>
namespace fsm
{
    template <class T>
    o_set<T>::o_set()
    {
        this->set = std::set<T>();
    }

    template <class T>
    o_set<T>::o_set(std::vector<T> elements)
    {
        this->set = std::set<T>();
        for (auto element : elements)
        {
            this->set.insert(element);
        }
    }

    template <class T>
    int o_set<T>::size()
    {
        return this->set.size();
    }

    template <class T>
    bool o_set<T>::find(T element)
    {
        return this->set.find(element) != this->set.end();
    }

    template <class T>
    void o_set<T>::insert(T element)
    {
        this->set.insert(element);
    }

    template <class T>
    void o_set<T>::remove(T element)
    {
        this->set.erase(element);
    }

    template <class T>
    bool o_set<T>::empty()
    {
        return this->set.empty();
    }

    template <class T>
    void o_set<T>::out()
    {
        for (auto element : this->set)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    template <class T>
    void o_set<T>::del()
    {
        this->set.clear();
    }

    template <class T>
    o_set<T>::~o_set()
    {
        this->set.clear();
    }

    template <class T>
    u_set<T>::u_set()
    {
        this->set = std::unordered_set<T>();
    }

    template <class T>
    u_set<T>::u_set(std::vector<T> elements)
    {
        this->set = std::unordered_set<T>();
        for (auto element : elements)
        {
            this->set.insert(element);
        }
    }

    template <class T>
    int u_set<T>::size()
    {
        return this->set.size();
    }

    template <class T>
    bool u_set<T>::find(T element)
    {
        return this->set.find(element) != this->set.end();
    }

    template <class T>
    void u_set<T>::insert(T element)
    {
        this->set.insert(element);
    }

    template <class T>
    void u_set<T>::remove(T element)
    {
        this->set.erase(element);
    }

    template <class T>
    bool u_set<T>::empty()
    {
        return this->set.empty();
    }

    template <class T>
    void u_set<T>::out()
    {
        for (auto element : this->set)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    template <class T>
    void u_set<T>::del()
    {
        this->set.clear();
    }

    template <class T>
    u_set<T>::~u_set()
    {
        this->set.clear();
    }
}