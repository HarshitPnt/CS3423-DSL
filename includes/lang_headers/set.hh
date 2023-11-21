#include "defs.hh"
namespace fsm
{
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
};