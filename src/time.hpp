#ifndef TIME_HPP
#define TIME_HPP
#include <iostream>

namespace novokhatskiy {

    struct Time {
        unsigned char minutes;
        unsigned char hours;
    };

    std::istream& operator>>(std::iostream& in, Time& obj);
}

#endif
