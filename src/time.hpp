#ifndef TIME_HPP
#define TIME_HPP
#include <iostream>

namespace novokhatskiy {

    struct Time {
        unsigned short hours;
        unsigned short minutes;
    };

    std::istream& operator>>(std::istream& in, Time& time);
    std::ostream& operator<<(std::ostream& out, const Time& time);
}

#endif
