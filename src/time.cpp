#include "time.hpp"
#include <iomanip>

std::istream &novokhatskiy::operator>>(std::istream &in, novokhatskiy::Time &time) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    unsigned int hours, minutes;
    char colon;

    if (in >> hours >> colon >> minutes && colon == ':' && hours < 24 && minutes < 60) {
        time.hours = static_cast<unsigned short>(hours);
        time.minutes = static_cast<unsigned short>(minutes);
        return in;
    }

    in.setstate(std::ios::failbit);

    return in;
}

std::ostream &novokhatskiy::operator<<(std::ostream &out, const novokhatskiy::Time &time) {
    out << std::setfill('0') << std::setw(2) << time.hours << ':' << std::setw(2) << time.minutes << '\n';
    return out;
}
