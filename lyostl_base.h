#pragma once

/* LYOSTD_BASE.H:
   Base defines and functions for lyoSTL. */

// #define LYOSTL_DEBUG

#ifdef LYOSTL_DEBUG
#include <iostream>
#endif

#define LYOSTL_BEGIN namespace lyo {
#define LYOSTL_END }

constexpr int CEIL_INT(double x)
{
    const int i = static_cast<int>(x);
    return (x > i) ? (i + 1) : (i);
}