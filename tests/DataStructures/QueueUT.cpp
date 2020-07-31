/////////////////////////////////
/// @file QueueUT.cpp
///
/// @brief Unit Test for Queue
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <catch2/catch.hpp>
#include "Queue.hpp"  // Test class

TEST_CASE("Queue Basic Functionality", "[data_structure]")
{
    Queue<int> queue = Queue<int>();

    for (int i = 0; i < 10; i++)
    {
        queue.Push(i);
        REQUIRE(queue.Peek() == 0);
    }
    REQUIRE(queue.Size() == 10);

    for (int i = 0; i < 10; i++)
    {
        REQUIRE(queue.Pop() == i);
    }

    REQUIRE_THROWS_AS(queue.Pop(), Queue<int>::EmptyQueueException);
}
