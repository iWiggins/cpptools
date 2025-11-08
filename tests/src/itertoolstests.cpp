#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iterator>
#include <string>
#include <vector>
#include "itertools.h"
#include "doctest/doctest.h"

using namespace cpputils;
using std::string;
using std::vector;

static_assert(std::input_iterator<SingleIter<int>>);
static_assert(std::input_iterator<MergeIter<int, vector<int>::iterator,vector<int>::iterator,vector<int>::iterator,vector<int>::iterator>>);

TEST_SUITE("Iterator Tools")
{
    TEST_CASE("Iterate Two Vectors")
    {
        vector<int> vec1;
        vec1.push_back(1);
        vec1.push_back(2);
        vec1.push_back(3);

        vector<int> vec2;
        vec1.push_back(4);
        vec1.push_back(5);
        vec1.push_back(6);

        auto merge = Merge<int, std::vector<int>::iterator>(
            vec1.begin(),
            vec1.end(),
            vec2.begin(),
            vec2.end());

        int count = 1;
        for(auto a : merge)
        {
            REQUIRE_EQ(count++, a);
        }
        REQUIRE_EQ(count, 7);
    }

    TEST_CASE("Iterate char vector and string")
    {
        vector<char> expected;
        vector<char> left;
        left.push_back('a');
        expected.push_back('a');
        left.push_back('b');
        expected.push_back('b');
        left.push_back('c');
        expected.push_back('c');

        string right = "def";
        expected.push_back('d');
        expected.push_back('e');
        expected.push_back('f');

        auto merge = BiMerge<int, std::vector<char>::iterator, std::string::iterator>(
            left.begin(),
            left.end(),
            right.begin(),
            right.end()
        );

        int count = 0;
        for(auto a : merge)
        {
            char expected = count < 3 ? left[count] : right[count-3];
            REQUIRE_EQ(expected, a);
            ++count;
        }
        REQUIRE_EQ(count, 6);
        
    }
}
