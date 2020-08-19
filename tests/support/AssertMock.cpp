#include "Assert.hpp"
#include <assert.h>

void Assert(bool expr, const char* fileName, int lineNumber, int numArgs, ...)
{
    assert(expr);
}