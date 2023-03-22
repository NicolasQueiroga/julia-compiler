#pragma once

#include <iostream>
#include <variant>

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const std::variant<T1, T2> &v)
{
    std::visit([&os](const auto &value)
               { os << value; },
               v);
    return os;
}
