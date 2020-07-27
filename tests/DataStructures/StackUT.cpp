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
#include "UnitTest.hpp"
#include "Stack.hpp"  // Test class

////////////////////////////////
/// Test Objects
////////////////////////////////
Stack<int> myStack;

////////////////////////////////
/// PushTest Function
////////////////////////////////
bool PushTest()
{
    for (int i = 0; i < 10; i++)
    {
        myStack.Push(i);
        UNIT_ASSERT(myStack.Peek() == i);
    }

    return true;
}

////////////////////////////////
/// SizeTest Function
////////////////////////////////
bool SizeTest()
{
    UNIT_ASSERT(myStack.Size() == 10);
    return true;
}

////////////////////////////////
/// PopTest Function
////////////////////////////////
bool PopTest()
{
    for (int i = 9; i >= 0; i--)
    {
        int item = myStack.Pop();
        UNIT_ASSERT(item == i);
    }

    try
    {
        myStack.Pop();
        UNIT_ASSERT(false);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        myStack.Peek();
        UNIT_ASSERT(false);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return true;
}

////////////////////////////////
/// Main Function
////////////////////////////////
bool StackUT()
{
    UnitTest unitTest("Stack Unit Test");

    unitTest.AddSubTest(PushTest);
    unitTest.AddSubTest(SizeTest);
    unitTest.AddSubTest(PopTest);

    return unitTest.Run();
}