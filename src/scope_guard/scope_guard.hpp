#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP
#include <ios>

namespace novokhatskiy {
    class ScopeGuard
    {
    public:
        explicit ScopeGuard(std::basic_ios< char >& c);
        ~ScopeGuard();
    private:
        std::basic_ios< char >& _s;
        std::streamsize _precision;
        std::basic_ios< char >::fmtflags _flags;
    };
}

#endif
