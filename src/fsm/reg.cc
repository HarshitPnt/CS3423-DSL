#include "../../includes/lang_headers/reg.hh"
#include <iostream>
#include <stack>
namespace fsm
{

    regex::regex(const std::string str)
    {
        this->str = str;
        
        this->valid = regcomp(&(this->reg), this->str.c_str(), REG_EXTENDED);
    }

    regex::~regex()
    {
        regfree(&(this->reg));
    }

    bool regex::simulate(const std::string str)
    {
        if (this->valid != 0)
            return false;
        return (regexec(&(this->reg), str.c_str(), 0, NULL, 0) == 0);
    }

    bool regex::is_valid()
    {
        return (this->valid == 0);
    }

    std::string regex::to_postfix(){
        std::string postfix = "";
        std::stack<char> st;
        
    }
} // namespace fsm