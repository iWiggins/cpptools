#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>
#include <vector>
#include <ranges>
#include "cxtools.h"
#include "letters.h"
#include "doctest/doctest.h"

using std::string;
using namespace cpputils;

TEST_SUITE("Letters Tests")
{
    TEST_CASE("Lowercase Letters")
    {
        auto lowercase = lowercase_letters();
        int i = 0;
        for(char letter = 'a'; letter <= 'z'; ++letter)
        {
            REQUIRE_EQ(letter, lowercase[i++]);
        }
    }
    TEST_CASE("Uppercase Letters")
    {
        auto uppercase = uppercase_letters();
        int i = 0;
        for(char letter = 'A'; letter <= 'Z'; ++letter)
        {
            REQUIRE_EQ(letter, uppercase[i++]);
        }
    }
}

TEST_SUITE("isDigit")
{
    TEST_CASE("decimal digits are digits")
    {
        for(char c = 0; c < 127; c++)
        {
            if(c >= '0' && c <= '9')
            {
                REQUIRE(isDigit(c));
            }
            else
            {
                REQUIRE_FALSE(isDigit(c));
            }
        }
    }
    TEST_CASE("hex digits are digits")
    {
        for(char c = 0; c < 127; c++)
        {
            if(c >= '0' && c <= '9')
            {
                REQUIRE(isDigit(c, 16));
            }
            else if(c >= 'A' && c <= 'F')
            {
                REQUIRE(isDigit(c, 16));
            }
            else if(c >= 'a' && c <= 'f')
            {
                REQUIRE(isDigit(c, 16));
            }
            else
            {
                REQUIRE_FALSE(isDigit(c, 16));
            }
        }
    }
    TEST_CASE("binary digits are digits")
    {
        for(char c = 0; c < 127; c++)
        {
            if(c == '0' || c == '1')
            {
                REQUIRE(isDigit(c, 2));
            }
            else
            {
                REQUIRE_FALSE(isDigit(c, 2));
            }
        }
    }
}
TEST_SUITE("strToInt")
{
    TEST_CASE("Empty string throws")
    {
        REQUIRE_THROWS(strToInt(""));
    }
    TEST_CASE("All 0s is 0")
    {
        string str = "0000000000";
        int result = strToInt(str);
        REQUIRE_EQ(0, result);
    }
    TEST_CASE("single dash throws")
    {
        string str = "-";
        REQUIRE_THROWS(strToInt(str));
    }
    TEST_CASE("invalid decimal string throws")
    {
        string str = "12a";
        REQUIRE_THROWS(strToInt(str));
    }
    TEST_CASE("valid decimal string converts")
    {
        string str = "123";
        int result = strToInt(str);
        REQUIRE_EQ(123, result);
    }
    TEST_CASE("negative decimal string converts")
    {
        string str = "-779";
        int result = strToInt(str);
        REQUIRE_EQ(-779, result);
    }
    TEST_CASE("single decimal string converts")
    {
        string str = "9";
        int result = strToInt(str);
        REQUIRE_EQ(9, result);
    }
    TEST_CASE("invalid hex string throws")
    {
        string str = "abg";
        REQUIRE_THROWS(strToInt(str, 16));
    }
    TEST_CASE("valid hex string converts")
    {
        string str = "1Ab";
        int result = strToInt(str, 16);
        REQUIRE_EQ(0x1AB, result);
    }
    TEST_CASE("single hex string converts")
    {
        string str = "C";
        int result = strToInt(str, 16);
        REQUIRE_EQ(12, result);
    }
    TEST_CASE("invalid binary string throws")
    {
        string str = "1012";
        REQUIRE_THROWS(strToInt(str, 2));
    }
    TEST_CASE("valid binary string converts")
    {
        string str = "0111";
        int result = strToInt(str, 2);
        REQUIRE_EQ(7, result);
    }
    TEST_CASE("single binary string converts")
    {
        string str = "1";
        int result = strToInt(str, 2);
        REQUIRE_EQ(1, result);
    }
}
TEST_SUITE("intToStr")
{
    TEST_CASE("0 is 0")
    {
        int i = 0;
        string result = intToStr(i);
        REQUIRE_EQ("0", result);
    }
    TEST_CASE("Decimal digit converts")
    {
        int i = 5;
        string result = intToStr(i);
        REQUIRE_EQ("5", result);
    }
    TEST_CASE("Decimal number converts")
    {
        int i = 123;
        string result = intToStr(i);
        REQUIRE_EQ("123", result);
    }
    TEST_CASE("Negative decimal converts")
    {
        int i = -864;
        string result = intToStr(i);
        REQUIRE_EQ("-864", result);
    }
    TEST_CASE("Hex digit converts")
    {
        int i = 0xC;
        string result = intToStr(i, 16);
        REQUIRE_EQ("C", result);
    }
    TEST_CASE("Hex number converts")
    {
        int i = 0x1AC4;
        string result = intToStr(i, 16);
        REQUIRE_EQ("1AC4", result);
    }
    TEST_CASE("Negative hex converts")
    {
        int i = -0x2FF;
        string result = intToStr(i, 16);
        REQUIRE_EQ("-2FF", result);
    }
    TEST_CASE("Bin digit converts")
    {
        int i = 1;
        string result = intToStr(i, 2);
        REQUIRE_EQ("1", result);
    }
    TEST_CASE("Bin number converts")
    {
        int i = 10;
        string result = intToStr(i, 2);
        REQUIRE_EQ("1010", result);
    }
    TEST_CASE("Negative bin number converts")
    {
        int i = -7;
        string result = intToStr(i, 2);
        REQUIRE_EQ("-111", result);
    }
}
TEST_SUITE("lower-upper")
{
    TEST_CASE("uppercase character becomes lowercase")
    {
        auto uppers = uppercase_letters();
        auto lowers = lowercase_letters();

        for(int i = 0; i < uppers.size(); ++i)
        {
            REQUIRE_EQ(lowers[i], toLower(uppers[i]));
        }
    }

    TEST_CASE("lowercase character becomes uppercase")
    {
        auto uppers = uppercase_letters();
        auto lowers = lowercase_letters();

        for(int i = 0; i < uppers.size(); ++i)
        {
            REQUIRE_EQ(uppers[i], toUpper(lowers[i]));
        }
    }
}