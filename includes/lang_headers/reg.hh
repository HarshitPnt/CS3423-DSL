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
} // namespace fsm
#endif