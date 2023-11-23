#include "../../includes/lang_headers/reg.hh"
#include <iostream>

namespace fsm
{

    regex::regex(const std::string reg)
    {
        this->str = reg;
        this->valid = regcomp(&(this->reg), str.c_str(), 0);
    }

    regex::~regex()
    {
        regfree(&(this->reg));
    }

    bool regex::simulate(const std::string str)
    {
        if (this->valid == 0)
            return false;
        return regexec(&(this->reg), str.c_str(), 0, NULL, 0) == 0;
    }

    bool regex::is_valid()
    {
        return this->valid == 0;
    }

} // namespace fsm