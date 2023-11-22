#include "../../includes/lang_headers/reg.hh"

namespace fsm
{
    regex::regex(std::string reg)
    {
        this->str = reg;
        this->valid = regcomp(&(this->reg), str.c_str(), 0);
    }

    regex::~regex()
    {
        regfree(&(this->reg));
    }

    bool regex::simulate(std::string str)
    {
        return regexec(&(this->reg), str.c_str(), 0, NULL, 0) == 0;
    }

    bool regex::is_valid()
    {
        return this->valid == 0;
    }
} // namespace fsm