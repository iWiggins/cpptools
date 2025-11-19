# CPP Utils

Useful utilities for C++ programs.

## stringutils

String functions missing from the standard library.

### split

Splits a string or character stream based on a delimiter.

The string split is a const expression.

## itertools

Additional iterators and tools for iterators.

### SingleIter

An iterator over a single value.

### MergeIter

The MergeIter classes allow combining two sets of iterators into a single iterator.

## cxtools

Constexpr versions of simple standard functions, like int to str and str to int.

### strToInt

Converts a string to an integer, for any radix. This is a const expression.

### intToStr

Converts an integer to a string, for any radix. This is a const expression.