#include "../../includes/lang_headers/nfa.hh"
#include <iostream>
#include <stack>

namespace fsm
{
    std::string epsilon = "\\e";
    nfa::nfa()
    {
        this->q0 = "";
    }

    bool nfa::insert_state(std::string state)
    {
        if (this->Q.find(state) != this->Q.end())
            return false;
        this->Q.insert(state);
        return true;
    }

    bool nfa::remove_state(std::string state)
    {
        if (this->Q.find(state) == this->Q.end())
            return false;
        this->Q.erase(state);
        if (this->q0 == state)
        {
            this->q0 = "";
        }
        if (this->F.find(state) != this->F.end())
        {
            this->F.erase(state);
        }
        for (auto it = this->delta.begin(); it != this->delta.end();)
        {
            if (it->first == state)
            {
                it = this->delta.erase(it);
                continue;
            }
            for (auto a = it->second.begin(); a != it->second.end();)
            {
                if (a->second == state)
                {
                    a = it->second.erase(a);
                }
                else
                {
                    a++;
                }
            }
            it++;
        }
        return true;
    }

    bool nfa::insert_alphabet(std::string alphabet, std::string val)
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
                    throw std::runtime_error("Ambiguous alphabet");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Runtime error: " << e.what() << "\n";
            throw e;
        }
        this->S[alphabet] = val;
        return true;
    }

    std::unordered_map<std::string, std::string> nfa::get_alphabet()
    {
        return this->S;
    }

    bool nfa::remove_alphabet(std::string alphabet)
    {
        if (alphabet.length() == 0)
            return false;
        auto it = this->S.find(alphabet);
        if (it == this->S.end())
            return false;

        this->S.erase(it);
        for (auto &d : this->delta)
        {
            for (auto a : d.second)
            {
                if (a.first == alphabet)
                {
                    d.second.erase(a.first);
                }
            }
        }
        return true;
    }

    bool nfa::insert_final(std::string state)
    {
        if (this->Q.find(state) == this->Q.end())
            return false;
        if (this->F.find(state) != this->F.end())
            return false;
        this->F.insert(state);
        return true;
    }

    bool nfa::is_final(std::string state)
    {
        if (this->Q.find(state) == this->Q.end())
            return false;
        if (this->F.find(state) != this->F.end())
            return true;
        return false;
    }

    bool nfa::remove_final(std::string state)
    {
        if (this->F.find(state) == this->F.end())
            return false;
        this->F.erase(state);
        return true;
    }

    bool nfa::add_transition(std::string state, std::string alphabet, std::string next_state)
    {
        if (this->Q.find(state) == this->Q.end())
            return false;
        if (this->Q.find(next_state) == this->Q.end())
            return false;
        if (alphabet != epsilon && this->S.find(alphabet) == this->S.end())
            return false;
        if (this->delta.find(state) == this->delta.end())
        {
            std::unordered_multimap<std::string, std::string> temp;
            temp.insert({alphabet, next_state});
            this->delta[state] = temp;
        }
        else
        {
            auto it = this->delta[state].equal_range(alphabet);
            for (auto i = it.first; i != it.second; i++)
            {
                if (i->second == next_state)
                    return false;
            }
            this->delta[state].insert({alphabet, next_state});
        }
        return true;
    }

    bool nfa::remove_transition(std::string state, std::string alphabet, std::string next_state)
    {
        if (this->Q.find(state) == this->Q.end())
            return false;
        if (this->Q.find(next_state) == this->Q.end())
            return false;
        if (alphabet != epsilon && this->S.find(alphabet) == this->S.end())
            return false;
        if (this->delta.find(state) == this->delta.end())
            return false;
        auto it = this->delta[state].equal_range(alphabet);
        for (auto i = it.first; i != it.second; i++)
        {
            if (i->second == next_state)
            {
                this->delta[state].erase(i);
                return true;
            }
        }
        return false;
    }

    bool nfa::change_start(std::string state)
    {
        if (state.length() == 0)
            return false;
        if (this->Q.find(state) == this->Q.end())
            return false;
        this->q0 = state;
        return true;
    }

    std::string nfa::get_start()
    {
        return this->q0;
    }

    nfa::~nfa()
    {
        this->Q.clear();
        this->S.clear();
        this->delta.clear();
        this->F.clear();
    }

    std::unordered_map<std::string, std::set<std::string>> nfa::eClosure()
    {
        std::unordered_map<std::string, std::set<std::string>> closure;
        for (auto state : this->Q)
        {
            std::set<std::string> temp;
            closure[state] = temp;
        }
        for (auto state : this->Q)
        {
            std::set<std::string> visited;
            std::stack<std::string> stack;
            stack.push(state);
            while (!stack.empty())
            {
                std::string current_state = stack.top();
                stack.pop();
                if (visited.find(current_state) != visited.end())
                    continue;
                visited.insert(current_state);
                closure[state].insert(current_state);
                auto it = this->delta[current_state].equal_range(epsilon);
                for (auto i = it.first; i != it.second; i++)
                {
                    stack.push(i->second);
                }
            }
        }
        return closure;
    }

    std::unordered_set<std::string> nfa::get_reachable(std::string state, std::string alphabet)
    {
        std::unordered_set<std::string> reachable;
        std::unordered_set<std::string> visited;
        std::stack<std::string> stack;
        stack.push(state);
        while (!stack.empty())
        {
            std::string current_state = stack.top();
            stack.pop();
            if (visited.find(current_state) != visited.end())
                continue;
            visited.insert(current_state);
            auto it = this->delta[current_state].equal_range(alphabet);
            for (auto i = it.first; i != it.second; i++)
            {
                stack.push(i->second);
                reachable.insert(i->second);
            }
        }
        return reachable;
    }

    bool nfa::simulate(std::string input)
    {
        // if (this->q0.length() == 0)
        //     return false;
        // std::unordered_set<std::string> current_states;
        // std::unordered_set<std::string> next_states;
        // current_states.insert(this->q0);
        // for (auto i : input)
        // {
        //     for (auto state : current_states)
        //     {
        //         auto it = this->delta[state].equal_range(std::string(1, i));
        //         for (auto j = it.first; j != it.second; j++)
        //         {
        //             next_states.insert(j->second);
        //         }
        //     }
        //     current_states = next_states;
        //     next_states.clear();
        // }
        // for (auto i : current_states)
        // {
        //     if (this->F.find(i) != this->F.end())
        //         return true;
        // }
        // return false;
    }

    void nfa::out()
    {
        std::cout << "Q : ";
        for (auto i : this->Q)
        {
            std::cout << i << " ";
        }
        std::cout << "\n";
        std::cout << "S : ";
        for (auto i : this->S)
        {
            std::cout << i.first << " ";
        }
        std::cout << "\n";
        std::cout << "q0 : " << this->q0 << "\n";
        std::cout << "F : ";
        for (auto i : this->F)
        {
            std::cout << i << " ";
        }
        std::cout << "\n";
        std::cout << "delta : \n";
        for (auto i : this->delta)
        {
            std::cout << i.first << " : ";
            for (auto j : i.second)
            {
                std::cout << "(" << j.first << "," << j.second << ") ";
            }
            std::cout << "\n";
        }
    }

    nfa* nfa::operator!()
    {
        nfa *temp = new nfa();
        temp->Q = this->Q;
        temp->S = this->S;
        temp->q0 = this->q0;
        temp->F = this->F;
        for (auto i : this->delta)
        {
            for (auto j : i.second)
            {
                temp->delta[j.second].insert({j.first, i.first});
            }
        }
        return temp;
    }

} // namespace fsm