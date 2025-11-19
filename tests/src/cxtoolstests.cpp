#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>
#include <vector>
#include "cxtools.h"
#include "doctest/doctest.h"

using std::string;
using namespace cpputils;

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