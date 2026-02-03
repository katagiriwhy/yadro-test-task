#include "scope_guard.hpp"

novokhatskiy::ScopeGuard::ScopeGuard(std::basic_ios<char> &c) :
    _s(c),
    _precision(c.precision()),
    _flags(c.flags())
{}

novokhatskiy::ScopeGuard::~ScopeGuard() {
    _s.precision(_precision);
    _s.flags(_flags);
}
