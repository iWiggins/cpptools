#pragma once
#include <iterator>

namespace cpputils
{

class SingleIterSentinel{};

template <typename T>
class SingleIter
{
public:

    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::input_iterator_tag;

    explicit constexpr SingleIter(const T& d):
    data(d),
    consumed(false)
    {}

    constexpr T operator*() const
    {
        return data;
    }
 
    constexpr SingleIter<T>& operator++()
    {
        consumed = true;
        return *this;
    }

    constexpr void operator++(int)
    {
        ++*this;
    }

    constexpr bool operator == (SingleIterSentinel sent) const
    {
        return consumed;
    }

    constexpr bool operator != (SingleIterSentinel sent) const
    {
        return !consumed;
    }


private:

    T data;
    bool consumed;
};

class MergeIterSentinel{};

template <typename T, std::input_iterator leftIt, std::sentinel_for<leftIt> leftSt, std::input_iterator rightIt, std::sentinel_for<rightIt> rightSt>
class MergeIter
{
public:

using self = MergeIter<T, leftIt, leftSt, rightIt, rightSt>;

    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::input_iterator_tag;

    constexpr MergeIter(leftIt leftBegin, leftSt leftEnd, rightIt rightBegin, rightSt rightEnd):
    leftCurr(leftBegin),
    leftEnd(leftEnd),
    rightCurr(rightBegin),
    rightEnd(rightEnd),
    left(true)
    {}
 
    constexpr T operator*() const
    {
        return left ? *leftCurr : *rightCurr;
    }
 
    constexpr self& operator++()
    {
        if(left)
        {
            if(leftCurr != leftEnd)
            {
                ++leftCurr;
                if(leftCurr == leftEnd)
                {
                    left = false;
                }
            }
        }
        else
        {
            if(rightCurr != rightEnd)
            {
                ++rightCurr;
            }
        }
        return *this;
    }

    constexpr void operator++(int)
    {
        ++*this;
    }

    constexpr bool operator == (const MergeIterSentinel sent) const
    {
        return !left && rightCurr == rightEnd;
    }

    constexpr bool operator != (const MergeIterSentinel sent) const
    {
        return left || rightCurr != rightEnd;
    }

private:

    leftIt leftCurr;
    leftSt leftEnd;
    rightIt rightCurr;
    rightSt rightEnd;
    bool left;
};

template <typename T, std::input_iterator leftIt, std::sentinel_for<leftIt> leftSt, std::input_iterator rightIt, std::sentinel_for<rightIt> rightSt>
class PolyMerge
{
    public:
    using iterator = MergeIter<T, leftIt, leftSt, rightIt, rightSt>;

    constexpr PolyMerge(leftIt leftBegin, leftSt leftEnd, rightIt rightBegin, rightSt rightEnd):
    leftBegin(leftBegin),
    leftEnd(leftEnd),
    rightBegin(rightBegin),
    rightEnd(rightEnd)
    {}

    constexpr iterator begin()
    {
        return cbegin();
    }
    constexpr MergeIterSentinel end()
    {
        return MergeIterSentinel();
    }
    constexpr iterator cbegin() const
    {
            return iterator(leftBegin, leftEnd, rightBegin, rightEnd);
    }
    constexpr MergeIterSentinel cend() const
    {
        return end();
    }

    leftIt leftBegin;
    leftSt leftEnd;
    rightIt rightBegin;
    rightSt rightEnd;
};

template <typename T, std::input_iterator leftIt, std::input_iterator rightIt>
class BiMerge: public PolyMerge<T, leftIt, leftIt, rightIt, rightIt>
{
    public:
    constexpr BiMerge(leftIt leftBegin, leftIt leftEnd, rightIt rightBegin, rightIt rightEnd):
    PolyMerge<T, leftIt, leftIt, rightIt, rightIt>(leftBegin, leftEnd, rightBegin, rightEnd)
    {}
};

template <typename T, std::input_iterator it, std::sentinel_for<it> st>
class MonoMerge: public PolyMerge<T, it, st, it, st>
{
    public:
    constexpr MonoMerge(it leftBegin, st leftEnd, it rightBegin, st rightEnd):
    PolyMerge<T, it, st, it, st>(leftBegin, leftEnd, rightBegin, rightEnd)
    {}
};

template <typename T, std::input_iterator it>
class Merge: public PolyMerge<T, it, it, it, it>
{
    public:
    constexpr Merge(it leftBegin, it leftEnd, it rightBegin, it rightEnd):
    PolyMerge<T, it, it, it, it>(leftBegin, leftEnd, rightBegin, rightEnd)
    {}
};

}