#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>
#include <vector>
#include <sstream>
#include "cxtools.h"
#include "stringutils.h"
#include "doctest/doctest.h"

using namespace cpputils;
using std::string;

static_assert(std::input_iterator<SplitIterator>);
constexpr std::vector<string> cxparts() { return split("1,2,3", ","); }

TEST_SUITE("Constexpr Split")
{
    TEST_CASE("Comma Separated List")
    {
        string line = "one,two,three,four,five";
        auto results = split(line, ',');
        REQUIRE_EQ(5, results.size());
        REQUIRE_EQ("one",results[0]);
        REQUIRE_EQ("two", results[1]);
        REQUIRE_EQ("three", results[2]);
        REQUIRE_EQ("four", results[3]);
        REQUIRE_EQ("five", results[4]);
    }
    TEST_CASE("Empty String")
    {
        string line = "";
        auto results = split(line, ',');
        REQUIRE_EQ(0, results.size());
    }
    TEST_CASE("Empty Delim")
    {
        string line = "abcd";
        auto results = split(line, "");
        REQUIRE_EQ(1, results.size());
        REQUIRE_EQ(line, results[0]);
    }
    TEST_CASE("wide delim")
    {
        string line = "one - two - three - four - five";
        auto results = split(line, " - ");
        REQUIRE_EQ(5, results.size());
        REQUIRE_EQ("one",results[0]);
        REQUIRE_EQ("two", results[1]);
        REQUIRE_EQ("three", results[2]);
        REQUIRE_EQ("four", results[3]);
        REQUIRE_EQ("five", results[4]);
    }
    TEST_CASE("wide delim with partial matches")
    {
        string line = "twenty-one lbs - twenty-two lbs - twenty-three lbs - twenty-four lbs - twenty-five lbs";
        auto results = split(line, " - ");
        REQUIRE_EQ(5, results.size());
        REQUIRE_EQ("twenty-one lbs",results[0]);
        REQUIRE_EQ("twenty-two lbs", results[1]);
        REQUIRE_EQ("twenty-three lbs", results[2]);
        REQUIRE_EQ("twenty-four lbs", results[3]);
        REQUIRE_EQ("twenty-five lbs", results[4]);
    }
    TEST_CASE("single delim with no data")
    {
        string line = ",";
        auto results = split(line, ',');
        REQUIRE_EQ(2, results.size());
        REQUIRE_EQ("", results[0]);
        REQUIRE_EQ("", results[1]);
    }
    TEST_CASE("all delims")
    {
        string line = ",,,";
        auto results = split(line, ',');
        REQUIRE_EQ(4, results.size());
        for(string s : results)
        {
            REQUIRE_EQ("", s);
        }
    }
    TEST_CASE("all wide delims")
    {
        string line = " -  -  - ";
        auto results = split(line, " - ");
        REQUIRE_EQ(4, results.size());
        for(string s : results)
        {
            REQUIRE_EQ("", s);
        }
    }
    TEST_CASE("split is constexpr")
    {
        REQUIRE(Equal<3, cxparts().size()>::result);
        REQUIRE(Equal<1, strToInt(cxparts()[0])>::result);
        REQUIRE(Equal<2, strToInt(cxparts()[1])>::result);
        REQUIRE(Equal<3, strToInt(cxparts()[2])>::result);
    }
}

TEST_SUITE("Stream Split")
{
    TEST_CASE("Comma Separated List")
    {
        string line = "one,two,three,four,five";
        std::stringstream stream(line);
        auto iter = split(stream, ',');
        REQUIRE_EQ("one",*iter);
        ++iter;
        REQUIRE_EQ("two", *iter);
        ++iter;
        REQUIRE_EQ("three", *iter);
        ++iter;
        REQUIRE_EQ("four", *iter);
        ++iter;
        REQUIRE_EQ("five", *iter);

        REQUIRE_EQ(StreamSplitIterator(), iter);
    }
    TEST_CASE("Empty String")
    {
        string line = "";
        std::stringstream stream(line);
        auto iter = split(stream, ',');
        REQUIRE_EQ(StreamSplitIterator(), iter);
    }
    TEST_CASE("Empty Delim")
    {
        string line = "abcd";
        std::stringstream stream(line);
        auto iter = split(stream, "");
        REQUIRE_EQ(line, *iter);
        REQUIRE_EQ(StreamSplitIterator(), iter);
    }
    TEST_CASE("wide delim")
    {
        string line = "one - two - three - four - five";
        std::stringstream stream(line);
        auto iter = split(stream, " - ");
        REQUIRE_EQ("one",*iter);
        ++iter;
        REQUIRE_EQ("two", *iter);
        ++iter;
        REQUIRE_EQ("three", *iter);
        ++iter;
        REQUIRE_EQ("four", *iter);
        ++iter;
        REQUIRE_EQ("five", *iter);

        REQUIRE_EQ(StreamSplitIterator(), iter);
    }
    TEST_CASE("wide delim with partial matches")
    {
        string line = "twenty-one lbs - twenty-two lbs - twenty-three lbs - twenty-four lbs - twenty-five lbs";
        std::stringstream stream(line);
        auto iter = split(stream, " - ");
        REQUIRE_EQ("twenty-one lbs",*iter);
        ++iter;
        REQUIRE_EQ("twenty-two lbs", *iter);
        ++iter;
        REQUIRE_EQ("twenty-three lbs", *iter);
        ++iter;
        REQUIRE_EQ("twenty-four lbs", *iter);
        ++iter;
        REQUIRE_EQ("twenty-five lbs", *iter);

        REQUIRE_EQ(StreamSplitIterator(), iter);
    }
    TEST_CASE("single delim with no data")
    {
        string line = ",";
        std::stringstream stream(line);
        auto iter = split(stream, ',');
        REQUIRE_EQ("", *iter);
        ++iter;
        REQUIRE_EQ("", *iter);
        REQUIRE_EQ(StreamSplitIterator(), iter);
    }
    TEST_CASE("all delims")
    {
        string line = ",,,";
        std::stringstream stream(line);
        auto iter = split(stream, ',');
        for(;iter != StreamSplitIterator(); ++iter)
        {
            REQUIRE_EQ("", *iter);
        }
    }
    TEST_CASE("all wide delims")
    {
        string line = " -  -  -  - ";
        std::stringstream stream(line);
        auto iter = split(stream, " - ");
        for(;iter != StreamSplitIterator(); ++iter)
        {
            REQUIRE_EQ("", *iter);
        }
    }
    TEST_CASE("split is constexpr")
    {
        REQUIRE(Equal<3, cxparts().size()>::result);
        REQUIRE(Equal<1, strToInt(cxparts()[0])>::result);
        REQUIRE(Equal<2, strToInt(cxparts()[1])>::result);
        REQUIRE(Equal<3, strToInt(cxparts()[2])>::result);
    }
}