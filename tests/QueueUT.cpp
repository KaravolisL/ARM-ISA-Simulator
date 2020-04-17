/////////////////////////////////
/// @file QueueUT.cpp
///
/// @brief Unit Test for Queue
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
#include <assert.h>
#include <iostream>

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include "Queue.hpp"  // Test class

////////////////////////////////
/// Test Objects
////////////////////////////////
Queue<int> myQueue = Queue<int>();

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
        myQueue.Push(i);
        assert(myQueue.Peek() == 0);
    }
    assert(myQueue.Size() == 10);
}

////////////////////////////////
/// PopTest Function
////////////////////////////////
void PopTest()
{
    for (int i = 0; i < 10; i++)
    {
        int value = myQueue.Pop();
        assert(value == i);
    }

    try
    {
        myQueue.Pop();
        assert(false);
    }
    catch(const Queue<int>::EmptyQueueException& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

////////////////////////////////
/// Teardown Function
////////////////////////////////
void teardown()
{

}

////////////////////////////////
/// Main Function
////////////////////////////////
int main(int argc, char* argv[])
{
    setup();

    PushTest();
    PopTest();

    teardown();

    std::cout << "Queue Unit Test Complete: SUCCESS";
    return 0;
}