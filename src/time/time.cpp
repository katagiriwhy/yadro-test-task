#include "time.hpp"
#include <iomanip>
#include <regex>
#include "scope_guard/scope_guard.hpp"

std::istream &novokhatskiy::operator>>(std::istream &in, novokhatskiy::Time &time) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    std::string strTime = "";
    in >> strTime;
    std::regex regex("^([01][0-9]|2[0-3]):([0-5][0-9])$");
    std::smatch match;

    if (!std::regex_match(strTime, match, regex)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    time.hours = std::stoi(match[1].str());
    time.minutes = std::stoi(match[2].str());

    return in;
}

std::ostream &novokhatskiy::operator<<(std::ostream &out, const novokhatskiy::Time &time) {
    novokhatskiy::ScopeGuard scopeGuard(out);
    out << std::setfill('0') << std::setw(2) << time.hours << ':' << std::setw(2) << time.minutes;
    return out;
}

bool novokhatskiy::Time::operator<(const novokhatskiy::Time &other) const {
    return (this->hours < other.hours) || ((this->hours == other.hours) && (this->minutes < other.minutes));
}

bool novokhatskiy::Time::operator>(const novokhatskiy::Time &other) const {
    return other < *this;
}

bool novokhatskiy::Time::operator!=(const novokhatskiy::Time &other) const {
    return !(*this == other);
}

bool novokhatskiy::Time::operator==(const novokhatskiy::Time &other) const {
    return !(*this < other) && !(*this > other);
}

bool novokhatskiy::Time::operator<=(const novokhatskiy::Time &other) const {
    return !(*this > other);
}

bool novokhatskiy::Time::operator>=(const novokhatskiy::Time &other) const {
    return !(*this < other);
}

novokhatskiy::Time novokhatskiy::Time::operator-(const novokhatskiy::Time &other) const {
    unsigned short newHours = 0;
    unsigned short newMinutes = 0;
    if (minutes - other.minutes < 0)
    {
        newHours = hours - other.hours - 1;
        newMinutes = minutes - other.minutes + 60;
    }
    else
    {
        newHours = hours - other.hours;
        newMinutes = minutes - other.minutes;
    }
    if (newHours < 0)
    {
        newHours = 23;
    }
    return Time{newHours, newMinutes};
}

novokhatskiy::Time novokhatskiy::Time::operator+(const novokhatskiy::Time &other) const {
    unsigned short newHours = 0;
    unsigned short newMinutes = 0;
    if (minutes + other.minutes > 59)
    {
        newHours = hours + other.hours + 1;
        newMinutes = minutes + other.minutes - 60;
    }
    else
    {
        newHours = hours + other.hours;
        newMinutes = minutes + other.minutes;
    }
    if (newHours > 23)
    {
        newHours = 0;
    }
    return Time{newHours, newMinutes};
}

