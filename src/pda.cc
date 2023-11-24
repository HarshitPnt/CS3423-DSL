#include "../includes/lang_headers/pda.hh"
#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>

namespace fsm
{
    pda::pda()
    {
        this->q0 = "";
        this->insert_stack("\e", "\e");
        this->insert_alphabet("\e", "\e");
    }

    bool pda::insert_state(std::string state)
    {
        if (this->Q.find(state) == this->Q.end())
        {
            this->Q.insert(state);
            return true;
        }
        return false;
    }

    bool pda::remove_state(std::string state)
    {
        if (this->Q.find(state) != this->Q.end())
        {
            this->Q.erase(state);
            if (this->q0 == state)
                this->q0 = "";
            if (this->F.find(state) != this->F.end())
                this->F.erase(state);
            for (auto d = this->delta.begin(); d != this->delta.end();)
            {
                for (auto a = d->second.begin(); a != d->second.end();)
                {
                    if (a->first.first == state || a->second.first == state)
                        d->second.erase(a->first);
                    else
                        a++;
                }
                if (d->second.size() == 0)
                    d = this->delta.erase(d);
                else
                    d++;
            }
            return true;
        }
        return false;
    }

    bool pda::insert_alphabet(std::string alphabet, std::string val)
    {
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
        if (this->S.find(alphabet) == this->S.end())
            return false;
        this->S.erase(alphabet);
        for (auto d = this->delta.begin(); d != this->delta.end();)
        {
            for (auto a = d->second.begin(); a != d->second.end();)
            {
                if (a->first.first == alphabet)
                    d->second.erase(a->first);
                else
                    a++;
            }
            if (d->second.size() == 0)
                d = this->delta.erase(d);
            else
                d++;
        }
        return true;
    }

    bool pda::insert_stack(std::string alphabet, std::string val)
    {
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

    bool pda::remove_stack(std::string alphabet)
    {
        if (this->T.find(alphabet) == this->T.end())
            return false;
        this->T.erase(alphabet);
        for (auto d = this->delta.begin(); d != this->delta.end();)
        {
            for (auto a = d->second.begin(); a != d->second.end();)
            {
                if (a->first.second == alphabet || a->second.second == alphabet)
                    d->second.erase(a->first);
                else
                    a++;
            }
            if (d->second.size() == 0)
                d = this->delta.erase(d);
            else
                d++;
        }
        return true;
    }

    bool pda::add_transition(std::string state, std::string alphabet, std::string stack, std::string next_state, std::string next_stack)
    {
        if (this->Q.find(state) == this->Q.end() || this->Q.find(next_state) == this->Q.end() || this->S.find(alphabet) == this->S.end() || this->T.find(stack) == this->T.end() || this->T.find(next_stack) == this->T.end())
            return false;
        if (this->delta.find(state) == this->delta.end())
            this->delta[state].insert({{alphabet, stack}, {next_state, next_stack}});
        else
        {
            for (auto d : this->delta[state])
            {
                if (d.first.first == alphabet && d.first.second == stack && d.second.first == next_state && d.second.second == next_stack)
                    return false;
                else
                    this->delta[state].insert({{alphabet, stack}, {next_state, next_stack}});
            }
        }
        return true;
    }

    bool pda::remove_transition(std::string state, std::string alphabet, std::string stack, std::string next_state, std::string next_stack)
    {
        if (this->Q.find(state) == this->Q.end() || this->Q.find(next_state) == this->Q.end() || this->S.find(alphabet) == this->S.end() || this->T.find(stack) == this->T.end() || this->T.find(next_stack) == this->T.end())
            return false;
        if (this->delta.find(state) == this->delta.end())
            return false;
        else
        {
            for (auto d : this->delta[state])
            {
                if (d.first.first == alphabet && d.first.second == stack && d.second.first == next_state && d.second.second == next_stack)
                {
                    this->delta[state].erase(d.first);
                    return true;
                }
            }
        }
        return false;
    }

    bool pda::change_start(std::string state)
    {
        if (state.length() == 0)
            return false;
        else if (this->Q.find(state) == this->Q.end())
            return false;
        else if (this->q0 == state)
            return false;
        this->q0 = state;
        return true;
    }

    bool pda::insert_final(std::string state)
    {
        if (this->Q.find(state) == this->Q.end())
            return false;
        else if (this->F.find(state) != this->F.end())
            return false;
        this->F.insert(state);
        return true;
    }

    bool pda::remove_final(std::string state)
    {
        if (this->F.find(state) == this->F.end())
            return false;
        this->F.erase(state);
        return true;
    }

    bool pda::simulate_helper(std::vector<std::string> input_vec, int index, std::string current_state, std::stack<std::string> current_stack, std::unordered_multimap<int, std::string> vis)
    {
        if (index == input_vec.size())
        {
            if (this->F.find(current_state) != this->F.end() && current_stack.size() == 0)
                return true;
            else
                return false;
        }
        bool ans = false;
        for (auto d : this->delta[current_state])
        {
            if ((d.first.first == input_vec[index] || d.first.first == "\e") && (d.first.second == current_stack.top() || d.first.second == "\e"))
            {
                if (d.first.second != "\e")
                    current_stack.pop();
                if (d.second.second != "\e")
                    current_stack.push(d.second.second);
                vis.insert({index, current_state});
                ans = ans || simulate_helper(input_vec, index + 1, d.second.first, current_stack, vis);

                auto range = vis.equal_range(index);

                for (auto i = range.first; i != range.second; i++)
                {
                    if (i->second == current_state)
                        vis.erase(i);
                }

                if (ans)
                    return true;
                if (d.second.second != "\e")
                    current_stack.pop();
                if (d.first.second != "\e")
                    current_stack.push(d.first.second);
            }
        }
    }

    bool pda::simulate(std::string input)
    {
        if (this->q0.length() == 0)
        {
            return false;
        }
        auto current_state = this->q0;
        std::stack<std::string> st;
        std::vector<std::string> input_vec;
        auto vis = new std::unordered_multimap<int, std::string>();
        std::string temp = "";
        for (auto i : input)
        {
            temp += i;
            for (auto s : this->S)
            {
                if (temp == s.second)
                {
                    input_vec.push_back(s.first);
                    temp = "";
                    break;
                }
            }
        }
        if (temp.length() != 0)
            return false;
    }

    void pda::out()
    {
        std::cout << "--- PDA ---\n";
        std::cout << "\nStart State ( q0 ):\n"
                  << this->q0 << '\n';
        std::cout << "\nStates ( Q ):\n";
        for (auto q : this->Q)
            std::cout << q << ' ';
        std::cout << '\n';
        std::cout << "\nFinal States ( F ):\n";
        for (auto f : this->F)
            std::cout << f << ' ';
        std::cout << '\n';
        std::cout << "\nInput Alphabet ( Alphabet : Value ):\n";
        for (auto s : this->S)
            std::cout << s.first << ' : ' << s.second << '\n';
        std::cout << '\n';
        std::cout << "Stack Alphabet ( Alphabet : Value ):\n";
        for (auto t : this->T)
            std::cout << t.first << ' : ' << t.second << '\n';
        std::cout << '\n';
        std::cout << "Transition Function ( Q x S x T --> Q x T )\n";
        for (auto d : this->delta)
        {
            for (auto a : d.second)
                std::cout << '( ' << d.first << " , " << a.first.first << " , " << a.first.second << " ) --> ( " << a.second.first << " , " << a.second.second << " )\n";
        }
        std::cout << "------------\n";
    }
}
