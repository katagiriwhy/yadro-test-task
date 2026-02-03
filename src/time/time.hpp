#ifndef TIME_HPP
#define TIME_HPP
#include <iostream>

namespace novokhatskiy {

    struct Time {
        unsigned short hours;
        unsigned short minutes;

        bool operator<(const Time& other) const;
        bool operator>(const Time& other) const;
        bool operator<=(const Time& other) const;
        bool operator>=(const Time& other) const;
        bool operator!=(const Time& other) const;
        bool operator==(const Time& other) const;
    };

    std::istream& operator>>(std::istream& in, Time& time);
    std::ostream& operator<<(std::ostream& out, const Time& time);
}

#endif
