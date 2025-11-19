#pragma once
#include <string>
#include <stdexcept>

namespace cpputils
{
    constexpr bool isDigit(char c, int radix = 10)
    {
        if(radix <= 10)
        {
            return c >= '0' && c < ('0' + radix);
        }
        else
        {
            return
                c >= '0' && c <= '9'
                ||
                c >= 'A' && c < 'A'+(radix-10)
                ||
                c >= 'a' && c < 'a'+(radix-10);
        }
    }
    constexpr int charToInt(char c, int radix = 10)
    {
        if(!isDigit(c, radix)) throw std::invalid_argument(std::string("\"")+c+std::string("\" is not a digit"));
        if(radix <= 10)
        {
            return c - '0';
        }
        else
        {
            if(c >= '0' && c <= '9') return c - '0';
            else if(c >= 'A' && c <= 'Z') return c - 'A' + 10;
            else if(c >= 'a' && c <= 'z') return c - 'a' + 10;
            // this should never happen.
            else throw std::logic_error("Invalid char to int");
        }
    }
    constexpr int strToInt(std::string s, int radix = 10)
    {
        if(s.length() == 0) throw std::invalid_argument("empty string");
        else if(s.length() == 1) return charToInt(s[0], radix);
        else
        {
            int result = 0;
            int sign, start;
            if(s[0] == '-')
            {
                sign = -1;
                start = 1;
            }
            else
            {
                sign = 1;
                start = 0;
            }
            // skip leading 0s
            while(start < s.length() && s[start] == '0')
            {
                ++start;
            }
            for(int i = start; i < s.length(); ++i)
            {
                result *= radix;
                result += charToInt(s[i], radix);
            }
            return result * sign;
        }
    }
    template <int left, int right>
    struct Equal
    {
        static constexpr bool result = left == right;
    };
}