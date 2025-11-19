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
            else if(c >= 'A' && c < 'A'+(radix-10)) return c - 'A' + 10;
            else if(c >= 'a' && c < 'a'+(radix-10)) return c - 'a' + 10;
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
    char intToChar(int i, int radix = 10)
    {
        if(i < 0 || i >= radix)
        {
            throw std::invalid_argument("i is not a single digit");
        }

        if(radix <= 10)
        {
            return '0' + i;
        }
        else
        {
            if(i >= 0 && i < 10)
            {
                return '0' + i;
            }
            else
            {
                return 'A' + (i - 10);
            }
        }
    }
    constexpr std::string intToStr(int number, int radix = 10)
    {
        // special case for 0
        if(number == 0)
        {
            return std::string(1, '0');
        }

        bool neg = number < 0;
        int offset = neg ? 1 : 0;
        if(neg) number *= -1;

        // first, count the digits
        int num = number;
        int digits = 0;
        while(num > 0)
        {
            num /= radix;
            ++digits;
        }
        // create a string of sifficient length, plus one if negative
        std::string result(digits + offset, '0');
        // if negative, add a minus
        if(neg) result[0] = '-';

        // place digits into the string in reverse order
        num = number;
        for(int i = digits-1+offset; i >= offset; --i)
        {
            int digit = num % radix;
            result[i] = intToChar(digit, radix);
            num /= radix;
        }

        return result;
    }
    template <int left, int right>
    struct Equal
    {
        static constexpr bool result = left == right;
    };
}