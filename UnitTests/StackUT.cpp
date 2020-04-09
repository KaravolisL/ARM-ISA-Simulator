/////////////////////////////////
/// StackUT.cpp
///
/// @brief Unit Test for Stack
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Stack.hpp"  // Test class

////////////////////////////////
/// Test Objects
////////////////////////////////
Stack<int>* pMyStack = new Stack<int>();

////////////////////////////////
/// Setup Function
////////////////////////////////
void setup()
{

}

////////////////////////////////
/// PushTest Function
////////////////////////////////
void PushTest()
{
    for (int i = 0; i < 10; i++)
    {
        pMyStack->Push(i);
        assert(pMyStack->Peek() == i);
    }
}

////////////////////////////////
/// SizeTest Function
////////////////////////////////
void SizeTest()
{
    assert(pMyStack->Size() == 10);
}

////////////////////////////////
/// PopTest Function
////////////////////////////////
void PopTest()
{
    for (int i = 9; i >= 0; i--)
    {
        int item = pMyStack->Pop();
        assert(item == i);
    }

    try
    {
        pMyStack->Pop();
        assert(false);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        pMyStack->Peek();
        assert(false);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

////////////////////////////////
/// Teardown Function
////////////////////////////////
void teardown()
{
    delete pMyStack;
}

////////////////////////////////
/// Main Function
////////////////////////////////
int main(int argc, char* argv[])
{
    setup();

    PushTest();
    SizeTest();
    PopTest();

    teardown();
    return 0;
}