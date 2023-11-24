#include "../../includes/lang_headers/pda.hh"
#include <iostream>
#include <stack>
#include <vector>
#include <queue>

namespace fsm
{
    std::string epsilon = "\\e";
    pda::pda()
    {
        this->q0 = "";
        S.insert({epsilon, epsilon});
        T.insert({epsilon, epsilon});
    }

    pda::~pda()
    {
        this->Q.clear();
        this->S.clear();
        this->F.clear();
        this->T.clear();
        this->delta.clear();
        q0 = "";
    }

    bool pda::change_start(std::string state)
    {
        if (state.length() == 0)
            return false;
        if (this->Q.find(state) == this->Q.end())
            return false;
        this->q0 = state;
        return true;
    }

    bool pda::insert_state(std::string state)
    {
        if (state.length() == 0)
            return false;
        if (this->Q.find(state) != this->Q.end())
            return false;
        this->Q.insert(state);
        return true;
    }

    bool pda::remove_state(std::string state)
    {
        if (state.length() == 0)
            return false;
        if (this->Q.find(state) == this->Q.end())
            return false;
        if (this->q0 == state)
            this->q0 = "";
        if (this->F.find(state) != this->F.end())
            this->F.erase(state);
        for (auto it = this->delta.begin(); it != this->delta.end();)
        {
            if (it->first == state)
            {
                it = this->delta.erase(it);
                continue;
            }
            for (auto listItem = it->second.begin(); listItem != it->second.end();)
            {
                if ((*listItem)[2] == state)
                {
                    listItem = it->second.erase(listItem);
                    continue;
                }
                listItem++;
            }
            if (it->second.size() == 0)
                it = this->delta.erase(it);
            else
                it++;
        }
    }

    bool pda::insert_final(std::string state)
    {
        if (state.length() == 0)
            return false;
        if (this->Q.find(state) == this->Q.end())
            return false;
        this->F.insert(state);
        return true;
    }

    bool pda::insert_alphabet(std::string alphabet, std::string val)
    {
        if (alphabet.length() == 0 || val.length() == 0)
            return false;
        if (this->S.find(alphabet) != this->S.end())
            return false;
        try
        {
            for (auto d : this->S)
            {
                if (val.compare(0, d.second.length(), d.second) == 0 || d.second.compare(0, val.length(), val) == 0)
                {
                    throw std::runtime_error("Ambiguous alphabet");
                }
            }
        }
        catch (std::exception &e)
        {
            std::cerr << "Runtime Error: " << e.what() << '\n';
            throw e;
        }
        this->S[alphabet] = val;
        return true;
    }

    bool pda::remove_alphabet(std::string alphabet)
    {
        if (alphabet.length() == 0)
            return false;
        if (this->S.find(alphabet) == this->S.end())
            return false;
        for (auto it = this->delta.begin(); it != this->delta.end();)
        {
            for (auto listItem = it->second.begin(); listItem != it->second.end();)
            {
                if ((*listItem)[0] == alphabet)
                {
                    listItem = it->second.erase(listItem);
                    continue;
                }
                listItem++;
            }
            if (it->second.size() == 0)
                it = this->delta.erase(it);
            else
                it++;
        }
        this->S.erase(alphabet);
        return true;
    }

    bool pda::insert_stack_symbol(std::string alphabet, std::string val)
    {
        if (alphabet.length() == 0 || val.length() == 0)
            return false;
        if (this->T.find(alphabet) != this->T.end())
            return false;
        try
        {
            for (auto d : this->T)
            {
                if (val.compare(0, d.second.length(), d.second) == 0 || d.second.compare(0, val.length(), val) == 0)
                {
                    throw std::runtime_error("Ambiguous alphabet");
                }
            }
        }
        catch (std::exception &e)
        {
            std::cerr << "Runtime Error: " << e.what() << '\n';
            throw e;
        }
        this->T[alphabet] = val;
        return true;
    }

    bool pda::remove_stack_symbol(std::string alphabet)
    {
        if (alphabet.length() == 0)
            return false;
        if (this->T.find(alphabet) == this->T.end())
            return false;
        for (auto it = this->delta.begin(); it != this->delta.end();)
        {
            for (auto listItem = it->second.begin(); listItem != it->second.end();)
            {
                if ((*listItem)[1] == alphabet || (*listItem)[3] == alphabet)
                {
                    listItem = it->second.erase(listItem);
                    continue;
                }
                listItem++;
            }
            if (it->second.size() == 0)
                it = this->delta.erase(it);
            else
                it++;
        }
        this->T.erase(alphabet);
        return true;
    }

    bool pda::insert_transition(std::string state, std::string alphabet, std::string stack_top, std::string next_state, std::string stack_push)
    {
        if (state.length() == 0 || alphabet.length() == 0 || next_state.length() == 0 || stack_top.length() == 0 || stack_push.length() == 0)
            return false;
        if (this->Q.find(state) == this->Q.end())
            return false;
        if (this->Q.find(next_state) == this->Q.end())
            return false;
        if (this->S.find(alphabet) == this->S.end())
            return false;
        if (this->T.find(stack_top) == this->T.end())
            return false;
        if (this->T.find(stack_push) == this->T.end())
            return false;
        this->delta[state].insert({alphabet, stack_top, next_state, stack_push});
        return true;
    }

