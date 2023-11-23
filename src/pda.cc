#include "../includes/lang_headers/pda.hh"#include "../includes/lang_headers/pda.hh"
#include <iostream>

namespace fsm
{
    pda::pda()
    {
        this->q0 = "";
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
        return true;
    }
    bool pda::add_transition(std::string state, std::string alphabet, std::string stack, std::string next_state, std::string next_stack)
    {
        
    }
}