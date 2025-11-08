#pragma once
#include <string>

namespace cpputils
{
    constexpr int charToInt(char c)
    {
        return c - '0';
    }
    constexpr int strToInt(std::string s)
    {
        return charToInt(s[0]);
    }
    template <int left, int right>
    struct Equal
    {
        static constexpr bool result = left == right;
    };
}