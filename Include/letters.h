#pragma once
#include <iterator>
#include <vector>

namespace cpputils
{
class CharacterIterator
{
    char current;
    public:
    using difference_type = std::ptrdiff_t;
    using value_type = char;
    using pointer = char*;
    using reference = char&;
    using iterator_category = std::input_iterator_tag;

    constexpr CharacterIterator(char start):
    current(start) {}

    constexpr char operator * ()
    {
        return current;
    }

    constexpr CharacterIterator& operator ++ ()
    {
        ++current;
        return *this;
    }

    constexpr void operator ++ (int)
    {
        ++*this;
    }

    constexpr bool operator == (const CharacterIterator& other)
    {
        return current == other.current;
    }

    constexpr bool operator != (const CharacterIterator& other)
    {
        return current != other.current;
    }
};

constexpr std::vector<char> lowercase_letters()
{
    return std::vector<char>(CharacterIterator('a'), CharacterIterator('z'+1));
}

constexpr std::vector<char> uppercase_letters()
{
    return std::vector<char>(CharacterIterator('A'), CharacterIterator('Z'+1));
}
}