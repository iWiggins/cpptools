#pragma once
#include <string>
#include <vector>
#include "itertools.h"

namespace cpputils
{
using std::string;
using std::vector;

enum class SplitSteps
{
    End=0,
    Ending=1,
    Running=2
};

class SplitIterator
{
    public:
    using difference_type = std::ptrdiff_t;
    using value_type = std::string;
    using pointer = std::string*;
    using reference = std::string&;
    using iterator_category = std::input_iterator_tag;

    constexpr SplitIterator():
    str(""),
    strLen(0),
    delim(""),
    delLen(0),
    lastDel(0),
    start(0),
    step(SplitSteps::End)
    {}

    constexpr SplitIterator(const string& str, const string& delim):
    str(str),
    strLen(str.length()),
    delim(delim),
    delLen(delim.length()),
    lastDel(strLen-delLen),
    start(0),
    step(SplitSteps::Running)
    {
        if(strLen == 0)
        {
            step = SplitSteps::End;
        }
        else if(delLen == 0)
        {
            slice = str;
            step = SplitSteps::Ending;
        }
        else
        {
            // advance to capture first slice
            ++*this;
        }
    }

    constexpr string operator * () const
    {
        return slice;
    }

    constexpr SplitIterator& operator ++()
    {
        if(step == SplitSteps::End)
        {
            // done, do nothing
        }
        else if(step == SplitSteps::Ending)
        {
            // advance to the end, finished.
            step = SplitSteps::End;
        }
        else if(start >= strLen)
        {
            // there is a trailing delim
            slice = "";
            step = SplitSteps::Ending;
        }
        else
        {
            int pos = str.find(delim, start);
            if(pos < 0)
            {
                slice = str.substr(start);
                step = SplitSteps::Ending;
            }
            else
            {
                int sliceLen = pos - start;
                slice = str.substr(start, sliceLen);
                start = pos + delLen;
            }
        }

        return *this;
    }

    constexpr void operator ++(int)
    {
        ++*this;
    }

    constexpr bool operator == (SplitIterator other) const
    {
        // The only reason to compare against another is to check if we are at the end.
        return step == other.step;
    }

    constexpr bool operator != (SplitIterator other) const
    {
        return step != other.step;
    }

    private:
    int start;
    string str;
    int strLen;
    string delim;
    int delLen;
    int lastDel;
    string slice;
    SplitSteps step;
};

constexpr vector<string> split(const string& str, const string& delim)
{
    return vector<string>(SplitIterator(str, delim), SplitIterator());
}

constexpr vector<string> split(const string& str, char delim)
{
    return split(str, string(1, delim));
}

}
