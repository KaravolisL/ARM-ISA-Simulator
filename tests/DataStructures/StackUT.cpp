/////////////////////////////////
/// @file StackUT.cpp
///
/// @brief Unit Test for Stack
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <catch2/catch.hpp>
#include "UnitTest.hpp"
#include "Stack.hpp"  // Test class

TEST_CASE("Push and Peek", "[data_structure]")
{
    Stack<uint32_t> stack;

    for (uint32_t i = 0; i < 25; i++)
    {
        stack.Push(i);
        REQUIRE(stack.Peek() == i);
        REQUIRE(stack.Size() == (i + 1));
    }

    for (int32_t i = 24; i >= 0; i--)
    {
        REQUIRE(stack.Pop() == static_cast<uint32_t>(i));
        REQUIRE(stack.Size() == static_cast<uint32_t>(i));
    }

    REQUIRE_THROWS(stack.Pop());
    REQUIRE_THROWS(stack.Peek());
}
