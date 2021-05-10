//**************************************
// runtime_assert.h
//
// Contains the definition for the
// assert method I use for making
// assertions at runtime
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************
#pragma once

#include <string>

constexpr void runtime_assert(bool expr)
{
    if (expr) return;
    fprintf(stderr, "Assertion failure in file %s on line %d", __FILE__, __LINE__);
    abort();
}