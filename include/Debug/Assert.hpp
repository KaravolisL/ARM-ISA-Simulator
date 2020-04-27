/////////////////////////////////
/// @file Assert.hpp
///
/// @brief Declaration of Assert functions
///
/// @details These functions are used in place
/// of the traditional assert method. They allow
/// for more information to be included when
/// an assert statement is added
///
/// @author Luke Karavolis
/////////////////////////////////
#ifndef ASSERT_HPP
#define ASSERT_HPP

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
// (None)

// FORWARD DECLARATIONS
// (None)

// Macros
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// Accept any number of args >= N, but expand to just the Nth one. In this case,
// we have settled on 9 as N. We could pick a different number by adjusting
// the count of throwaway args before N. Note that this macro is preceded by
// an underscore--it's an implementation detail, not something we expect people
// to call directly.
#define _GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N

// Count how many args are in a variadic macro. Only works for up to N-1 args.
#define _COUNT_VARARGS(...) _GET_NTH_ARG("ignored", ##__VA_ARGS__, 8, 7, 6, 5, 4, 3, 2, 1, 0)

/// This macro is to be used to in place of the traditional assert statement
/// in order to pass along more information in the case that the expression is
/// false.
#define ASSERT( expr, ... ) Assert(expr, __FILENAME__, __LINE__, _COUNT_VARARGS(__VA_ARGS__), ##__VA_ARGS__)

////////////////////////////////
/// FUNCTION NAME: Assert
///
/// @brief This function wraps the traditional
/// assert statement. If false, this function
/// will print the provided messages to the debug
/// log prior to asserting. It should only be called
/// using the ASSERT macro defined above
///
/// @warning This function is not to be called. It's
/// included in the above macro
///
/// @note USAGE: ASSERT(expression, format string, ...)
///
/// @param expr         Expression to be asserted
/// @param fileName     Name of file where assert is placed
/// @param lineNumber   Line on which assert is placed
/// @param numArgs      Number of arguments passed in additionally
/// @param ...          Format string followed by replacement variables
////////////////////////////////
void Assert(bool expr, const char* fileName, int lineNumber, int numArgs, ...);

#endif