    bool pda::simulate_helper(std::string state, int index, std::set<std::pair<int, std::string>> &vis, std::stack<std::string> &stack, std::vector<std::string> &input_vec)
    {
        std::cout << "State: " << state << " Index: " << index << " Stack Size: " << stack.size() << '\n';
        bool ans = false;
        if (index == input_vec.size())
        {
            if (this->F.find(state) != this->F.end() && stack.empty())
                return true;
            if (this->delta.find(state) == this->delta.end())
                return false;
            auto d = this->delta[state];
            for (auto it = d.begin(); it != d.end(); it++)
            {
                if ((*it)[0] == epsilon)
                {
                    if ((*it)[1] == epsilon)
                    {
                        if ((*it)[3] != epsilon)
                            stack.push((*it)[3]);
                        if (vis.find({index, (*it)[2]}) != vis.end())
                            return false;
                        vis.insert({index, (*it)[2]});
                        ans = this->simulate_helper((*it)[2], index, vis, stack, input_vec);
                        vis.erase({index, (*it)[2]});
                        if ((*it)[3] != epsilon)
                            stack.pop();
                    }
                    else if ((*it)[1] == stack.top())
                    {
                        if ((*it)[3] != epsilon)
                            stack.push((*it)[3]);
                        if (vis.find({index, (*it)[2]}) != vis.end())
                            return false;
                        vis.insert({index, (*it)[2]});
                        ans = this->simulate_helper((*it)[2], index, vis, stack, input_vec);
                        vis.erase({index, (*it)[2]});
                        if ((*it)[3] != epsilon)
                            stack.pop();
                    }
                }
                if (ans)
                    return true;
            }
            return ans;
        }

        auto d = this->delta[state];

        for (auto it = d.begin(); it != d.end(); it++)
        {
            if ((*it)[0] == epsilon || (*it)[0] == input_vec[index])
            {
                if ((*it)[0] != epsilon)
                    index++;

                if ((*it)[1] == epsilon)
                {
                    if ((*it)[3] != epsilon)
                        stack.push((*it)[3]);
                    if (vis.find({index, (*it)[2]}) != vis.end())
                        return false;
                    vis.insert({index, (*it)[2]});
                    ans = this->simulate_helper((*it)[2], index, vis, stack, input_vec);
                    vis.erase({index, (*it)[2]});
                    if ((*it)[3] != epsilon)
                        stack.pop();
                }

                else if ((*it)[1] == stack.top())
                {
                    stack.pop();
                    if ((*it)[3] != epsilon)
                        stack.push((*it)[3]);
                    if (vis.find({index, (*it)[2]}) != vis.end())
                        return false;
                    vis.insert({index, (*it)[2]});
                    ans = this->simulate_helper((*it)[2], index, vis, stack, input_vec);
                    vis.erase({index, (*it)[2]});
                    if ((*it)[3] != epsilon)
                        stack.pop();

                    stack.push((*it)[1]);
                }
                if (ans)
                    return true;

                if ((*it)[0] != epsilon)
                    index--;
            }
        }

        return ans;
    }

    bool pda::simulate(std::string input)
    {
        std::vector<std::string> input_vec;
        std::string temp = "";
        for (auto c : input)
        {
            temp += c;
            if (this->S.find(temp) != this->S.end())
            {
                input_vec.push_back(temp);
                temp = "";
            }
        }
        if (temp.length() != 0)
            return false;

        std::stack<std::string> stack;
        std::set<std::pair<int, std::string>> vis;
        std::cout << input_vec.size() << '\n';
        vis.insert({0, this->q0});
        return this->simulate_helper(this->q0, 0, vis, stack, input_vec);
    }

    void pda::out()
    {
        std::cout << "Starting state : ( q0 )\n"
                  << this->q0 << '\n';

        std::cout << "\nStates : ( Q )\n";
        for (auto q : this->Q)
            std::cout << q << " ";
        std::cout << '\n';

        std::cout << "\nAlphabets : ( Alphabet : Value )\n";
        for (auto s : this->S)
            std::cout << s.first << " : " << s.second << '\n';

        std::cout << "\nStack Symbols : ( Alphabet : Value )\n";
        for (auto s : this->T)
            std::cout << s.first << " : " << s.second << '\n';

        std::cout << "\nFinal States : ( F )\n";
        for (auto f : this->F)
            std::cout << f << " ";
        std::cout << '\n';

        std::cout << "\nTransition Function : ( Q x Alphabet x Stack-Pop ) -> ( Q x Stack-Push )\n";
        for (auto d : this->delta)
        {
            for (auto a : d.second)
            {
                std::cout << "( " << d.first << " x " << a[0] << " x " << a[1] << " ) --> ( " << a[2] << " x " << a[3] << " )\n";
            }
        }

        return;
    }
}