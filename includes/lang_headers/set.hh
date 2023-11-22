// Purpose: Provides set and unordered_set classes.
// header guards
#ifndef __set_hh__
#define __set_hh__
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>

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
#endif