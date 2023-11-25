// Purpose: Provides set and unordered_set classes.
// header guards
#ifndef __set_hh__
#define __set_hh__
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <type_traits>
#include <iostream>
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

// need to do printing for u_set

namespace fsm
{
    template <typename T>
    class u_set;

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
        template <typename U>
        operator o_set<U>() const
        {
            o_set<U> result;
            for (const auto &element : set)
            {
                result.set.insert(static_cast<U>(element));
            }
            return result;
        }
        void del();
        void out()
        {
            std::cout << "Set contents: ";
            for (const auto &element : set)
            {
                printElement(element);
                std::cout << " ";
            }
            std::cout << std::endl;
        }
        ~o_set();
        o_set();
        o_set(std::vector<T>);
        T operator[](size_t index) const;
        o_set<T> operator+(o_set<T> &other);
        o_set<T> operator-(o_set<T> &other);
        // intersection? (* operator)
        o_set<T> operator*(o_set<T> &other);
        o_set<T> operator*(u_set<T> &other);
        o_set<T> operator+(u_set<T> &other);
        o_set<T> operator-(u_set<T> &other);
        o_set<o_set<T>> power_set(); // TODO

        friend bool operator<(const o_set &lhs, const o_set &rhs)
        {
            return lhs.set < rhs.set;
        }

    private:
        void printElement(const T &element)
        {
            if constexpr (std::is_same_v<T, o_set<T>>)
            {
                // If the element is an o_set, recursively call its out function
                element.out();
            }
            else
            {
                std::cout << element;
            }
        }
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const o_set<T> &set)
    {
        os << "{";
        for (const auto &element : set.set)
        {
            os << element << " ";
        }
        os << "}";
        return os;
    }

    template <typename>
    struct is_o_set : public std::false_type
    {
    };

    template <typename T>
    struct is_o_set<o_set<T>> : public std::true_type
    {
    };

    template <typename T>
    constexpr bool is_o_setFunc(T const &)
    {
        return is_o_set<T>::value;
    }

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
        template <typename U>
        operator u_set<U>() const
        {
            u_set<U> result;
            for (const auto &element : set)
            {
                result.set.insert(static_cast<U>(element));
            }
            return result;
        }
        ~u_set();
        u_set();
        u_set(std::vector<T>);
        u_set<T> operator+(u_set<T> &other);
        u_set<T> operator-(u_set<T> &other);
        // intersection? (* operator)
        u_set<T> operator*(u_set<T> &other);
        o_set<T> operator*(o_set<T> &other);
        o_set<T> operator-(o_set<T> &other);
        o_set<T> operator+(o_set<T> &other);
        u_set<u_set<T>> power_set(); // TODO
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
    o_set<T> o_set<T>::operator+(u_set<T> &other)
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
    o_set<T> u_set<T>::operator+(o_set<T> &other)
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
    void recursive_power_set(o_set<o_set<T>> &res, o_set<T> &set, int index, o_set<T> &curr)
    {
        if (index == set.size())
        {
            res.insert(curr);
            return;
        }
        recursive_power_set(res, set, index + 1, curr);
        curr.insert(set[index]);
        recursive_power_set(res, set, index + 1, curr);
        curr.remove(set[index]);
    }

    template <typename T>
    o_set<o_set<T>> o_set<T>::power_set()
    {
        o_set<o_set<T>> result;
        o_set<T> empty;
        result.insert(empty);
        o_set<T> curr;
        // Find all subsets of the set
        recursive_power_set(result, *this, 0, curr);
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
    void recursive_power_set(u_set<u_set<T>> &res, u_set<T> &set, int index, u_set<T> &curr)
    {
        if (index == set.size())
        {
            res.insert(curr);
            return;
        }
        recursive_power_set(res, set, index + 1, curr);
        curr.insert(set[index]);
        recursive_power_set(res, set, index + 1, curr);
        curr.remove(set[index]);
    }

    template <typename T>
    u_set<u_set<T>> u_set<T>::power_set()
    {
        u_set<u_set<T>> result;
        u_set<T> empty;
        result.insert(empty);
        u_set<T> curr;
        // Find all subsets of the set
        recursive_power_set(result, *this, 0, curr);
        return result;
    }
}

#endif