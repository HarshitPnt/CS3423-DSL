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
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

namespace fsm
{
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
        u_set<T> operator+(u_set<T> &other);
        u_set<T> operator-(u_set<T> &other);
        u_set<u_set<T>> power_set(); // TODO
    };

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
        T operator[](size_t index) const;
        o_set<T> operator+(o_set<T> &other);
        o_set<T> operator-(o_set<T> &other);

        o_set<o_set<T>> power_set(); // TODO
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
        std::cout << "{ ";
        for (auto element : this->set)
        {
            std::cout << element << " ";
        }
        std::cout << "}" << std::endl;
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
    T o_set<T>::operator[](size_t index) const
    {
        try
        {
            if (index < set.size())
            {
                auto it = set.begin();
                std::advance(it, index);
                return *it;
            }
            else
            {
                throw std::out_of_range("Index out of range");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << RED << "Runtime Error: " << RESET << e.what() << '\n';
            throw std::out_of_range("Index out of range");
            // std::abort();
        }
    }

    template <typename T>
    o_set<T> o_set<T>::operator+(o_set<T> &other)
    {
        o_set<T> result;
        for (auto element : this->set)
        {
            result.insert(element);
        }
        for (auto element : other.set)
        {
            result.insert(element);
        }
        return result;
    }

    template <typename T>
    o_set<T> o_set<T>::operator-(o_set<T> &other)
    {
        o_set<T> result;
        for (auto element : this->set)
        {
            if (!other.find(element))
            {
                result.insert(element);
            }
        }
        return result;
    }

    template <typename T>
    o_set<o_set<T>> o_set<T>::power_set()
    {
        o_set<o_set<T>> result;
        o_set<T> empty;
        result.insert(empty);
        // Find all subsets of the set
        return result;
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
        std::cout << "{ ";
        for (auto element : this->set)
        {
            std::cout << element << " ";
        }
        std::cout << "}" << std::endl;
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

    template <typename T>
    u_set<T> u_set<T>::operator+(u_set<T> &other)
    {
        u_set<T> result;
        for (auto element : this->set)
        {
            result.insert(element);
        }
        for (auto element : other.set)
        {
            result.insert(element);
        }
        return result;
    }

    template <typename T>
    u_set<T> u_set<T>::operator-(u_set<T> &other)
    {
        u_set<T> result;
        for (auto element : this->set)
        {
            if (!other.find(element))
            {
                result.insert(element);
            }
        }
        return result;
    }

    template <typename T>
    u_set<u_set<T>> u_set<T>::power_set()
    {
        u_set<u_set<T>> result;
        u_set<T> empty;
        result.insert(empty);
        // Find all subsets of the set
        return result;
    }
}

#endif