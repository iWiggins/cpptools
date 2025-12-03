#pragma once
#include <string>
#include <vector>
#include <istream>
#include <sstream>
#include "itertools.h"

namespace cpputils
{
using std::string;
using std::vector;

std::stringstream& operator << (std::stringstream& sstr, std::istream& istr)
{
    while(!istr.eof())
    {
        char c = (char)istr.get();
        if(c != EOF)
        {
            sstr << c;
        }
    }
    return sstr;
}

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

class StreamSplitIterator
{
    public:
    using difference_type = std::ptrdiff_t;
    using value_type = std::string;
    using pointer = std::string*;
    using reference = std::string&;
    using iterator_category = std::input_iterator_tag;

    StreamSplitIterator():
    stream(nullptr),
    read(true)
    {}

    StreamSplitIterator(std::istream& stream, const string& delim):
    stream(&stream),
    delim(delim),
    buffer(""),
    read(true)
    {}

    string operator * ()
    {
        if(!read)
        {
            // if we have not read the current buffered value, read it.
            read = true;
            return buffer;
        }
        else
        {
            // otherwise, advance first, then read it.
            ++*this;
            read = true;
            return buffer;
        }
    }

    StreamSplitIterator& operator ++()
    {
        if(delim.length() == 0)
        {
            if(!stream->eof())
            {
                // If not at end of stream and there is no delim,
                // read whole stream. Buffer is now unread.
                read = false;
                std::stringstream str;
                for(char c = stream->get(); c != EOF; c = stream->get())
                {
                    str.put(c);
                }
                buffer = str.str();
            }
            
        }
        else
        {
            buffer.clear();
            while(!buffer.ends_with(delim))
            {
                char c = (char)stream->get();
                if(c != EOF)
                {
                    // buffer was modified, it is unread
                    read = false;
                    buffer += c;
                }
                else
                {
                    // end of stream found, break
                    break;
                }
            }
            if(buffer.ends_with(delim))
            {
                buffer = buffer.substr(0, buffer.length()-delim.length());
            }
        }
        return *this;
    }

    void operator ++(int)
    {
        ++*this;
    }

    bool operator == (StreamSplitIterator other) const
    {
        // if this iter has a null stream, it is being used as a sentinel
        if(stream == nullptr) return other.eof();
        else return eof();
    }

    bool operator != (StreamSplitIterator other) const
    {
        // if this iter has a null stream, it is being used as a sentinel
        if(stream == nullptr) return !other.eof();
        else return !eof();
    }

    private:
    bool eof() const
    {
        return stream == nullptr || (read && stream->peek() == EOF);
    }
    std::istream* stream;
    string buffer;
    string delim;
    bool read;
};

StreamSplitIterator split(std::istream& str, const string& delim)
{
    return StreamSplitIterator(str, delim);
}

StreamSplitIterator split(std::istream& str, char delim)
{
    return split(str, string(1, delim));
}

}

