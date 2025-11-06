#pragma once
#include <string>
#include <vector>

namespace cpputils
{
using std::string;
using std::vector;

vector<string> split(const string& str, const string& delim)
{
    vector<string> results;
    const int strLen = str.length();
    const int delLen = delim.length();
    const int lastDel = strLen - delLen;
    int start = 0;

    // If string is empty, return empty results.
    if(strLen == 0)
    {
        return results;
    }

    // If delim is empty, put whole string in result
    if(delLen == 0)
    {
        results.push_back(str);
        return results;
    }

    while(start < strLen)
    {
        int pos = str.find(delim, start);
        if(pos < 0)
        {
            string slice = str.substr(start);
            results.push_back(slice);
            break;
        }
        else
        {
            int sliceLen = pos - start;
            string slice = str.substr(start, sliceLen);
            results.push_back(slice);
            start = pos + delLen;
        }
        // special case for if the string ends with a deliminator
        if(pos == lastDel)
        {
            results.push_back("");
            break;
        }
    }

    return results;
}
vector<string> split(const string& str, char delim)
{
    return split(str, string(1,delim));
}
}