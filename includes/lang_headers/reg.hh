// defines a regex class
// header guard
#ifndef __reg_hh__
#define __reg_hh__
#include <string>
#include <regex.h>

namespace fsm
{
    // Incomplete
    class regex
    {
    public:
        regex_t reg;
        std::string str;
        bool valid;
        bool simulate(std::string);
        bool is_valid();
        ~regex();
        regex(std::string);
    };

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
        if(this->valid == 0)
            return false;
        return regexec(&(this->reg), str.c_str(), 0, NULL, 0) == 0;
    }

    bool regex::is_valid()
    {
        return this->valid == 0;
    }
} // namespace fsm
#endif